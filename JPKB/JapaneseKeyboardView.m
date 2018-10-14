//
//  JapaneseKeyboardView.m
//  Coach日本語入力
//
//  Created by xwang on 10/5/18.
//  Copyright © 2018 kishikawa katsumi. All rights reserved.
//

#import "JapaneseKeyboardView.h"
#import "KeyboardButton.h"
#import "DrawView.h"
#import "HandWritingController.h"

#import "KeyboardCandidateBar.h"
#import "KanaInputEngine.h"
#import "InputManager.h"
#import "InputCandidate.h"

typedef NS_ENUM(NSUInteger, ButtonLayout) {
    ButtonLayoutDefault = 0,
    ButtonLayoutNumberPunctual,
    ButtonLayoutMoreSign,
    ButtonLayoutHandwriting
};

@interface JapaneseKeyboardView() {
    BOOL _shiftOn;
    ButtonLayout _buttonLayout;
    DrawView *_drawView;
    HandWritingController *_handwritingController;
    
    KeyboardButton *_returnButton;
}
@property (nonatomic) KanaInputEngine *inputEngine;
@property (nonatomic) InputManager *inputManager;

@property (nonatomic) NSString *markedText;
@property (nonatomic) UILabel *markedTextLabel;
@property (nonatomic) KeyboardCandidateBar *candidateBar;
@end

@implementation JapaneseKeyboardView

-(id) initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if(self) {
        [self commonInit];
    }
    return self;
}

-(void) commonInit {
    self.translatesAutoresizingMaskIntoConstraints = NO;
    self.backgroundColor = [UIColor colorWithWhite:0.784 alpha:1.000];
    _shiftOn = NO;
    _buttonLayout = ButtonLayoutDefault;
}

-(void) updateLayout {
    for (UIView *view in self.subviews) {
        if([view isKindOfClass:[KeyboardButton class]] || [view isKindOfClass:[DrawView class]]) {
            [view removeFromSuperview];
        }
    }
    
    switch(_buttonLayout) {
        case ButtonLayoutNumberPunctual:
            [self buildNumberPunctualLayout];
            break;
        case ButtonLayoutMoreSign:
            [self buildMoreSignLayout];
            break;
        case ButtonLayoutHandwriting:
            [self buildHandwritingLayout];
            break;
        default:
            [self buildDefaultLayout];
            break;
    }
}


#pragma mark - Create Button Layout
-(void) buildHandwritingLayout {
    NSUInteger left = 2;
    NSUInteger top = AccessoryViewHeightDefault;
    //QWERTY button
    UIButton *button = [self darkgrayButtonWithTitle:@"あいう" image: nil];
    [button addTarget:self action:@selector(handleNumAlphButton:) forControlEvents:UIControlEventTouchDown];
    [button setFrame:CGRectMake(left, self.frame.size.height - AccessoryViewHeightDefault - 2, KEY_WIDTH, KEY_WIDTH)];
    [self addSubview:button];
    
    //Draw view
    CGFloat width = [UIScreen mainScreen].bounds.size.width;
    _drawView = [[DrawView alloc] initWithFrame:CGRectMake(KEY_WIDTH, top, width - 65 - 65, self.frame.size.height - AccessoryViewHeightDefault)];
    left = CGRectGetMaxX(_drawView.frame);
    [self addSubview:_drawView];
    
    //Back button
//    button = [self darkgrayButtonWithTitle:@"あいう" image: nil];
//    [button addTarget:self action:@selector(handleNumAlphButton:) forControlEvents:UIControlEventTouchDown];
//    [button setFrame:CGRectMake(left, top, KEY_WIDTH, KEY_WIDTH)];
//    [self addSubview:button];
    
    //Handwriting clear button
    button = [self darkgrayButtonWithTitle:@"手書クリア" image: nil];
    [button setFrame:CGRectMake(left, self.frame.size.height - AccessoryViewHeightDefault - 2, KEY_WIDTH, KEY_WIDTH)];
    [self addSubview:button];
    [button addTarget:self action:@selector(handleHandwritingClearButton:) forControlEvents:UIControlEventTouchDown];
    
    _handwritingController = [[HandWritingController alloc] init];
    
    BOOL result = [_handwritingController HandsInkInitialize];
    NSAssert(result, @"HandWriting Initialize Failed");
    _handwritingController.delegate = self;
    _drawView.controller = _handwritingController;
    [_handwritingController HandsInkSetOneLineRecognize];
}

