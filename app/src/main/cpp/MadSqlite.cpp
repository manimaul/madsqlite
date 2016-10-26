#include <jni.h>
#include <string>
#include "Database.h"

extern "C" {

JNIEXPORT jlong JNICALL
Java_io_madrona_madsqlite_JniBridge_query(JNIEnv *env,
                                          jclass type,
                                          jlong dbPtr,
                                          jstring query,
                                          jobjectArray args) {
    const char *queryStr = env->GetStringUTFChars(query, 0);

    int count = env->GetArrayLength(args);
    auto argsVector = std::vector<std::string>((unsigned long) count);
    for (int i=0; i<count; i++) {
        jstring str = (jstring) (env->GetObjectArrayElement(args, i));
        const char *rawString = env->GetStringUTFChars(str, 0);
        argsVector.push_back(rawString);
        env->ReleaseStringUTFChars(str, rawString);
    }

    Database *db = reinterpret_cast<Database *>(dbPtr);
    auto cursor = db->query(queryStr, argsVector);

    env->ReleaseStringUTFChars(query, queryStr);
    return reinterpret_cast<jlong>(new Cursor(cursor));
}

JNIEXPORT jlong JNICALL
Java_io_madrona_madsqlite_JniBridge_openDatabase(JNIEnv *env,
                                                 jclass type,
                                                 jstring absPath) {
    if (absPath) {
        const char *path = env->GetStringUTFChars(absPath, 0);
        jlong retVal = reinterpret_cast<jlong>(new Database(path));
        env->ReleaseStringUTFChars(absPath, path);
        return retVal;
    } else {
        return reinterpret_cast<jlong>(new Database());
    }
}

JNIEXPORT void JNICALL
Java_io_madrona_madsqlite_JniBridge_closeDatabase(JNIEnv *env,
                                                  jclass type,
                                                  jlong nativePtr) {
    void *db = reinterpret_cast<void *>(nativePtr);
    delete(db);
}

JNIEXPORT void JNICALL
Java_io_madrona_madsqlite_JniBridge_closeCursor(JNIEnv *env,
                                                jclass type,
                                                jlong nativePtr) {
    void *db = reinterpret_cast<void *>(nativePtr);
    delete(db);
}

}
