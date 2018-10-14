//
//  KeyboardViewController.m
//  JPKB
//
//  Created by kishikawa katsumi on 2014/09/28.
//  Copyright (c) 2014 kishikawa katsumi. All rights reserved.
//

#import "KeyboardViewController.h"
#import "KeyboardView.h"
#import "NumberKeyboardView.h"
#import "JapaneseKeyboardView.h"
#import "EmailKeyboardView.h"

@interface KeyboardViewController () <KeyboardViewDelegate>

@property (nonatomic) NSString *currentDocumentIdentifier;
@property (nonatomic) NSLayoutConstraint *widthConstraint;
@property (nonatomic) NSLayoutConstraint *heightConstraint;
@property (nonatomic) NSLayoutConstraint *leftSideConstraint;
@property (nonatomic) NSLayoutConstraint *rightSideConstraint;
@property (nonatomic) NSLayoutConstraint *topSideConstraint;
@property (nonatomic) NSLayoutConstraint *bottomSideConstraint;

@property (nonatomic) UIView *currentKeyboardView;
@property (nonatomic) JapaneseKeyboardView *japaneseKeyboardView;
@property (nonatomic) NumberKeyboardView *numberKeyboardView;
@property (nonatomic) EmailKeyboardView *emailKeyboardView;

@property (nonatomic) KeyboardView *keyboardView;

@end

@implementation KeyboardViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.inputView.translatesAutoresizingMaskIntoConstraints = NO;
    
    self.keyboardView = [[KeyboardView alloc] initWithFrame:self.inputView.bounds];
    self.keyboardView.translatesAutoresizingMaskIntoConstraints = NO;
    self.keyboardView.delegate = self;
    
    [self.inputView addSubview:self.keyboardView];
    
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];

    [self.inputView.superview addConstraint:[NSLayoutConstraint constraintWithItem:self.inputView
                                                                    attribute:NSLayoutAttributeLeading
                                                                    relatedBy:NSLayoutRelationEqual
                                                                       toItem:self.inputView.superview
                                                                    attribute:NSLayoutAttributeLeading
                                                                   multiplier:1.0
                                                                     constant:0.0]];

    [self.inputView.superview addConstraint:[NSLayoutConstraint constraintWithItem:self.inputView
                                                                    attribute:NSLayoutAttributeTrailing
                                                                    relatedBy:NSLayoutRelationEqual
                                                                       toItem:self.inputView.superview
                                                                    attribute:NSLayoutAttributeTrailing
                                                                   multiplier:1.0
                                                                     constant:0.0]];

    CGFloat height = CGRectGetHeight(self.inputView.bounds);
    self.heightConstraint = [NSLayoutConstraint constraintWithItem:self.inputView
                                                         attribute:NSLayoutAttributeHeight
                                                         relatedBy:NSLayoutRelationEqual
                                                            toItem:nil
                                                         attribute:NSLayoutAttributeNotAnAttribute
                                                        multiplier:0.0
                                                          constant:height + 44.0];
    [self.inputView addConstraint:self.heightConstraint];

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark -

- (void)textWillChange:(id<UITextInput>)textInput
{
    
}

- (void)textDidChange:(id<UITextInput>)textInput
{
    NSLog(@"Coach Keyboard-documentIdentifier:%@, keyboardType:%ld", self.textDocumentProxy.documentIdentifier, self.textDocumentProxy.keyboardType);
    
    NSString *UUIDString = [self.textDocumentProxy.documentIdentifier UUIDString];
    if(![self.currentDocumentIdentifier isEqualToString:UUIDString]) {
        self.currentDocumentIdentifier = UUIDString;
        //change keyboard
        switch (self.textDocumentProxy.keyboardType) {
            case UIKeyboardTypeNumberPad:
            case UIKeyboardTypePhonePad:
            case UIKeyboardTypeNumbersAndPunctuation:
                [self showNumberKeyboard];
                break;
            case UIKeyboardTypeEmailAddress:
                [self showEmailKeyboard];
                break;
            default:
                [self.keyboardView setInputMode:KeyboardInputModeKana];
                break;
        }
    }
}