-(void) buildBottomRowButton:(NSUInteger) top {
    
    NSUInteger left = 2;
    NSString *title = nil;
    if(_buttonLayout == ButtonLayoutDefault) {
        title = @".?123";
    } else {
        title = @"あいう";
    }
    UIButton *button = [self darkgrayButtonWithTitle:title image: nil];
    [button setFrame:CGRectMake(left, top, KEY_WIDTH, KEY_WIDTH)];
    [self addSubview:button];
    
    [button addTarget:self action:@selector(handleNumAlphButton:) forControlEvents:UIControlEventTouchDown];
    
    //handwriting
    button = [self darkgrayButtonWithTitle:@"手書" image: nil];
    left += KEY_WIDTH;
    left += KEY_H_SEP;
    [button setFrame:CGRectMake(left, top, KEY_WIDTH, KEY_WIDTH)];
    [self addSubview:button];
    [button addTarget:self action:@selector(handleHandwritingButton:) forControlEvents:UIControlEventTouchDown];
    
    left += KEY_WIDTH;
    left += KEY_H_SEP;
    button = [self darkgrayButtonWithTitle:nil image:[UIImage imageNamed:@"global"]];
    [button setFrame:CGRectMake(left, top, KEY_WIDTH, KEY_WIDTH)];
    [button addTarget:self.delegate action:@selector(handleInputModeListFromView:withEvent:) forControlEvents:UIControlEventAllTouchEvents];
    [self addSubview:button];
}

-(void) buildNumberPunctualLayout {
    NSArray *buttons = [self numberPunctualLayout];
    NSUInteger left = 0;
    NSUInteger top = AccessoryViewHeightDefault;
    
    NSUInteger i = 0;
    for(NSArray *row in buttons) {
        left = 2;
        if(i == 1) {
            left += KEY_WIDTH/2;
        }
        for(NSArray *keyChars in row) {
            KeyboardButton *button = nil;
            NSString *key = [keyChars firstObject];
            if([key isEqualToString:@"Return"]) {
                button = [self darkgrayButtonWithTitle:@"改行" image: nil];
                [button addTarget:self action:@selector(handleReturnButton:) forControlEvents:UIControlEventTouchDown];
                _returnButton = button;
            } else if([key isEqualToString:@"Del"]) {
                button = [self darkgrayButtonWithTitle:@"" image: [UIImage imageNamed:@"del"]];
                [button addTarget:self action:@selector(handleDeleteButton:) forControlEvents:UIControlEventTouchDown];
            } else if([key isEqualToString:@"#+="]) {
                button = [self darkgrayButtonWithTitle:@"#+=" image: nil];
                [button addTarget:self action:@selector(handleMoreSignButton:) forControlEvents:UIControlEventTouchDown];
            } else {
                if([keyChars count] == 2) {
                    if(_shiftOn) {
                        key = [keyChars firstObject];
                    } else {
                        key = [NSString stringWithFormat:@"%@\n%@", [keyChars objectAtIndex:0], [keyChars objectAtIndex:1]];
                    }
                }
                button = [self whiteButtonWithTitle:_shiftOn?[key uppercaseString]:[key lowercaseString] image:nil];
            }
            
            if([key isEqualToString:@"Return"]) {
                [button setFrame:CGRectMake(left, top, KEY_WIDTH * 1.5, KEY_WIDTH)];
            } else {
                [button setFrame:CGRectMake(left, top, KEY_WIDTH, KEY_WIDTH)];
            }
            [self addSubview:button];
            
            left += KEY_WIDTH;
            left += KEY_H_SEP;
        }
        top += KEY_WIDTH;
        top += KEY_V_SEP;
        i++;
    }
    
    [self buildBottomRowButton:top];
}

