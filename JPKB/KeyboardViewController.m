//
//  KeyboardViewController.m
//  JPKB
//
//  Created by kishikawa katsumi on 2014/09/28.
//  Copyright (c) 2014 kishikawa katsumi. All rights reserved.
//

#import "KeyboardViewController.h"
#import "KeyboardView.h"

@interface KeyboardViewController () <KeyboardViewDelegate>

@property (nonatomic) NSString *currentDocumentIdentifier;

@property (nonatomic) NSLayoutConstraint *leadingConstraint;
@property (nonatomic) NSLayoutConstraint *tailingConstraint;
@property (nonatomic) NSLayoutConstraint *heightConstraint;

@property (nonatomic) KeyboardView *keyboardView;

@end

@implementation KeyboardViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.inputView.translatesAutoresizingMaskIntoConstraints = NO;
    
    self.keyboardView = [[KeyboardView alloc] initWithFrame:self.inputView.bounds];
    self.keyboardView.translatesAutoresizingMaskIntoConstraints = NO;
    self.keyboardView.delegate = self;
    
    [self.inputView addSubview:self.keyboardView];
    
    [self.inputView addConstraints:@[
                                     [NSLayoutConstraint constraintWithItem:self.keyboardView
                                                                  attribute:NSLayoutAttributeLeading
                                                                  relatedBy:NSLayoutRelationEqual
                                                                     toItem:self.inputView
                                                                  attribute:NSLayoutAttributeLeading
                                                                 multiplier:1.0
                                                                   constant:0.0],
                                     [NSLayoutConstraint constraintWithItem:self.keyboardView
                                                                  attribute:NSLayoutAttributeTrailing
                                                                  relatedBy:NSLayoutRelationEqual
                                                                     toItem:self.inputView
                                                                  attribute:NSLayoutAttributeTrailing
                                                                 multiplier:1.0
                                                                   constant:0.0],
                                     [NSLayoutConstraint constraintWithItem:self.keyboardView
                                                                  attribute:NSLayoutAttributeTop
                                                                  relatedBy:NSLayoutRelationEqual
                                                                     toItem:self.inputView
                                                                  attribute:NSLayoutAttributeTop
                                                                 multiplier:1.0
                                                                   constant:0.0],
                                     [NSLayoutConstraint constraintWithItem:self.keyboardView
                                                                  attribute:NSLayoutAttributeBottom
                                                                  relatedBy:NSLayoutRelationEqual
                                                                     toItem:self.inputView
                                                                  attribute:NSLayoutAttributeBottom
                                                                 multiplier:1.0
                                                                   constant:0.0]
                                     ]];
}

-(void) updateViewConstraints {
    if(!self.leadingConstraint && self.inputView.superview) {
        self.leadingConstraint = [NSLayoutConstraint constraintWithItem:self.inputView
                                                            attribute:NSLayoutAttributeLeading
                                                            relatedBy:NSLayoutRelationEqual
                                                               toItem:self.inputView.superview
                                                            attribute:NSLayoutAttributeLeading
                                                           multiplier:1.0
                                                             constant:0.0];
        [self.inputView.superview addConstraint:self.leadingConstraint];
    }
    
    if(!self.tailingConstraint && self.inputView.superview) {
        self.tailingConstraint = [NSLayoutConstraint constraintWithItem:self.inputView
                                                            attribute:NSLayoutAttributeTrailing
                                                            relatedBy:NSLayoutRelationEqual
                                                               toItem:self.inputView.superview
                                                            attribute:NSLayoutAttributeTrailing
                                                           multiplier:1.0
                                                             constant:0.0];
        [self.inputView.superview addConstraint:self.tailingConstraint];
    }
    
    if(!self.heightConstraint && self.inputView.superview) {
        self.heightConstraint = [NSLayoutConstraint constraintWithItem:self.inputView
                                                             attribute:NSLayoutAttributeHeight
                                                             relatedBy:NSLayoutRelationEqual
                                                                toItem:nil
                                                             attribute:NSLayoutAttributeNotAnAttribute
                                                            multiplier:0.0
                                                              constant:65 * 4 + 100];
        [self.inputView addConstraint:self.heightConstraint];
    }
    
    [super updateViewConstraints];
}
#pragma mark -

- (void)textWillChange:(id<UITextInput>)textInput {
    
}

- (void)textDidChange:(id<UITextInput>)textInput {
    NSLog(@"Keyboard-keyboardType:%ld", self.textDocumentProxy.keyboardType);
    
    BOOL changed = YES;
    if([self.textDocumentProxy respondsToSelector:@selector(documentIdentifier)]) {
        NSString *UUIDString = [self.textDocumentProxy.documentIdentifier UUIDString];
        changed = ![self.currentDocumentIdentifier isEqualToString:UUIDString];
        if(changed) {
            self.currentDocumentIdentifier = UUIDString;
        }
    }
    
    if(changed) {
        //change keyboard
        switch (self.textDocumentProxy.keyboardType) {
            case UIKeyboardTypePhonePad:
                [self.keyboardView setInputMode:KeyboardInputModePhone];
                break;
            case UIKeyboardTypeNumberPad:
            case UIKeyboardTypeNumbersAndPunctuation:
                [self.keyboardView setInputMode:KeyboardInputModeNumber];
                break;
            case UIKeyboardTypeEmailAddress:
                [self.keyboardView setInputMode:KeyboardInputModeEmail];
                break;
            default:
                [self.keyboardView setInputMode:KeyboardInputModeKana];
                break;
        }
    }
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
