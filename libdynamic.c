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

JNIEXPORT jint JNICALL Java_com_example_startingpoint_CAPI_sign
  (JNIEnv *env, jobject obj, jbyteArray sArray, jbyteArray hArray, jintArray tArray) {
    
    // validate arguments
    if ((*env)->GetArrayLength(env, sArray) != 64 || (*env)->GetArrayLength(env, hArray) != 32) {
        return -1;  // error invalid size of arrays
    }
    // get h data from jbyteArray
    uint8_t h[32];
    (*env)->GetByteArrayRegion(env, hArray, 0, 32, (jbyte *)h);

    
    jsize tLength = (*env)->GetArrayLength(env, tArray);
    // get pointer to t jintArray
    uint32_t *t = (uint32_t *)(*env)->GetIntArrayElements(env, tArray, NULL);

    // buffer for s output
    uint8_t s[64];
    // call the function
    uint32_t result = sign(s, h, t);

    // save the result to jbyteArray (Java)
    (*env)->SetByteArrayRegion(env, sArray, 0, 64, (const jbyte *)s);

    // release resources
    (*env)->ReleaseIntArrayElements(env, tArray, (jint *)t, JNI_ABORT);

    // return the resultt to Java
    return (jint)result;
}