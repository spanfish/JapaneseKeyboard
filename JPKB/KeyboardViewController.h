//
//  KeyboardViewController.h
//  JPKB
//
//  Created by kishikawa katsumi on 2014/09/28.
//  Copyright (c) 2014 kishikawa katsumi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EmailKeyboardView.h"
#import "NumberKeyboardView.h"
#import "JapaneseKeyboardView.h"
@interface KeyboardViewController : UIInputViewController<EmailKeyboardViewDelegate, NumberKeyboardViewDelegate, JapaneseKeyboardViewDelegate>

@end
