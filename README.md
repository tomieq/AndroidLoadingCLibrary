# Install Android NDK

NDK is needed for `clang` compiler

# Run build script

Run script to build `C` code as dynamic library for Android project:
```
./build.swift
```

# Use in Android App

Create `CAPI` class that exposes JNI C API to android app:
```
package com.example.startingpoint

import android.util.Log

class CAPI {
    companion object {
        init {
            Log.i("CAPI", "Loading libdynamic")
            System.loadLibrary("dynamic")
        }
    }
    external fun simple()
    external fun dynamicNumber(): Int
    external fun staticNumber(): Int
}
```