-(void) buildMoreSignLayout {
    NSArray *buttons = [self moreSignLayout];
    NSUInteger left = 0;
    NSUInteger top = AccessoryViewHeightDefault;
    
    NSUInteger i = 0;
    for(NSArray *row in buttons) {
        left = 2;
        if(i == 1) {
            left += KEY_WIDTH/2;
        }
        for(NSArray *keyChars in row) {
            KeyboardButton *button = nil;
            NSString *key = [keyChars firstObject];
            if([key isEqualToString:@"Return"]) {
                button = [self darkgrayButtonWithTitle:@"改行" image: nil];
                [button addTarget:self action:@selector(handleReturnButton:) forControlEvents:UIControlEventTouchDown];
                _returnButton = button;
            } else if([key isEqualToString:@"Del"]) {
                button = [self darkgrayButtonWithTitle:@"" image: [UIImage imageNamed:@"del"]];
                [button addTarget:self action:@selector(handleDeleteButton:) forControlEvents:UIControlEventTouchDown];
            } else if([key isEqualToString:@"123"]) {
                button = [self darkgrayButtonWithTitle:@"123" image: nil];
                [button addTarget:self action:@selector(handleNumAlphButton:) forControlEvents:UIControlEventTouchDown];
            } else {
                if([keyChars count] == 2) {
                    if(_shiftOn) {
                        key = [keyChars firstObject];
                    } else {
                        key = [NSString stringWithFormat:@"%@\n%@", [keyChars objectAtIndex:0], [keyChars objectAtIndex:1]];
                    }
                }
                button = [self whiteButtonWithTitle:_shiftOn?[key uppercaseString]:[key lowercaseString] image:nil];
            }
            if([key isEqualToString:@"Return"]) {
                [button setFrame:CGRectMake(left, top, KEY_WIDTH * 1.5, KEY_WIDTH)];
            } else {
                [button setFrame:CGRectMake(left, top, KEY_WIDTH, KEY_WIDTH)];
            }
            [self addSubview:button];
            
            left += KEY_WIDTH;
            left += KEY_H_SEP;
        }
        top += KEY_WIDTH;
        top += KEY_V_SEP;
        i++;
    }
    
    [self buildBottomRowButton:top];
}

-(void) buildDefaultLayout {
    self.inputEngine = [[KanaInputEngine alloc] init];
    self.inputEngine.delegate = self;
    
    self.inputManager = [[InputManager alloc] init];
    self.inputManager.delegate = self;
    
    //markedTextLabel
    CGRect labelFrame = CGRectMake(0, 0, self.frame.size.width
                                   , MarkedTextLabelHeightDefault);
    if(self.markedTextLabel == nil) {
        UILabel *markedTextLabel = [[UILabel alloc] initWithFrame:labelFrame];
        markedTextLabel.backgroundColor = [UIColor whiteColor];
        markedTextLabel.font = [UIFont systemFontOfSize:16];
        markedTextLabel.textColor = [UIColor colorWithWhite:0.65 alpha:1.0];
        [self addSubview:markedTextLabel];
        self.markedTextLabel = markedTextLabel;
    }

    //candidateBar
    if(self.candidateBar == nil) {
        CGRect barFrame = labelFrame;
        barFrame.origin.y = CGRectGetHeight(labelFrame);
        barFrame.size.height = AccessoryViewHeightDefault - CGRectGetHeight(labelFrame);
        KeyboardCandidateBar *candidateBar = [[KeyboardCandidateBar alloc] initWithFrame:barFrame];
        candidateBar.delegate = self;
        candidateBar.backgroundColor = [UIColor clearColor];
        [self addSubview:candidateBar];
        self.candidateBar = candidateBar;
    }
    
    self.markedText = @"";
    
    NSArray *buttons = [self defaultLayout];
    NSUInteger left = 0;
    NSUInteger top = AccessoryViewHeightDefault;
    NSUInteger i = 0;
    for(NSArray *row in buttons) {
        left = 2;
        if(i == 1) {
            left += KEY_WIDTH/2;
        }
        for(NSArray *keyChars in row) {
            KeyboardButton *button = nil;
            NSString *key = [keyChars firstObject];
            if([key isEqualToString:@"Return"]) {
                button = [self darkgrayButtonWithTitle:@"改行" image: nil];
                [button addTarget:self action:@selector(handleReturnButton:) forControlEvents:UIControlEventTouchDown];
                _returnButton = button;
            } else if([key isEqualToString:@"Del"]) {
                button = [self darkgrayButtonWithTitle:@"" image: [UIImage imageNamed:@"del"]];
                [button addTarget:self action:@selector(handleDeleteButton:) forControlEvents:UIControlEventTouchDown];
            } else if([key isEqualToString:@"Shift"]) {
                if(_shiftOn) {
                    button = [self darkgrayButtonWithTitle:@"" image: [UIImage imageNamed:@"shift_on"]];
                } else {
                    button = [self whiteButtonWithTitle:nil image:[UIImage imageNamed:@"shift"]];
                }
                [button addTarget:self action:@selector(handleShiftButton:) forControlEvents:UIControlEventTouchDown];
            } else {
                if([keyChars count] == 2) {
                    if(_shiftOn) {
                        key = [keyChars firstObject];
                    } else {
                        key = [NSString stringWithFormat:@"%@\n%@", [keyChars objectAtIndex:0], [keyChars objectAtIndex:1]];
                    }
                }
                button = [self whiteButtonWithTitle:_shiftOn?[key uppercaseString]:[key lowercaseString] image:nil];
                [button addTarget:self action:@selector(handleKeyDown:) forControlEvents:UIControlEventTouchDown];
            }
            
            if([key isEqualToString:@"Return"]) {
                [button setFrame:CGRectMake(left, top, KEY_WIDTH * 1.5, KEY_WIDTH)];
            } else {
                [button setFrame:CGRectMake(left, top, KEY_WIDTH, KEY_WIDTH)];
            }
            [self addSubview:button];
            
            left += KEY_WIDTH;
            left += KEY_H_SEP;
        }
        top += KEY_WIDTH;
        top += KEY_V_SEP;
        i++;
    }
    
    [self buildBottomRowButton:top];
}

