# Install Android NDK

NDK is needed for `clang` compiler

# Run build script

Run script to build `C` code as dynamic library for Android project:
```
./build.swift
```

# Use in Android App

Create `CAPI` class that exposes JNI C API to android app:
```kotlin
package com.example.startingpoint

import android.util.Log

class CAPI {
    companion object {
        init {
            Log.i("CAPI", "Loading libdynamic")
            System.loadLibrary("dynamic")
        }
    }
    external fun process()
    external fun dynamicNumber(): Int
    external fun staticNumber(): Int
    external fun sign(s: ByteArray, h: ByteArray, t: IntArray): Int
}
```

Usage:

```kotlin
fun hexString(bytes: ByteArray): String {
    return "${bytes.size} bytes: " + bytes.joinToString(" ") { "%02X".format(it) }
}

val s = ByteArray(64) // output buffer
val h = ByteArray(32) { (it + 223).toByte() } // 0xDF, ..., 0xFF
val t = IntArray(640) { it } // 0, 1, 2, ..., 639


Log.i("MainActivity", "h[] (hex): " + hexString(h))
val result = api.sign(s, h, t)
Log.i("MainActivity","result: ${"0x" + result.toUInt().toString(16).uppercase()}")
Log.i("MainActivity", "s[] (hex): " + hexString(s))
```