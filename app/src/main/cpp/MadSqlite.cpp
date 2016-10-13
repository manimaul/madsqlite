#include <jni.h>
#include <string>
#include "Database.h"


extern "C" {

JNIEXPORT jlong JNICALL
Java_io_madrona_madsqlite_JniBridge_openDatabase(JNIEnv *env, jclass type, jstring absPath_) {
    const char *absPath = env->GetStringUTFChars(absPath_, 0);
    env->ReleaseStringUTFChars(absPath_, absPath);
    return reinterpret_cast<jlong>(new Database(absPath));
}

JNIEXPORT void JNICALL
Java_io_madrona_madsqlite_JniBridge_closeDatabase(JNIEnv *env, jclass type, jlong ptr) {
    Database *db = reinterpret_cast<Database *>(ptr);
    delete(db);
}

JNIEXPORT void JNICALL
Java_io_madrona_madsqlite_JniBridge_closeCursor(JNIEnv *env, jclass type, jlong nativePtr) {

}

}
