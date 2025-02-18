#!/usr/bin/swift

import Foundation

struct Shell {
    @discardableResult
    func exec(_ command: String) -> String {
        // print("💻 \(command)")
        let task = Process()
        let pipe = Pipe()
        task.standardOutput = pipe
        task.standardError = pipe
        task.arguments = ["-c", command]
        task.launchPath = "/bin/zsh"
        task.launch()
        let data = pipe.fileHandleForReading.readDataToEndOfFile()
        let output = String(data: data, encoding: .utf8)!
        return output.trimmingCharacters(in: .newlines)
    }
}

struct Architecture {
    let folder: String
    let target: String
}

let architectures = [
    Architecture(folder: "x86_64", target: "x86_64-linux-android21"),
    Architecture(folder: "armeabi-v7a", target: "armv7a-linux-androideabi21"),
    Architecture(folder: "arm64-v8a", target: "aarch64-linux-android21"),
    Architecture(folder: "x86", target: "i686-linux-android21")
]

let shell = Shell()
@discardableResult func sh(_ command: String) -> String {
    shell.exec(command)
}
func c(_ command: String) {
    print(shell.exec(command))
}

let clangBin = sh("find ~/Library/Android/sdk/ndk -type l -name \"clang\"")
print(clangBin)
sh("rm -rf jniLibs")

architectures.forEach { arch in
    print("Compiling for arch: \(arch.target)")
    sh("mkdir -p jniLibs/\(arch.folder)")

    // compile static library
    sh("\(clangBin) --target=\(arch.target) -c -fPIC libstatic.c -o libstatic.o")
    sh("ar rcs libstatic.a libstatic.o")
    c("ar -t libstatic.a")
    // c("lipo -info libstatic.a") // not working for linux-elf formats
    c("objdump -a libstatic.a | grep 'file format'") // works for linux elf
    // c("nm libstatic.a")

    // compile dynamic library
    sh("\(clangBin) --target=\(arch.target) -c -fPIC libdynamic.c -o libdynamic.o")
    sh("\(clangBin) --target=\(arch.target) -llog libdynamic.o libstatic.a -shared -o libdynamic.so")
    c("nm libdynamic.so")
    sh("mv libdynamic.so jniLibs/\(arch.folder)")
    sh("rm *.o *.a")

    c("file jniLibs/\(arch.folder)/libdynamic.so")
}

print(sh("tree ."))

let androidProjectFolder = "/Users/tomaskuc/AndroidStudioProjects/StartingPoint/app/src/main"
sh("rm -rf \(androidProjectFolder)/jniLibs")
sh("cp -R jniLibs \(androidProjectFolder)")
