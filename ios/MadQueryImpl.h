//
// Created by William Kamp on 11/16/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MadQueryImpl.h"
#import "MadQuery.h"
#include "Cursor.h"

@interface MadQueryImpl : NSObject <MadQuery>

-(instancetype) initWithCursor:(Cursor &)cursor;

@end
