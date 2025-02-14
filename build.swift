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

let clangBin = sh("find ~/Library/Android/sdk/ndk -type l -name \"clang\"")
print(clangBin)
sh("rm -rf jniLibs")

architectures.forEach { arch in
    sh("mkdir -p jniLibs/\(arch.folder)")
    print(sh("\(clangBin) --target=\(arch.target) -c -fPIC sample.c -o sample.o"))
    print(sh("\(clangBin) --target=\(arch.target) -llog sample.o -shared -o libsample.so"))
    sh("mv libsample.so jniLibs/\(arch.folder)")

    print(sh("file jniLibs/\(arch.folder)/libsample.so"))
}

print(sh("tree ."))

