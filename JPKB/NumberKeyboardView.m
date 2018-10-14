//
//  NumberKeyboardView.m
//  JapaneseIME
//
//  Created by xwang on 10/5/18.
//  Copyright © 2018 kishikawa katsumi. All rights reserved.
//

#import "NumberKeyboardView.h"

@implementation NumberKeyboardView

-(id) initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
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

-(void) commonInit {
    
    UINib *nib = [UINib nibWithNibName:@"NumberKeyboardView" bundle:nil];
    
    UIView *view = [[nib instantiateWithOwner:self options:nil] firstObject];
    self.translatesAutoresizingMaskIntoConstraints = NO;
    view.translatesAutoresizingMaskIntoConstraints = NO;
    [self addSubview:view];
    
    NSLayoutConstraint *leftSideConstraint = [NSLayoutConstraint constraintWithItem: view attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0.0];
    NSLayoutConstraint *rightSideConstraint = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeRight multiplier:1.0 constant:0.0];
    NSLayoutConstraint *bottomConstraint = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0.0];
    NSLayoutConstraint *topConstraint = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeTop multiplier:1.0 constant:0.0];
    
    [self addConstraints:@[leftSideConstraint, rightSideConstraint, bottomConstraint, topConstraint]];
    
    view.backgroundColor = [UIColor colorWithWhite:0.784 alpha:1.000];
    for (UIButton *button in view.subviews) {
        [button addTarget:self action:@selector(keyTouched:) forControlEvents:UIControlEventTouchDown];
    }
}

-(IBAction)keyTouched:(id)sender {
    UIButton *button = sender;
    if(button.tag == 1) {
        //Del button
        if([self.delegate respondsToSelector:@selector(emailKeyboardViewDidInputDelete)]) {
            [self.delegate numberKeyboardViewDidInputDelete];
        }
    } else {
        if([self.delegate respondsToSelector:@selector(emailKeyboardViewDidTyped:)]) {
            NSString *key = [button titleForState:UIControlStateNormal];
            [self.delegate numberKeyboardViewDidTyped:key];
        }
    }
}

@end
