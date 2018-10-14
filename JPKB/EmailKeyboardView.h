//
//  EmailKeyboardView.h
//  Coach日本語入力
//
//  Created by xwang on 10/5/18.
//  Copyright © 2018 kishikawa katsumi. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol EmailKeyboardViewDelegate<NSObject>

-(void) emailKeyboardViewDidTyped:(NSString *) key;
- (void)emailKeyboardViewDidInputDelete;
@end

@interface EmailKeyboardView : UIView

@property(nonatomic, weak) id<EmailKeyboardViewDelegate> delegate;
@end
