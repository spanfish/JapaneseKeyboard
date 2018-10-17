//
//  KeyboardButton.h
//  JapaneseKeyboardKit
//
//  Created by kishikawa katsumi on 2014/09/28.
//  Copyright (c) 2014 kishikawa katsumi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

IB_DESIGNABLE
@interface KeyboardButton : UIButton {
    
}

+(id) buttonWithType:(UIButtonType) type insect:(CGSize) size;
@property (nonatomic) NSUInteger keyIndex;
@property (nonatomic) CGSize inset;
@end
