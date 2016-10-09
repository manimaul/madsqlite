#include <jni.h>
#include <string>
#include "sqlite-amalgamation-3140200/sqlite3.h"

extern "C" {

jstring Java_io_madrona_madsqlite_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    const char* version = sqlite3_libversion();
    return env->NewStringUTF(version);
}

}