-(void) showJapaneseKeyboard {
    NSLog(@"Coach Keyboard-Japanese");
    if([self.currentKeyboardView isKindOfClass:[JapaneseKeyboardView class]]) {
        return;
    } else {
        if(self.leftSideConstraint != nil) {
            [self.inputView removeConstraint:self.leftSideConstraint];
        }
        if(self.rightSideConstraint != nil) {
            [self.inputView removeConstraint:self.rightSideConstraint];
        }
        if(self.topSideConstraint != nil) {
            [self.inputView removeConstraint:self.topSideConstraint];
        }
        if(self.bottomSideConstraint != nil) {
            [self.inputView removeConstraint:self.bottomSideConstraint];
        }
        [self.currentKeyboardView removeFromSuperview];
        self.leftSideConstraint = self.rightSideConstraint = self.topSideConstraint = self.bottomSideConstraint = nil;
    }
    
    if(self.japaneseKeyboardView == nil) {
        self.japaneseKeyboardView = [[JapaneseKeyboardView alloc] initWithFrame:self.inputView.bounds];
        self.japaneseKeyboardView.delegate = self;
    }
    self.currentKeyboardView = self.japaneseKeyboardView;
    [self.inputView addSubview: self.japaneseKeyboardView];
    
    self.leftSideConstraint = [NSLayoutConstraint constraintWithItem: self.japaneseKeyboardView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0.0];
    self.rightSideConstraint = [NSLayoutConstraint constraintWithItem:self.japaneseKeyboardView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeRight multiplier:1.0 constant:0.0];
    self.bottomSideConstraint = [NSLayoutConstraint constraintWithItem:self.japaneseKeyboardView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0.0];
    self.topSideConstraint = [NSLayoutConstraint constraintWithItem:self.japaneseKeyboardView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0.0];
    
    [self.inputView addConstraints:@[self.leftSideConstraint, self.rightSideConstraint, self.bottomSideConstraint, self.topSideConstraint]];
    
    if (self.heightConstraint) {
        [self.inputView removeConstraints:@[self.heightConstraint]];
    }
    
    self.heightConstraint = [NSLayoutConstraint constraintWithItem:self.inputView
                                                         attribute:NSLayoutAttributeHeight
                                                         relatedBy:NSLayoutRelationEqual
                                                            toItem:nil
                                                         attribute:NSLayoutAttributeNotAnAttribute
                                                        multiplier:0.0
                                                          constant:KEY_WIDTH * 4 + KEY_V_SEP * 4 + AccessoryViewHeightDefault];
    [self.inputView addConstraint:self.heightConstraint];
    
    [self.japaneseKeyboardView updateLayout];
}

-(void) showEmailKeyboard {
    NSLog(@"Coach Keyboard-Email");
    if([self.currentKeyboardView isKindOfClass:[EmailKeyboardView class]]) {
        return;
    } else {
        if(self.leftSideConstraint != nil) {
            [self.inputView removeConstraint:self.leftSideConstraint];
        }
        if(self.rightSideConstraint != nil) {
            [self.inputView removeConstraint:self.rightSideConstraint];
        }
        if(self.topSideConstraint != nil) {
            [self.inputView removeConstraint:self.topSideConstraint];
        }
        if(self.bottomSideConstraint != nil) {
            [self.inputView removeConstraint:self.bottomSideConstraint];
        }
        [self.currentKeyboardView removeFromSuperview];
        self.leftSideConstraint = self.rightSideConstraint = self.topSideConstraint = self.bottomSideConstraint = nil;
    }
    
    if(self.emailKeyboardView == nil) {
        self.emailKeyboardView = [[EmailKeyboardView alloc] initWithFrame:self.inputView.bounds];
        self.emailKeyboardView.delegate = self;
    }
    self.currentKeyboardView = self.emailKeyboardView;
    [self.inputView addSubview: self.emailKeyboardView];

    self.leftSideConstraint = [NSLayoutConstraint constraintWithItem: self.emailKeyboardView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0.0];
    self.rightSideConstraint = [NSLayoutConstraint constraintWithItem:self.emailKeyboardView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeRight multiplier:1.0 constant:0.0];
    self.bottomSideConstraint = [NSLayoutConstraint constraintWithItem:self.emailKeyboardView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0.0];
    self.topSideConstraint = [NSLayoutConstraint constraintWithItem:self.emailKeyboardView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0.0];

    [self.inputView addConstraints:@[self.leftSideConstraint, self.rightSideConstraint, self.bottomSideConstraint, self.topSideConstraint]];
    
    if (self.heightConstraint) {
        [self.inputView removeConstraints:@[self.heightConstraint]];
    }
    
    self.heightConstraint = [NSLayoutConstraint constraintWithItem:self.inputView
                                                         attribute:NSLayoutAttributeHeight
                                                         relatedBy:NSLayoutRelationEqual
                                                            toItem:nil
                                                         attribute:NSLayoutAttributeNotAnAttribute
                                                        multiplier:0.0
                                                          constant:65 * 5 + 4];
    [self.inputView addConstraint:self.heightConstraint];
}

