//
// Created by William Kamp on 11/17/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MadContentValues.h"
#import "ContentValues.hpp"


@interface MadContentValuesImpl : NSObject <MadContentValues>

- (instancetype)init;

- (std::shared_ptr<ContentValues>)getValues;

@end
