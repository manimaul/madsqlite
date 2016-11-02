#include <jni.h>
#include <string>
#include "Database.h"

extern "C" {

JNIEXPORT jboolean JNICALL
Java_io_madrona_madsqlite_JniBridge_moveToNext(JNIEnv *env,
                                               jclass type,
                                               jlong nativePtr) {
    Cursor *cursor = reinterpret_cast<Cursor *>(nativePtr);
    return (jboolean) cursor->moveToNext();
}

JNIEXPORT jboolean JNICALL
Java_io_madrona_madsqlite_JniBridge_isAfterLast(JNIEnv *env,
                                                jclass type,
                                                jlong nativePtr) {
    Cursor *cursor = reinterpret_cast<Cursor *>(nativePtr);
    return (jboolean) cursor->isAfterLast();
}

JNIEXPORT jint JNICALL
Java_io_madrona_madsqlite_JniBridge_getDataCount(JNIEnv *env,
                                                 jclass type,
                                                 jlong nativePtr) {
    Cursor *cursor = reinterpret_cast<Cursor *>(nativePtr);
    return cursor->getDataCount();
}

JNIEXPORT jstring JNICALL
Java_io_madrona_madsqlite_JniBridge_getString(JNIEnv *env,
                                              jclass type,
                                              jlong nativePtr,
                                              jint columnIndex) {
    Cursor *cursor = reinterpret_cast<Cursor *>(nativePtr);
    auto str = cursor->getString(columnIndex);
    return env->NewStringUTF(str.c_str());
}

JNIEXPORT jbyteArray JNICALL
Java_io_madrona_madsqlite_JniBridge_getBlob(JNIEnv *env,
                                            jclass type,
                                            jlong nativePtr,
                                            jint columnIndex) {
    Cursor *cursor = reinterpret_cast<Cursor *>(nativePtr);
    auto vec = cursor->getBlob(columnIndex);
    jbyteArray retVal = env->NewByteArray((jsize) vec.size());
    env->SetByteArrayRegion(retVal, 0, (jsize) vec.size(), (const jbyte *) vec.front());
    return retVal;
}

JNIEXPORT jlong JNICALL
Java_io_madrona_madsqlite_JniBridge_getInt(JNIEnv *env,
                                           jclass type,
                                           jlong nativePtr,
                                           jint columnIndex) {

    Cursor *cursor = reinterpret_cast<Cursor *>(nativePtr);
    return (jlong) cursor->getInt(columnIndex);
}

JNIEXPORT jdouble JNICALL
Java_io_madrona_madsqlite_JniBridge_getReal(JNIEnv *env,
                                            jclass type,
                                            jlong nativePtr,
                                            jint columnIndex) {
    Cursor *cursor = reinterpret_cast<Cursor *>(nativePtr);
    return cursor->getReal(columnIndex);
}

JNIEXPORT jstring JNICALL
Java_io_madrona_madsqlite_JniBridge_getError(JNIEnv *env,
                                             jclass type,
                                             jlong dbPtr) {
    Database *db = reinterpret_cast<Database *>(dbPtr);
    return env->NewStringUTF(db->getError().c_str());
}

JNIEXPORT void JNICALL
Java_io_madrona_madsqlite_JniBridge_beginTransaction(JNIEnv *env,
                                                     jclass type,
                                                     jlong dbPtr) {
    Database *db = reinterpret_cast<Database *>(dbPtr);
    db->beginTransaction();
}

JNIEXPORT void JNICALL
Java_io_madrona_madsqlite_JniBridge_rollbackTransaction(JNIEnv *env,
                                                        jclass type,
                                                        jlong dbPtr) {
    Database *db = reinterpret_cast<Database *>(dbPtr);
    db->rollbackTransaction();
}

JNIEXPORT void JNICALL
Java_io_madrona_madsqlite_JniBridge_endTransaction(JNIEnv *env,
                                                   jclass type,
                                                   jlong dbPtr) {
    Database *db = reinterpret_cast<Database *>(dbPtr);
    db->endTransaction();
}

//JNIEXPORT jboolean JNICALL
//Java_io_madrona_madsqlite_JniBridge_insert(JNIEnv *env,
//                                           jclass type,
//                                           jlong dbPtr,
//                                           jstring table,
//                                           jobject values) {
//    const char *tableStr = env->GetStringUTFChars(table, 0);
//    jclass contentValuesClass = env->GetObjectClass(values);
//    jmethodID getMethodId = env->GetMethodID(contentValuesClass, "get", "()Ljava/lang/String;");
//    jobject value = env->CallObjectMethod(values, getMethodId, "key");
//    Database *db = reinterpret_cast<Database *>(dbPtr);
//
//    env->ReleaseStringUTFChars(table, tableStr);
//}

JNIEXPORT jboolean JNICALL
Java_io_madrona_madsqlite_JniBridge_insert(JNIEnv *env,
                                           jclass type,
                                           jlong dbPtr,
                                           jstring table,
                                           jobjectArray keys,
                                           jobjectArray values) {
    const char *tableStr = env->GetStringUTFChars(table, 0);
    int keyCount = env->GetArrayLength(keys);
    int valueCount = env->GetArrayLength(keys);
    ContentValues contentValues = {};
    if (keyCount == valueCount) {
        for (int i = 0; i < keyCount; i++) {
            jstring key = (jstring) (env->GetObjectArrayElement(keys, i));
            const char *keyStr = env->GetStringUTFChars(key, 0);
            jobject value = env->GetObjectArrayElement(values, i);
            size_t sz = sizeof(value);
            contentValues.putBlob(keyStr, &value, sz); //todo: put specific type
            env->ReleaseStringUTFChars(key, keyStr);
        }
        Database *db = reinterpret_cast<Database *>(dbPtr);
        bool retVal = db->insert(tableStr, contentValues);
        env->ReleaseStringUTFChars(table, tableStr);
        return (jboolean) retVal;
    } else {
        return (jboolean) false;
    }
}

JNIEXPORT jint JNICALL
Java_io_madrona_madsqlite_JniBridge_exec(JNIEnv *env,
                                         jclass type,
                                         jlong dbPtr,
                                         jstring sql) {
    const char *sqlStr = env->GetStringUTFChars(sql, 0);
    Database *db = reinterpret_cast<Database *>(dbPtr);
    int changes = db->exec(sqlStr);
    env->ReleaseStringUTFChars(sql, sqlStr);
    return reinterpret_cast<jint>(changes);
}

JNIEXPORT jlong JNICALL
Java_io_madrona_madsqlite_JniBridge_query(JNIEnv *env,
                                          jclass type,
                                          jlong dbPtr,
                                          jstring query,
                                          jobjectArray args) {
    Database *db = reinterpret_cast<Database *>(dbPtr);
    const char *queryStr = env->GetStringUTFChars(query, 0);
    Cursor *cursor;
    if (args) {
        int count = env->GetArrayLength(args);
        auto argsVector = std::vector<std::string>((unsigned long) count);
        for (int i=0; i<count; i++) {
            jstring str = (jstring) (env->GetObjectArrayElement(args, i));
            const char *rawString = env->GetStringUTFChars(str, 0);
            argsVector.push_back(rawString);
            env->ReleaseStringUTFChars(str, rawString);
        }
        auto c = db->query(queryStr, argsVector);
        cursor = new Cursor(c);
    } else {
        auto c = db->query(queryStr);
        cursor = new Cursor(c);
    }
    env->ReleaseStringUTFChars(query, queryStr);
    return reinterpret_cast<jlong>(cursor);
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