-(void) showNumberKeyboard {
    NSLog(@"Coach Keyboard-Number");
    
    if([self.currentKeyboardView isKindOfClass:[NumberKeyboardView class]]) {
        return;
    } else {
        if(self.leftSideConstraint != nil) {
            [self.inputView removeConstraint:self.leftSideConstraint];
        }
        if(self.rightSideConstraint != nil) {
            [self.inputView removeConstraint:self.rightSideConstraint];
        }
        if(self.topSideConstraint != nil) {
            [self.inputView removeConstraint:self.topSideConstraint];
        }
        if(self.bottomSideConstraint != nil) {
            [self.inputView removeConstraint:self.bottomSideConstraint];
        }
        [self.currentKeyboardView removeFromSuperview];
        self.leftSideConstraint = self.rightSideConstraint = self.topSideConstraint = self.bottomSideConstraint = nil;
    }
    
    if(self.numberKeyboardView == nil) {
        self.numberKeyboardView = [[NumberKeyboardView alloc] initWithFrame:self.inputView.bounds];
        self.numberKeyboardView.delegate = self;
    }
    self.currentKeyboardView = self.numberKeyboardView;
    [self.inputView addSubview: self.numberKeyboardView];
    
    self.leftSideConstraint = [NSLayoutConstraint constraintWithItem: self.numberKeyboardView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0.0];
    self.rightSideConstraint = [NSLayoutConstraint constraintWithItem:self.numberKeyboardView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeRight multiplier:1.0 constant:0.0];
    self.bottomSideConstraint = [NSLayoutConstraint constraintWithItem:self.numberKeyboardView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0.0];
    self.topSideConstraint = [NSLayoutConstraint constraintWithItem:self.numberKeyboardView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0.0];
    
    [self.inputView addConstraints:@[self.leftSideConstraint, self.rightSideConstraint, self.bottomSideConstraint, self.topSideConstraint]];
    
    if (self.heightConstraint) {
        [self.inputView removeConstraints:@[self.heightConstraint]];
    }
    
    self.heightConstraint = [NSLayoutConstraint constraintWithItem:self.inputView
                                                         attribute:NSLayoutAttributeHeight
                                                         relatedBy:NSLayoutRelationEqual
                                                            toItem:nil
                                                         attribute:NSLayoutAttributeNotAnAttribute
                                                        multiplier:0.0
                                                          constant:76 * 4 + 24 + 4];
    [self.inputView addConstraint:self.heightConstraint];
}

-(void) addViewConstraints {
    NSLayoutConstraint *leftSideConstraint = [NSLayoutConstraint constraintWithItem: self.currentKeyboardView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0.0];
    NSLayoutConstraint *rightSideConstraint = [NSLayoutConstraint constraintWithItem:self.currentKeyboardView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeRight multiplier:1.0 constant:0.0];
    NSLayoutConstraint *bottomConstraint = [NSLayoutConstraint constraintWithItem:self.currentKeyboardView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0.0];
    NSLayoutConstraint *topConstraint = [NSLayoutConstraint constraintWithItem:self.currentKeyboardView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.inputView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0.0];
    
    [self.inputView addConstraints:@[leftSideConstraint, rightSideConstraint, bottomConstraint, topConstraint]];
}
#pragma mark -

- (void)keyboardViewShouldAdvanceToNextInputMode:(KeyboardView *)keyboardView
{
    [self advanceToNextInputMode];
}

- (void)keyboardViewShouldDismiss:(KeyboardView *)keyboardView
{
    [self dismissKeyboard];
}

- (void)keyboardViewDidInputDelete:(KeyboardView *)keyboardView
{
    [self.textDocumentProxy deleteBackward];
}

- (void)keyboardViewDidInputReturn:(KeyboardView *)keyboardView
{
    [self.textDocumentProxy insertText:@"\n"];
}

- (void)keyboardViewBackCursor:(KeyboardView *)keyboardView
{
    [self.textDocumentProxy adjustTextPositionByCharacterOffset:-1];
}

- (void)keyboardViewForwardCursor:(KeyboardView *)keyboardView
{
    [self.textDocumentProxy adjustTextPositionByCharacterOffset:1];
}

- (void)keyboardView:(KeyboardView *)keyboardView didAcceptCandidate:(NSString *)candidate
{
    [self.textDocumentProxy insertText:candidate];
}

- (void)keyboardView:(KeyboardView *)keyboardView didChangedMarkedText:(NSString *) markedText {
    //[self.textDocumentProxy set];
}


#pragma mark - Email keyboard delegate
//email keyboard
-(void) emailKeyboardViewDidTyped:(NSString *) key {
    [self.textDocumentProxy insertText:key];
}
-(void) emailKeyboardViewDidInputDelete {
    [self.textDocumentProxy deleteBackward];
}

//Number keyboard
#pragma mark - Number keyboard delegate
-(void) numberKeyboardViewDidTyped:(NSString *) key {
    [self.textDocumentProxy insertText:key];
}

- (void)numberKeyboardViewDidInputDelete {
    [self.textDocumentProxy deleteBackward];
}

#pragma mark - Japanese keyboard delegate
-(void) keyboardViewDidInputDelete {
    [self.textDocumentProxy deleteBackward];
}

- (void)keyboardViewDidAcceptCandidate:(NSString *)candidate {
    [self.textDocumentProxy insertText:candidate];
}

- (void)keyboardViewDidInputReturn
{
    [self.textDocumentProxy insertText:@"\n"];
}
@end
