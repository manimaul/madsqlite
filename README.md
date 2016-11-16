[![Build Status](https://travis-ci.org/manimaul/madsqlite.svg?branch=master)](https://travis-ci.org/manimaul/madsqlite)

#MadSqlite

MadSqlite is:
 * A simple C++14 wrapper around [Sqlite](https://www.sqlite.org/)
 * An Android library and JNI Java bridge wrapper
  
Why:
 * We needed Sqlite with a [customized build configuration](https://www.sqlite.org/compile.html) such as 
 (FTS5, R*Tree, Json) that was not available in the Android SDK
 
Status:
 * Alpha