#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <android/log.h>

#define APPNAME "CLib"

#define LOGD(...)  __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, __VA_ARGS__) ;

// this function returns integer
int getNumber() {
    printf("[libC] This function returns 5\n");
    return 5;
}

// this function just executes, no parameter or return value

void simple() {
    LOGD("[libC] No returning function\n");
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD(">> JNI_OnLoad()");
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_com_example_startingpoint_CAPI_simple(JNIEnv *env, jclass aclass){
    LOGD("simple call");
    simple();
}

JNIEXPORT jint JNICALL Java_com_example_startingpoint_CAPI_getNumber(JNIEnv *env, jclass aclass){
    LOGD("getNumber call");
    return 12;
}