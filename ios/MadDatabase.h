//
// Created by William Kamp on 11/24/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MadQuery;
@protocol MadContentValues;

@protocol MadDatabase <NSObject>

- (BOOL)insert:(NSString *)table withValues:(id <MadContentValues>)values;

- (id <MadQuery>)query:(NSString *)sql;

- (id <MadQuery>)query:(NSString *)sql withArgs:(NSArray<NSString *> *)args;

- (NSInteger)exec:(NSString *)sql;

- (NSString *)getError;

- (void)beginTransaction;

- (void)rollbackTransaction;

- (void)endTransaction;

@end