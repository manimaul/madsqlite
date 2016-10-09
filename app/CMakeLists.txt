cmake_minimum_required(VERSION 3.4.1)

add_library( madsqlite-lib
             SHARED
             src/main/cpp/mad-sqlite.cpp
             src/main/cpp/sqlite-amalgamation-3140200/sqlite3.h
             src/main/cpp/sqlite-amalgamation-3140200/sqlite3.c
            )

find_library( log-lib
              log )

target_link_libraries( madsqlite-lib
                       ${log-lib} )
