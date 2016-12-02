//
// Created by William Kamp on 11/16/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MadQueryImpl.hh"
#import "MadQuery.h"
#include "Cursor.hpp"

@interface MADQueryImpl : NSObject <MADQuery>

-(instancetype) initWithCursor:(Cursor &)cursor;

@end
