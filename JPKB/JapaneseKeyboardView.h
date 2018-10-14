//
//  JapaneseKeyboardView.h
//  Coach日本語入力
//
//  Created by xwang on 10/5/18.
//  Copyright © 2018 kishikawa katsumi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HandWritingController.h"
#import "KeyboardCandidateBar.h"
#import "InputManager.h"

#define KEY_WIDTH 66
#define KEY_H_SEP 4
#define KEY_V_SEP 2
const CGFloat MarkedTextLabelHeightDefault = 20.0;
const CGFloat AccessoryViewHeightDefault = 60.0;

@protocol JapaneseKeyboardViewDelegate

-(void) nextIME;
-(void) keyboardViewDidInputDelete;
-(void) keyboardViewDidAcceptCandidate:(NSString *) can;
- (void)keyboardViewDidInputReturn;
@end

@interface JapaneseKeyboardView : UIView<HandWritingControllerDelegate, KeyboardCandidateBarDelegate, InputManagerDelegate>

@property(nonatomic, weak) id<JapaneseKeyboardViewDelegate> delegate;
-(void) updateLayout;
@end