#pragma mark - Button Event Handler
-(void) handleKeyDown:(id)sender {
    UIButton *button = sender;
    NSString *title = [button titleForState:UIControlStateNormal];
    NSArray *array = [title componentsSeparatedByString:@"\n"];
    [self.inputEngine insertCharacter:[array lastObject]];
}
-(void) handleShiftButton:(id)sender {
    _shiftOn = !_shiftOn;
    [self updateLayout];
}

-(void) handleNumAlphButton:(id)sender {
    UIButton *button = sender;
    NSString *title = [button titleForState:UIControlStateNormal];
    if([title isEqualToString:@"あいう"]) {
        _buttonLayout = ButtonLayoutDefault;
    } else if([title isEqualToString:@".?123"]) {
        _buttonLayout = ButtonLayoutNumberPunctual;
    }
    
    [self updateLayout];
}

-(void) handleMoreSignButton:(id)sender {
    UIButton *button = sender;
    NSString *title = [button titleForState:UIControlStateNormal];
    if([title isEqualToString:@"#+="]) {
        _buttonLayout = ButtonLayoutMoreSign;
    } else if([title isEqualToString:@"123"]) {
        _buttonLayout = ButtonLayoutNumberPunctual;
    }
    
    [self updateLayout];
}

-(void) handleHandwritingButton:(id) sender {
    _buttonLayout = ButtonLayoutHandwriting;
    [self updateLayout];
}

-(void) handleHandwritingClearButton:(id) sender {
    [_drawView clearPoints];
    [_handwritingController clear];
}

-(void) handleDeleteButton:(id) sender {
    NSString *markedText = self.markedText;
    NSUInteger length = markedText.length;
    if (length == 0) {
        [self.delegate keyboardViewDidInputDelete];
    } else {
        [self.inputEngine backspace];
        
        self.markedText = [markedText substringToIndex:length - 1];
        if (self.markedText.length > 0) {
            [self.inputManager requestCandidatesForInput:self.markedText];
        }
    }
}

-(void) handleReturnButton:(id)sender {
    NSString *markedText = self.markedText;
    NSUInteger length = markedText.length;
    if (length == 0) {
        [self.delegate keyboardViewDidInputReturn];
    } else {
        [self.delegate keyboardViewDidAcceptCandidate:markedText];
        self.markedText = @"";
    }
}
#pragma mark -
- (void)handWritingRecognized:(NSString *)str {
    
}
#pragma mark - Button Layout
- (NSArray *)defaultLayout {
    return @[
             @[@[@"q"], @[@"w"], @[@"e"], @[@"r"], @[@"t"], @[@"y"], @[@"u"], @[@"i"], @[@"o"], @[@"p"], @[@"Del"]],
             @[@[@"a"], @[@"s"], @[@"d"], @[@"f"], @[@"g"], @[@"h"], @[@"j"], @[@"k"], @[@"l"], @[@"Return"]],
             @[@[@"Shift"], @[@"z"], @[@"x"], @[@"c"], @[@"v"], @[@"b"], @[@"n"], @[@"m"], @[@"！", @"、"], @[@"？", @"。"], @[@"ー"]]
             ];
}

- (NSArray *)numberPunctualLayout {
    return @[
             @[@[@"1"], @[@"2"], @[@"3"], @[@"4"], @[@"5"], @[@"6"], @[@"7"], @[@"8"], @[@"9"], @[@"0"], @[@"Del"]],
             @[@[@"@"], @[@"#"], @[@"¥"], @[@"-"], @[@"*"], @[@"("], @[@")"], @[@"「"], @[@"」"], @[@"Return"]],
             @[@[@"#+="], @[@"％"], @[@"〜"], @[@"..."], @[@"/"], @[@";"], @[@":"], @[@"!",@"、"], @[@"?",@"。"], @[@"ー"]],
             ];
}

