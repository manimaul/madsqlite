cmake_minimum_required(VERSION 3.4.1)

set(SOURCE_FILES
        src/main/cpp/Constants.h
        src/main/cpp/ContentValues.h
        src/main/cpp/ContentValues.cpp
        src/main/cpp/Cursor.cpp
        src/main/cpp/Cursor.h
        src/main/cpp/Database.cpp
        src/main/cpp/Database.h
        src/main/cpp/Util.cpp
        src/main/cpp/sqlite-amalgamation-3140200/sqlite3.h
        src/main/cpp/sqlite-amalgamation-3140200/sqlite3.c)

#add_definitions(-DSQLITE_ENABLE_RTREE)
#add_definitions(-DSQLITE_ENABLE_FTS4)
add_definitions(-DSQLITE_ENABLE_FTS5)
#add_definitions(-DSQLITE_ENABLE_JSON1)

if (ANDROID)
    set(SOURCE_FILES
            src/main/cpp/MadSqlite.cpp
            ${SOURCE_FILES})
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    set(SOURCE_FILES
            src/main/cpp/Main.cpp
            ${SOURCE_FILES})
endif ()

if (ANDROID)
    add_library(madsqlite-lib SHARED ${SOURCE_FILES})
    find_library(log-lib log)
    target_link_libraries(madsqlite-lib ${log-lib})
else ()
    add_executable(madsqlite-lib ${SOURCE_FILES})
    target_link_libraries(madsqlite-lib)
endif ()