//
//  MadQuery.h
//  MadSqlite
//
//  Created by William Kamp on 11/16/16.
//  Copyright © 2016 William Kamp. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MadQuery

@required

-(BOOL) moveToFirst;
-(BOOL) moveToNext;
-(BOOL) isAfterLast;
-(NSString *) getString:(NSInteger)columnIndex;
-(NSData *) getBlob:(NSInteger)columnIndex;
-(NSInteger) getInt:(NSInteger)columnIndex;
-(NSNumber *) getReal:(NSInteger)columnIndex;

@end