- (NSArray *)moreSignLayout {
    return @[
             @[@[@"〒"], @[@"々"], @[@"〆"], @[@"※"], @[@"{"], @[@"}"], @[@"'"], @[@"\""], @[@","], @[@"."], @[@"Del"]],
             @[@[@"$"], @[@"€"], @[@"£"], @[@"&"], @[@"^"], @[@"["], @[@"]"], @[@"『"], @[@"』"], @[@"Return"]],
             @[@[@"123"], @[@"・"], @[@"_"], @[@"+"], @[@"="], @[@"\""], @[@"<"], @[@">"], @[@"!"], @[@"?"]],
             ];
}

#pragma mark - Buttons Utility Method
- (KeyboardButton *)whiteButtonWithTitle:(NSString *)title image:(UIImage *)image
{
    UIImage *backgroundImage = [UIImage imageNamed:@"key_white"];
    UIImage *highlightedBackgroundImage = [UIImage imageNamed:@"key_darkgray"];
    KeyboardButton *button = [self buttonWithTitle:title image:image backgroundImage:backgroundImage highlightedBackgroundImage:highlightedBackgroundImage];
    return button;
}

- (KeyboardButton *)grayButtonWithTitle:(NSString *)title image:(UIImage *)image
{
    UIImage *backgroundImage = [UIImage imageNamed:@"key_gray"];
    UIImage *highlightedBackgroundImage = [UIImage imageNamed:@"key_darkgray"];
    KeyboardButton *button = [self buttonWithTitle:title image:image backgroundImage:backgroundImage highlightedBackgroundImage:highlightedBackgroundImage];
    return button;
}

- (KeyboardButton *)darkgrayButtonWithTitle:(NSString *)title image:(UIImage *)image
{
    UIImage *backgroundImage = [UIImage imageNamed:@"key_darkgray"];
    UIImage *highlightedBackgroundImage = [UIImage imageNamed:@"key_white"];
    KeyboardButton *button = [self buttonWithTitle:title image:image backgroundImage:backgroundImage highlightedBackgroundImage:highlightedBackgroundImage];
    return button;
}

- (KeyboardButton *)blueButtonWithTitle:(NSString *)title image:(UIImage *)image
{
    UIImage *backgroundImage = [UIImage imageNamed:@"key_blue"];
    UIImage *highlightedBackgroundImage = [UIImage imageNamed:@"key_white"];
    KeyboardButton *button = [self buttonWithTitle:title image:image backgroundImage:backgroundImage highlightedBackgroundImage:highlightedBackgroundImage];
    return button;
}

- (KeyboardButton *)buttonWithTitle:(NSString *)title image:(UIImage *)image backgroundImage:(UIImage *)backgroundImage highlightedBackgroundImage:(UIImage *)highlightedBackgroundImage
{
    KeyboardButton *button = [KeyboardButton buttonWithType:UIButtonTypeCustom];
    
    button.titleLabel.font = [UIFont systemFontOfSize:20];
    button.titleLabel.textAlignment = NSTextAlignmentCenter;
    button.titleLabel.numberOfLines = 2;
    [button setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    
    [button setBackgroundImage:backgroundImage forState:UIControlStateNormal];
    [button setBackgroundImage:highlightedBackgroundImage forState:UIControlStateHighlighted];
    
    [button setTitle:title forState:UIControlStateNormal];
    [button setImage:image forState:UIControlStateNormal];
    
    return button;
}

- (void)setMarkedText:(NSString *)markedText
{
    _markedText = markedText;
    self.markedTextLabel.text = markedText;
    
    if (markedText.length == 0) {
        self.candidateBar.candidates = nil;
        [_returnButton setTitle:@"改行" forState:UIControlStateNormal];
    } else {
        [_returnButton setTitle:@"確定" forState:UIControlStateNormal];
    }
    
    [self setNeedsLayout];
}

#pragma mark - Delegate
- (void)keyboardInputEngine:(KanaInputEngine *)engine processedText:(NSString *)text displayText:(NSString *)displayText {
    self.markedText = displayText;
    [self.inputManager requestCandidatesForInput:text];
}

- (void)inputManager:(InputManager *)inputManager didCompleteWithCandidates:(NSArray *)candidates
{
    self.candidateBar.candidates = candidates;
    //InputCandidate *segment = [candidates firstObject];
}

- (void)candidateBar:(KeyboardCandidateBar *)candidateBar didAcceptCandidate:(InputCandidate *)segment
{
    NSString *input = segment.input;
    NSRange range = [self.markedText rangeOfString:input];
    if (range.location != NSNotFound) {
        self.markedText = [self.markedText stringByReplacingCharactersInRange:range withString:@""];
    }
    
    if (self.markedText.length > 0) {
        [self.inputManager requestCandidatesForInput:self.markedText];
    }
    
    self.inputEngine.text = self.markedText;

    [self.delegate keyboardViewDidAcceptCandidate: segment.candidate];
}
@end
