#!/usr/bin/env bash
jazzy --objc --clean --author Madrona --author_url https://madrona.io --github_url https://github.com/manimaul/madsqlite --umbrella-header MadSqlite/MadSqlite.h --framework-root . --module MadSqlite --output docs/objc_output
#jazzy --clean --author Madrona --author_url https://madrona.io --github_url https://github.com/manimaul/madsqlite --module MadSqlite --output docs/swift_output