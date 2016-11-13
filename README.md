[![Build Status](https://api.travis-ci.org/manimaul/madsqlite.png?branch=master)](https://travis-ci.org/manimaul/madsqlite)

#MadSqlite

MadSqlite is:
 * A simple C++14 wrapper around [Sqlite](https://www.sqlite.org/)
 * An Android library and JNI Java bridge wrapper
  
Why:
 * We needed Sqlite with a [customized build configuration](https://www.sqlite.org/compile.html) such as 
 (FTS4, FTS5, R*Tree) that was not available in the Android SDK
 
Status:
 * Beta