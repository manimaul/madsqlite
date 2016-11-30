//
// Created by William Kamp on 11/24/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MadContentValues;
@protocol MadDatabase;


@interface MadSqliteFactory : NSObject

/**
 * @return a new content-value container useful for inserting into a @see MadDatabase#insert: withValues:
 */
+ (id <MadContentValues>)contentValues;

/**
 * @return a new in-memory sqlite database.
 */
+ (id <MadDatabase>)inMemoryDatabase;

/**
 * Opens or creates a file system sqlite database.
 *
 * @param name the name of the database
 * @return a file system sqlite database
 */
+ (id <MadDatabase>)databaseNamed:(NSString *)name;

@end