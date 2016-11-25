//
// Created by William Kamp on 11/24/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MadContentValues;
@protocol MadDatabase;


@interface MadSqliteFactory : NSObject

+ (id <MadContentValues>)values;
+ (id <MadDatabase>)inMemoryDatabase;
+ (id <MadDatabase>)databaseNamed:(NSString *)name;

@end