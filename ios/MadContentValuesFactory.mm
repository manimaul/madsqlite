//
//  MadContentValuesFactory.m
//  MadSqlite
//
//  Created by William Kamp on 11/22/16.
//  Copyright © 2016 William Kamp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MadContentValues.h"
#import "MadContentValuesImpl.hh"

@implementation MadContentValuesFactory

+ (id <MadContentValues>)values {
    MadContentValuesImpl *values = [[MadContentValuesImpl alloc] init];
    return (id <MadContentValues>) values;
}

@end
