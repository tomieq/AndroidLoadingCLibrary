#include <stdlib.h>
#include "libstatic.h"
#include <android/log.h>

#define APPNAME "StaticLib"
#define LOGD(...)  __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, __VA_ARGS__) ;

int staticNumber() {
    return 40;
}


uint32_t sign (uint8_t s[64], const uint8_t h[32], const uint32_t *t) {
    LOGD("sign called");
    // fill with values 192 to 255
    for (int i = 0; i < 64; i++) {
        s[i] = i + 192;
    }
    char hBuffer[128] = {0}; // Bufor na log
    for (int i = 0; i < 32; i++) {
        snprintf(hBuffer + i * 3, 4, "%02X ", h[i]); // Formatowanie do hex
    }
    LOGD("h (32 bytes): %s", hBuffer);

    char tBuffer[128] = {0};
    for (int i = 0; i < 10; i++) {
        snprintf(tBuffer + i * 9, 10, "%08X ", t[i]);
    }
    LOGD("t (first 10 int values): %s", tBuffer);
    return 6;
}