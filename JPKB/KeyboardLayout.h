//
//  KeyboardLayout.h
//  JapaneseKeyboardKit
//
//  Created by kishikawa katsumi on 2014/09/28.
//  Copyright (c) 2014 kishikawa katsumi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, KeyboardMetrics) {
    KeyboardMetricsDefault,
    KeyboardMetricsLandscape,
    KeyboardMetricsLandscape568,
};

typedef NS_ENUM(NSUInteger, KeyboardButtonIndex) {
    KeyboardButtonIndexNextKeyboard = 40,
    KeyboardButtonIndexToggleInputMode,
    KeyboardButtonIndexShift,
    KeyboardButtonIndexSpace,
    KeyboardButtonIndexComma,
    KeyboardButtonIndexPeriod,
    KeyboardButtonIndexDelete,
    KeyboardButtonIndexReturn,
    KeyboardButtonIndexDismiss,
    KeyboardButtonIndexPreviousCandidate,
    KeyboardButtonIndexNextCandidate,
    KeyboardButtonIndexPreviousCursor,
    KeyboardButtonIndexNextCursor,
    KeyboardButtonIndexHandwriting,
    KeyboardButtonIndexHandwritingClear,
    KeyboardButtonIndexHandwritingUndo
};

typedef NS_ENUM(NSInteger, KeyboardInputMode) {
    KeyboardInputModeKana,
    KeyboardInputModeAlphabet,
    KeyboardInputModeNumberPunctual,
    KeyboardInputModeSymbol,
    KeyboardInputModeNumber,
    KeyboardInputModeEmail,
    KeyboardInputModeKataKana,
    KeyboardInputModeHandWriting
};

@class KeyboardButton;


@protocol KeyboardLayoutDelegate<NSObject>
-(void)buttonDidTouchDown:(KeyboardButton *)button event:(UIEvent *) event;
-(void)buttonDidCreated:(KeyboardButton *) button;
@end

@interface KeyboardLayout : NSObject

@property (nonatomic) KeyboardMetrics metrics;
@property (nonatomic) KeyboardInputMode inputMode;

@property (nonatomic) BOOL shifted;
@property (nonatomic) BOOL shiftLocked;

@property (nonatomic, weak) id<KeyboardLayoutDelegate> delegate;
- (instancetype)initWithDelegate:(id) delegate;

+ (KeyboardLayout *)keyboardLayout;
- (void)setupKeyboardButtonsWithView:(UIView *)view;

@end

@interface KeyboardLayoutPhone5 : KeyboardLayout

@end

@interface KeyboardLayoutPhone6 : KeyboardLayout

@end

@interface KeyboardLayoutPhone6Plus : KeyboardLayout

@end

@interface KeyboardLayoutiPad : KeyboardLayout

@end
