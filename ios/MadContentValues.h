//
// Created by William Kamp on 11/17/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MadContentValues

- (instancetype)init;

- (void)putInteger:(NSString *)key withValue:(NSInteger)value;

- (void)putReal:(NSString *)key withValue:(NSNumber *)value;

- (void)putString:(NSString *)key withValue:(NSString *)value;

- (void)putBlob:(NSString *)key withValue:(NSData *)value;

- (void)clear;

@end

@interface MadContentValuesFactory : NSObject

+ (id <MadContentValues>)values;

@end
