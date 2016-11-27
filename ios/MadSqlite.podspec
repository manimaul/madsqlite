Pod::Spec.new do |s|

  s.name         = "MadSqlite"
  s.version      = "0.0.1"
  s.summary      = "A simple sqlite abstraction with FTS5 and RTree enabled."
  s.description  = "Easy sqlite with FTS5 and RTree" 

  s.homepage     = "https://github.com/manimaul/madsqlite"
  s.license      = "BSD"
  s.author       = { "Will Kamp" => "manimaul@gmail.com" }
  s.platform     = :ios, "10.0"

  #s.source        = { :path => '.' }
  s.source        = { :git => 'https://github.com/manimaul/madsqlite.git', :tag => s.version.to_s }
  s.source_files  = "MadSqlite/**/*.{h,hh,m,mm,swift}"
  s.exclude_files = 'MadSqlite/**/*Spec.swift'

  #s.dependency 'RxSwift', '~> 3.0.0-beta.2'
end
