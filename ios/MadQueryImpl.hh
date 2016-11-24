//
// Created by William Kamp on 11/16/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MadQueryImpl.hh"
#import "MadQuery.hh"
#include "Cursor.hpp"

@interface MadQueryImpl : NSObject <MadQuery>

-(instancetype) initWithCursor:(Cursor &)cursor;

@end
