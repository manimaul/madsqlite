//
// Created by William Kamp on 11/24/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//

#import "MadSqliteFactory.hh"
#import "MadContentValues.h"
#import "MadContentValuesImpl.hh"
#import "MadDatabase.h"
#import "MadDatabaseImpl.hh"


@implementation MadSqliteFactory

+ (id <MadContentValues>)contentValues {
    MadContentValuesImpl *values = [[MadContentValuesImpl alloc] init];
    return (id <MadContentValues>) values;
}

+ (id <MadDatabase>)inMemoryDatabase {
    MadDatabaseImpl *db = [[MadDatabaseImpl alloc] init];
    return (id <MadDatabase>) db;
}

+ (id <MadDatabase>)databaseNamed:(NSString *)name {
    return nil;
}


@end