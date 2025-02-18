#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include "libstatic.h"

#define APPNAME "CLib"

#define LOGD(...)  __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, __VA_ARGS__) ;

// this function returns integer
int dynamicNumber() {
    printf("[libC] This function returns 5\n");
    return 5;
}

// this function just executes, no parameter or return value

void process() {
    LOGD("[libC] No returning process\n");
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD(">> JNI_OnLoad()");
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_com_example_startingpoint_CAPI_process(JNIEnv *env, jclass aclass){
    LOGD("process call");
    process();
}

JNIEXPORT jint JNICALL Java_com_example_startingpoint_CAPI_dynamicNumber(JNIEnv *env, jclass aclass){
    LOGD("dynamicNumber call");
    return dynamicNumber();
}

JNIEXPORT jint JNICALL Java_com_example_startingpoint_CAPI_staticNumber(JNIEnv *env, jclass aclass){
    LOGD("staticNumber call");
    return staticNumber();
}