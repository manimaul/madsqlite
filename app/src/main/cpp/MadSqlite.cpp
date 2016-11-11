#include <jni.h>
#include <string>
#include "Database.h"

/*
 * How to find java class,field and method signatures:
 * $unzip /Library/Java/JavaVirtualMachines/jdk1.8.0_74.jdk/Contents/Home/jre/lib/rt.jar
 * $javap -s ./java/lang/Object.class
 */

ContentValues::DataType typeOf(JNIEnv *env, jobject &object) {
    jclass integerClass = env->FindClass("java/lang/Integer");
    jclass doubleClass = env->FindClass("java/lang/Double");
    jclass stringClass = env->FindClass("java/lang/String");
    // todo: Float
    // todo: Long
    jclass arrayClass = env->FindClass("java/lang/reflect/Array");

    jclass objectClass = env->FindClass("java/lang/Object");
    jmethodID getClassMethodId = env->GetMethodID(objectClass, "getClass", "()Ljava/lang/Class;");
    jmethodID equalsMethodId = env->GetMethodID(objectClass, "equals", "(Ljava/lang/Object;)Z");
    jobject theClass = env->CallObjectMethod(object, getClassMethodId);
    if (env->CallBooleanMethod(theClass, equalsMethodId, integerClass)) {
        return ContentValues::DataType::INT;
    }
    if (env->CallBooleanMethod(theClass, equalsMethodId, doubleClass)) {
        return ContentValues::DataType::REAL;
    }
    if (env->CallBooleanMethod(theClass, equalsMethodId, stringClass)) {
        return ContentValues::DataType::TEXT;
    }
    if (env->CallBooleanMethod(theClass, equalsMethodId, arrayClass)) {
        return ContentValues::DataType::BLOB;
    }
    return ContentValues::DataType::NONE;
}

int jobjectToInteger(JNIEnv *env, jobject &value) {
    jclass jClass = env->FindClass("java/lang/Integer");
    jmethodID methodId = env->GetMethodID(jClass, "intValue", "()I");
    return env->CallIntMethod(value, methodId);
}

double jobjectToDouble(JNIEnv *env, jobject &value) {
    jclass jClass = env->FindClass("java/lang/Double");
    jmethodID methodId = env->GetMethodID(jClass, "doubleValue", "()D");
    return env->CallDoubleMethod(value, methodId);
}

std::string jobjectToString(JNIEnv *env, jobject &value) {
    const char *strValue = env->GetStringUTFChars((jstring) value, 0);
    std::string retVal(strValue);
    env->ReleaseStringUTFChars((jstring) value, strValue);
    return retVal;
}


extern "C" {

JNIEXPORT jboolean JNICALL
Java_io_madrona_madsqlite_JniBridge_moveToFirst(JNIEnv *env,
                                                jclass type,
                                                jlong nativePtr) {

    Cursor *cursor = reinterpret_cast<Cursor *>(nativePtr);
    return (jboolean) cursor->moveToFirst();
}

JNIEXPORT jboolean JNICALL
Java_io_madrona_madsqlite_JniBridge_moveToPosition(JNIEnv *env,
                                                   jclass type,
                                                   jlong nativePtr,
                                                   jint position) {
    Cursor *cursor = reinterpret_cast<Cursor *>(nativePtr);
    return (jboolean) cursor->moveToPosition(position);
}

JNIEXPORT jint JNICALL
Java_io_madrona_madsqlite_JniBridge_getCount(JNIEnv *env,
                                             jclass type,
                                             jlong nativePtr) {

    Cursor *cursor = reinterpret_cast<Cursor *>(nativePtr);
    return cursor->getCount();
}

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
            ContentValues::DataType dataType = typeOf(env, value);
            switch (dataType) {
                case ContentValues::INT:
                    contentValues.putInteger(keyStr, jobjectToInteger(env, value));
                    break;
                case ContentValues::REAL:
                    contentValues.putReal(keyStr, jobjectToDouble(env, value));
                    break;
                case ContentValues::TEXT:
                    contentValues.putString(keyStr, jobjectToString(env, value));
                    break;
                case ContentValues::BLOB: {
                    size_t sz = sizeof(value);
                    contentValues.putBlob(keyStr, &value, sz);
                    break;
                }
                case ContentValues::NONE:
                    break;
            }
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
        for (int i = 0; i < count; i++) {
            jstring str = (jstring) (env->GetObjectArrayElement(args, i));
            const char *rawString = env->GetStringUTFChars(str, 0);
            argsVector.push_back(rawString);
            env->ReleaseStringUTFChars(str, rawString);
        }
        auto c = db->query(queryStr, argsVector);
        cursor = new Cursor(std::move(c));
    } else {
        auto c = db->query(queryStr);
        cursor = new Cursor(std::move(c));
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
    delete (db);
}

JNIEXPORT void JNICALL
Java_io_madrona_madsqlite_JniBridge_closeCursor(JNIEnv *env,
                                                jclass type,
                                                jlong nativePtr) {
    void *db = reinterpret_cast<void *>(nativePtr);
    delete (db);
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    //todo: index class, field and method ids
    return JNI_VERSION_1_6;
}

}
