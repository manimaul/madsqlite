//
// Created by William Kamp on 11/16/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//

#import "MadDatabase.h"
#include "Database.h"
#import "MadContentValues.h"
#import "MadContentValuesImpl.h"
#import "MadQueryImpl.h"

@implementation MadDatabase

std::shared_ptr<Database> database;

- (instancetype)init {
    if (self = [super init]) {
        database = std::make_shared<Database>();
        return self;
    } else {
        return nil;
    }
}

- (instancetype)initWithPath:(NSString *)path {
    if (self = [super init]) {
        database = std::make_shared<Database>(path.UTF8String);
        return self;
    } else {
        return nil;
    }
}

- (BOOL)insert:(NSString *)table withValues:(id <MadContentValues>)values {
    MadContentValuesImpl *impl = (MadContentValuesImpl *)values;
    return database->insert(table.UTF8String, *impl.getValues);
}

- (id <MadQuery>)query:(NSString *)sql {
    auto c = database->query(sql.UTF8String);
    MadQueryImpl *impl = [[MadQueryImpl alloc] initWithCursor:c];
    return impl;
}

- (id <MadQuery>)query:(NSString *)sql withArgs:(NSArray<NSString *> *)args {
    auto vec = std::vector<std::string>();
    for (NSString *arg in args) {
        vec.push_back(arg.UTF8String);
    }
    auto c = database->query(sql.UTF8String, vec);
    MadQueryImpl *impl = [[MadQueryImpl alloc] initWithCursor:c];
    return impl;
}

- (NSInteger)exec:(NSString *)sql {
    return database->exec(sql.UTF8String);
}

- (NSString *)getError {
    std::string err = database->getError();
    if (err.length()) {
        return [NSString stringWithUTF8String:err.c_str()];
    } else {
        return nil;
    }
}

- (void)beginTransaction {
    database->beginTransaction();
}

- (void)rollbackTransaction {
    database->rollbackTransaction();
}

- (void)endTransaction {
    database->endTransaction();
}

- (void)dealloc {
    //?
}

@end
