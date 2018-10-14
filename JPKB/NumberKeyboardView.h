//
//  NumberKeyboardView.h
//  JapaneseIME
//
//  Created by xwang on 10/5/18.
//  Copyright © 2018 kishikawa katsumi. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol NumberKeyboardViewDelegate<NSObject>

-(void) numberKeyboardViewDidTyped:(NSString *) key;
- (void)numberKeyboardViewDidInputDelete;
@end

@interface NumberKeyboardView : UIView

-(id) initWithFrame:(CGRect)frame;
@property(nonatomic, weak) id<NumberKeyboardViewDelegate> delegate;
@end
