//
//  KeyboardButton.m
//  JapaneseKeyboardKit
//
//  Created by kishikawa katsumi on 2014/09/28.
//  Copyright (c) 2014 kishikawa katsumi. All rights reserved.
//

#import "KeyboardButton.h"

@implementation KeyboardButton
-(id) init {
    self = [super init];
    if(self) {
        [self commonInit];
    }
    return self;
}

-(id) initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if(self) {
        [self commonInit];
    }
    return self;
}

-(id) initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if(self) {
        [self commonInit];
    }
    return self;
}


-(void) commonInit {
}

- (CGRect)backgroundRectForBounds:(CGRect)bounds
{
    return CGRectInset(bounds, 6.0, 6.0);
}

-(BOOL) isNumberButton {
    NSString *title = [self titleForState:UIControlStateNormal];
    NSScanner *scanner = [NSScanner scannerWithString:title];
    return [scanner scanInt:NULL];
}
@end
