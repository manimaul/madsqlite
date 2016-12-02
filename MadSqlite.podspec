#
# Be sure to run `pod lib lint MadSqlite.podspec' to ensure this is a
# valid spec before submitting. https://guides.cocoapods.org/making/getting-setup-with-trunk ->  'pod trunk push MadSqlite.podspec'
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name                   = 'MadSqlite'
  s.version                = '0.1.0'

  s.summary                = 'A simple Sqlite Abstraction'
  s.description            = 'A simple Sqlite Abstraction with FTS5 and R*Tree enabled'
  s.homepage               = 'https://manimaul.github.io/madsqlite/'
  s.license                = { :type => 'BSD', :file => 'LICENSE.md' }
  s.author                 = { 'William Kamp' => 'manimaul@gmail.com' }
  s.documentation_url      = 'https://manimaul.github.io/madsqlite/ios' 

  s.source                 = { :git => 'https://github.com/manimaul/madsqlite.git', :tag => s.version.to_s }

  s.ios.deployment_target  = '8.0'
  s.source_files           = 'ios/MadSqlite/Classes/**/*.{h,m,hh,mm}',
			     'madsqlite/src/main/cpp/*.{hpp}',
			     'madsqlite/src/main/cpp/ContentValues.cpp',
			     'madsqlite/src/main/cpp/Cursor.cpp',
			     'madsqlite/src/main/cpp/Database.cpp',
			     'madsqlite/src/main/cpp/Util.cpp',
			     'madsqlite/src/main/cpp/sqlite-amalgamation-3140200/sqlite3.c',
                             'madsqlite/src/main/cpp/*.{hpp}',
			     'madsqlite/src/main/cpp/sqlite-amalgamation-3140200/sqlite3.h'
  s.private_header_files   = 'madsqlite/src/main/cpp/*.{hpp}',
                             'ios/MadSqlite/Classes/**/*Impl.{hh}',
                             'madsqlite/src/main/cpp/sqlite-amalgamation-3140200/sqlite3.h'
  s.requires_arc           = true

  #s.library                = 'c++'
  s.xcconfig               = {
       'CLANG_CXX_LANGUAGE_STANDARD' => 'c++14',
       'CLANG_CXX_LIBRARY' => 'libc++'
  }
 
end
