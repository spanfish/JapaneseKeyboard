//
//  KeyboardView.m
//  JapaneseKeyboardKit
//
//  Created by kishikawa katsumi on 2014/09/28.
//  Copyright (c) 2014 kishikawa katsumi. All rights reserved.
//

#import "KeyboardView.h"
#import "KeyboardButton.h"
#import "KeyboardCandidateBar.h"
#import "KanaInputEngine.h"
#import "InputManager.h"
#import "InputCandidate.h"
#import "HandWritingController.h"
#import "DrawView.h"

const CGFloat AccessoryViewHeightDefault = 50.0;
//const CGFloat AccessoryViewHeightLandscape = 30.0;
const CGFloat MarkedTextLabelHeightDefault = 16.0;
//const CGFloat MarkedTextLabelHeightLandscape = 10.0;

@interface KeyboardView () <KeyboardInputEngineDelegate, KeyboardCandidateBarDelegate> {
    BOOL _shiftOn;
    BOOL _leftFuncOn;
    BOOL _rightFuncOn;
    DrawView *_drawView;
    HandWritingController *_handwritingController;
}

//@property (nonatomic) HandWritingController *handWritingController;
@property (nonatomic) KanaInputEngine *inputEngine;
@property (nonatomic) InputManager *inputManager;

@property (nonatomic) KeyboardButton *shiftButton;
@property (nonatomic) KeyboardButton *returnButton;
@property (nonatomic) KeyboardButton *leftFuncButton;
@property (nonatomic) KeyboardButton *rightFuncButton;
@property (nonatomic) KeyboardButton *spaceButton;
@property (nonatomic) KeyboardButton *nextIMEButton;

//
//@property (nonatomic) BOOL shifted;
//@property (nonatomic) BOOL shiftLocked;

@property (nonatomic) NSString *markedText;
@property (nonatomic) UILabel *markedTextLabel;

@property (nonatomic) KeyboardCandidateBar *candidateBar;

@property (nonatomic) UIView *borderTop;
@property (nonatomic) UIView *borderBottom;

@end

@implementation KeyboardView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.inputEngine = [[KanaInputEngine alloc] init];
        self.inputEngine.delegate = self;
        
        self.inputManager = [[InputManager alloc] init];
        self.inputManager.delegate = self;
        
        CGRect labelFrame = frame;
        labelFrame.size.height = MarkedTextLabelHeightDefault;
        UILabel *markedTextLabel = [[UILabel alloc] initWithFrame:labelFrame];
        markedTextLabel.backgroundColor = [UIColor whiteColor];
        markedTextLabel.font = [UIFont systemFontOfSize:12.0];
        markedTextLabel.textColor = [UIColor colorWithWhite:0.65 alpha:1.0];
        [self addSubview:markedTextLabel];
        self.markedTextLabel = markedTextLabel;
        markedTextLabel.backgroundColor = [UIColor clearColor];
        
        CGRect barFrame = labelFrame;
        barFrame.origin.y = CGRectGetHeight(labelFrame);
        barFrame.size.height = AccessoryViewHeightDefault - CGRectGetHeight(labelFrame);
        KeyboardCandidateBar *candidateBar = [[KeyboardCandidateBar alloc] initWithFrame:barFrame];
        candidateBar.delegate = self;
        [self addSubview:candidateBar];
        self.candidateBar = candidateBar;
        self.candidateBar.backgroundColor = [UIColor clearColor];
        
        
//        UIColor *borderColor = [UIColor colorWithWhite:0.784 alpha:1.000];
//        CGFloat scale = [[UIScreen mainScreen] scale];
//
//        UIView *borderTop = [[UIView alloc] initWithFrame:CGRectMake(0.0, 0.0, CGRectGetWidth(self.bounds), 1.0 / scale)];
//        borderTop.autoresizingMask = UIViewAutoresizingFlexibleWidth;
//        borderTop.backgroundColor = borderColor;
//        [self addSubview:borderTop];
//        self.borderTop = borderTop;
//
//        UIView *borderBottom = [[UIView alloc] initWithFrame:CGRectMake(0.0, CGRectGetMaxY(barFrame) - 1.0 / scale, CGRectGetWidth(self.bounds), 1.0 / scale)];
//        borderBottom.autoresizingMask = UIViewAutoresizingFlexibleWidth;
//        borderBottom.backgroundColor = borderColor;
//        [self addSubview:borderBottom];
//        self.borderBottom = borderBottom;
        
        self.markedText = @"";
    }
    
    return self;
}

-(void) layoutSubviews {
    [super layoutSubviews];
    
    NSLog(@"textLabel:%@%@", NSStringFromCGRect(self.markedTextLabel.frame), NSStringFromCGRect(self.candidateBar.frame));
    self.markedTextLabel.frame = CGRectMake(0, 0, self.frame.size.width, MarkedTextLabelHeightDefault);
    self.candidateBar.frame = CGRectMake(0, MarkedTextLabelHeightDefault, self.frame.size.width, AccessoryViewHeightDefault - MarkedTextLabelHeightDefault);
    NSLog(@"textLabel:%@%@", NSStringFromCGRect(self.markedTextLabel.frame), NSStringFromCGRect(self.candidateBar.frame));
    
//    CGFloat scale = [[UIScreen mainScreen] scale];
//    self.borderTop.frame = CGRectMake(0, 0, self.frame.size.width, 1/scale);
//
//    self.borderBottom.frame = CGRectMake(0, MarkedTextLabelHeightDefault - 1/scale, self.frame.size.width, 1/scale);
}
#pragma mark -
-(void) removeAllButtons {
    for (UIView *view in self.subviews) {
        if([view isKindOfClass:[KeyboardButton class]]) {
            [view removeFromSuperview];
        }
    }
}

- (void)setInputMode:(KeyboardInputMode)inputMode {
    _inputMode = inputMode;
    [self removeAllButtons];
    switch (inputMode) {
        case KeyboardInputModeKana:
            [self setKanaLayout];
            break;
        case KeyboardInputModeNumber:
            [self setNumberLayout];
            break;
        case KeyboardInputModeEmail:
            [self setEmailLayout];
            break;
        case KeyboardInputModeHandWriting:
            [self setHandwritingLayout];
            break;
        case KeyboardInputModeAlphabet:
        case KeyboardInputModeNumberPunctual:
        case KeyboardInputModeKataKana:
        default:
            [self setKanaLayout];
            break;
    }
}

- (void)setMarkedText:(NSString *)markedText {
    _markedText = markedText;
    self.markedTextLabel.text = markedText;
    
    if (markedText.length == 0) {
        self.candidateBar.candidates = nil;
        [self.spaceButton setTitle:@"" forState:UIControlStateNormal];
    }
    
    [self setNeedsLayout];
}

#pragma mark -
- (void)handleInputModeListFromView:(nonnull UIView *)view withEvent:(nonnull UIEvent *)event {
    if([self.delegate respondsToSelector:@selector(handleInputModeListFromView:withEvent:)]) {
        [self.delegate handleInputModeListFromView:view withEvent:event];
    } else {
        [self.delegate advanceToNextInputMode];
    }
}

//- (void)buttonDidTouchDown:(KeyboardButton *)button
//{
//    KeyboardButtonIndex keyIndex = button.keyIndex;
//
//    if (keyIndex < KeyboardButtonIndexNextKeyboard) {
//        NSString *input = [button titleForState:UIControlStateNormal];
//        if (self.inputMode == KeyboardInputModeKana) {
//            [self.inputEngine insertCharacter:input];
//        } else {
//            [self.delegate keyboardView:self didAcceptCandidate:input];
//        }
//        [self resetShift];
//    } else {
//        switch (keyIndex) {
//            case KeyboardButtonIndexHandwriting:
//                [self handleHandWritingInputMode];
//                break;
//            case KeyboardButtonIndexHandwritingClear:
//                [self handleHandWritingClear];
//                break;
//            case KeyboardButtonIndexHandwritingUndo:
//                [self handleHandWritingUndo];
//                break;
//            case KeyboardButtonIndexToggleInputMode:
//                [self handleToggleInputMode];
//                break;
//
//            case KeyboardButtonIndexShift:
//                [self handleShift];
//                break;
//
//            case KeyboardButtonIndexSpace:
//                [self handleSpace];
//                break;
//
//            case KeyboardButtonIndexComma:
//                [self handleComma];
//                break;
//
//            case KeyboardButtonIndexPeriod:
//                [self handlePeriod];
//                break;
//
//            case KeyboardButtonIndexDelete:
//                [self handleDelete];
//                break;
//
//            case KeyboardButtonIndexPreviousCursor:
//                [self.delegate keyboardViewBackCursor:self];
//                break;
//
//            case KeyboardButtonIndexNextCursor:
//                [self.delegate keyboardViewForwardCursor:self];
//                break;
//
//            default:
//                break;
//        }
//    }
//}
//
//- (void)buttonDidTouchUp:(KeyboardButton *)button
//{
//    KeyboardButtonIndex keyIndex = button.keyIndex;
//    switch (keyIndex) {
//        case KeyboardButtonIndexNextKeyboard:
//            [self acceptCurrentCandidate];
//            [self.delegate keyboardViewShouldAdvanceToNextInputMode:self];
//            break;
//
//        case KeyboardButtonIndexReturn:
//            [self handleReturn:nil];
//            break;
//
//        case KeyboardButtonIndexDismiss:
//            [self.delegate keyboardViewShouldDismiss:self];
//            [self resetShift];
//            break;
//
//        case KeyboardButtonIndexPreviousCandidate:
//            [self.candidateBar selectPreviousCandidate];
//            break;
//
//        case KeyboardButtonIndexNextCandidate:
//            [self.candidateBar selectNextCandidate];
//            break;
//
//        default:
//            break;
//    }
//}

//- (void)buttonDidTouchDownRepeat:(KeyboardButton *)button
//{
//    KeyboardButtonIndex keyIndex = button.keyIndex;
//    switch (keyIndex) {
//        case KeyboardButtonIndexShift:
//            [self handleShiftLock];
//            break;
//
//        default:
//            break;
//    }
//}
//
//-(void) handleHandWritingClear {
////    [[HandWritingController controller] clear];
//}
//
//-(void) handleHandWritingUndo {
////    [[HandWritingController controller] undo];
//}

//- (void)handleHandWritingInputMode
//{
//    if (self.inputMode == KeyboardInputModeHandWriting) {
//        self.inputMode = KeyboardInputModeKana;
//    } else {
//        self.inputMode = KeyboardInputModeHandWriting;
//    }
//
//
//    if(self.inputMode == KeyboardInputModeHandWriting) {
//        [self setupHandWritingController];
//    } else {
//        [self dismissHandWritingController];
//    }
//
////    [self.keyboardLayout setMetrics:self.keyboardLayout.metrics];
//
////    [self updateKeyboardLayout];
//    //[self.keyboardLayout setInputMode:<#(KeyboardInputMode)#> updateButtonLayout];
//}

//-(void) setupHandWritingController {
////    self.handWritingController = [HandWritingController controller];
//    BOOL result = [self.handWritingController HandsInkInitialize];
//    NSAssert(result, @"HandWriting Initialize Failed");
////    self.handWritingController.delegate = self;
////    [[HandWritingController controller] HandsInkSetOneLineRecognize];
//    _markedTextLabel.hidden = YES;
//}

//-(void) dismissHandWritingController {
//    _markedTextLabel.hidden = NO;
////    [[HandWritingController controller] HandsInkClose];
//}

//-(void) recognizeHandWriting {
//
//}

- (void)handleComma
{
    if (self.inputMode == KeyboardInputModeKana) {
        [self.inputEngine insertCharacter:@"、"];
    } else {
        [self.delegate keyboardView:self didAcceptCandidate:@","];
    }
}

- (void)handlePeriod
{
    if (self.inputMode == KeyboardInputModeKana) {
        [self.inputEngine insertCharacter:@"。"];
    } else {
        [self.delegate keyboardView:self didAcceptCandidate:@"."];
    }
}


- (void)handleReturn:(id) sender
{
    NSString *markedText = self.markedText;
    NSUInteger length = markedText.length;
    if (length == 0) {
        [self.delegate keyboardViewDidInputReturn:self];
    } else {
        [self acceptCurrentCandidate];
    }
}

//- (void)handleShift
//{
//    if (self.shiftLocked) {
//        self.shiftLocked = NO;
//    } else {
//        self.shifted = !self.shifted;
//    }
//}
//
//- (void)handleShiftLock
//{
//    self.shiftLocked = !self.shiftLocked;
//}
//
//- (void)resetShift
//{
//    if (!self.shiftLocked) {
//        self.shifted = NO;
//    }
//}
//
#pragma mark -

//- (void)setShifted:(BOOL)shifted
//{
//    _shifted = shifted;
//    self.inputEngine.shifted = shifted;
////    self.keyboardLayout.shifted = shifted;
//}
//
//- (void)setShiftLocked:(BOOL)shiftLocked
//{
//    _shiftLocked = shiftLocked;
//    _shifted = shiftLocked;
//    self.inputEngine.shifted = shiftLocked;
////    self.keyboardLayout.shiftLocked = shiftLocked;
//}

#pragma mark -

- (void)acceptCurrentCandidate
{
    if (self.candidateBar.selectedCandidate) {
        [self.candidateBar acceptCurrentCandidate];
    } else {
        [self.delegate keyboardView:self didAcceptCandidate:self.markedText];
        
        self.markedText = @"";
        self.inputEngine.text = self.markedText;
    }
}

#pragma mark - Input Engine
- (void)handWritingRecognized:(NSString *)str {
    InputCandidate *candidate = [[InputCandidate alloc] initWithInput:nil candidate:str];
    [self inputManager:nil didCompleteWithCandidates:@[candidate]];
}

- (void)keyboardInputEngine:(KanaInputEngine *)engine processedText:(NSString *)text displayText:(NSString *)displayText {
    //NSLog(@"keyboardInputEngine:%@", displayText);
    self.markedText = displayText;
    [self.inputManager requestCandidatesForInput:text];
}

#pragma mark -
//-(void)handWritingRecognized:(NSString *) str {
//    InputCandidate *segment = [[InputCandidate alloc] init];
//    segment.input = @"";
//    segment.candidate = str;
//    self.candidateBar.candidates = @[segment];
//}

- (void)inputManager:(InputManager *)inputManager didCompleteWithCandidates:(NSArray *)candidates {
    self.candidateBar.candidates = candidates;
    //NSLog(@"candidates:%@", candidates);
    //InputCandidate *segment = [candidates firstObject];
    if([candidates count] > 0) {
        [self.spaceButton setTitle:@"次候補" forState:UIControlStateNormal];
    } else {
        [self.spaceButton setTitle:@"" forState:UIControlStateNormal];
    }
}

- (void)inputManager:(InputManager *)inputManager didFailWithError:(NSError *)error {
    
}

#pragma mark -

- (void)candidateBar:(KeyboardCandidateBar *)candidateBar didAcceptCandidate:(InputCandidate *)segment
{
    if(self.inputMode == KeyboardInputModeHandWriting) {
        [self handleHandwritingClearButton:nil];
    } else {
        NSString *input = segment.input;
        NSRange range = [self.markedText rangeOfString:input];
        if (range.location != NSNotFound) {
            self.markedText = [self.markedText stringByReplacingCharactersInRange:range withString:@""];
        }
        
        if (self.markedText.length > 0) {
            [self.inputManager requestCandidatesForInput:self.markedText];
        }
        
        self.inputEngine.text = self.markedText;
    }
    [self.delegate keyboardView:self didAcceptCandidate:segment.candidate];
}

#pragma mark -
-(void) setHandwritingLayout {
    NSUInteger left = 2;
    NSUInteger top = AccessoryViewHeightDefault;
    
    CGFloat w = [UIScreen mainScreen].bounds.size.width;
    CGFloat width = MIN(MAX(w/11, 65), 75);
    CGFloat height = width;
    
    //Draw view
    _drawView = [[DrawView alloc] initWithFrame:CGRectMake(2, top, w - width - 2, self.frame.size.height - AccessoryViewHeightDefault)];
    left = CGRectGetMaxX(_drawView.frame);
    [self addSubview:_drawView];

    
    //QWERTY button
    UIButton *button = [self darkgrayButtonWithTitle:@"あいう" image: nil];
    [button addTarget:self action:@selector(handleQwertButton:) forControlEvents:UIControlEventTouchDown];
    [button setFrame:CGRectMake(self.frame.size.width - width, self.frame.size.height - height, width, height)];
    [self addSubview:button];
    
    top = AccessoryViewHeightDefault;
    button = [self darkgrayButtonWithTitle:nil image: [UIImage imageNamed:@"del"]];
    [button setFrame:CGRectMake(self.frame.size.width - width, top, width, height)];
    [self addSubview: button];
    [button addTarget:self action:@selector(handleDeleteButton:) forControlEvents:UIControlEventTouchDown];
    
    //Handwriting clear button
    top += height;
    button = [self darkgrayButtonWithTitle:nil image: [UIImage imageNamed:@"eraser"]];
    [button setFrame:CGRectMake(self.frame.size.width - width, top, width, height)];
    [self addSubview:button];
    [button addTarget:self action:@selector(handleHandwritingClearButton:) forControlEvents:UIControlEventTouchUpInside];
//
    if(!_handwritingController) {
        _handwritingController = [[HandWritingController alloc] init];
    }
    
    BOOL result = [_handwritingController HandsInkInitialize];
    NSAssert(result, @"HandWriting Initialize Failed");
    _handwritingController.delegate = self;
    _drawView.controller = _handwritingController;
    [_handwritingController HandsInkSetOneLineRecognize];
}

-(void) setPhoneLayout {
    [self setNumberLayout:YES];
}

-(void) setNumberLayout {
    [self setNumberLayout: NO];
}

-(void) setNumberLayout:(BOOL) phone {
    NSArray *keys = keys = @[
                             @[@[@"1"], @[@"2"], @[@"3"], @[phone ? @"*" : @""]],
                             @[@[@"4"], @[@"5"], @[@"6"], @[phone ? @"+" : @""]],
                             @[@[@"7"], @[@"8"], @[@"9"], @[phone ? @"#" : @""]],
                             ];
    
    NSUInteger numOfCols = phone ? 4 : 3;
    CGFloat w = [UIScreen mainScreen].bounds.size.width;
    CGFloat width = MIN(MAX(w/numOfCols, 65), 75);
    CGFloat height = width;
    CGFloat leftMargin = (w - width * numOfCols) / 2;
    CGFloat top = AccessoryViewHeightDefault;
    
    NSUInteger row = 0;
    for(NSArray *keyRow in keys) {
        NSUInteger left = leftMargin;
        for(NSArray *keys in keyRow) {
            NSString *keyTitle = [keys firstObject];
            if([keyTitle length] == 0) {
                break;
            }
            KeyboardButton *button = [self whiteButtonWithTitle:keyTitle image:nil];
            [button addTarget:self action:@selector(handleButtonUp:) forControlEvents:UIControlEventTouchUpInside];
            [button setFrame:CGRectMake(left, top, width, height)];
            [self addSubview: button];
            left += width;
        }
        row++;
        top += height;
    }
    
    NSUInteger left = leftMargin;
    KeyboardButton *zeroButton = [self whiteButtonWithTitle:@"0" image:nil];
    [zeroButton addTarget:self action:@selector(handleButtonUp:) forControlEvents:UIControlEventTouchUpInside];
    [zeroButton setFrame:CGRectMake(left, top, width, height)];
    [self addSubview: zeroButton];
    left += width * 2;
    
    KeyboardButton *delButton = [self darkgrayButtonWithTitle:@"" image: [UIImage imageNamed:@"del"]];
    [delButton addTarget:self action:@selector(handleDeleteButton:) forControlEvents:UIControlEventTouchUpInside];
    [delButton setFrame:CGRectMake(left, top, width, height)];
    [self addSubview: delButton];
    
    if(phone) {
        CGRect frame = zeroButton.frame;
        frame.size.width *= 2;
        zeroButton.frame = frame;
        
        frame = delButton.frame;
        frame.size.width *= 2;
        delButton.frame = frame;
    }
}

-(void) setEmailLayout {
    NSLog(@"Keyboard-setEmailLayout");
    NSArray *keys = nil;
    if(_leftFuncOn == 1) {
        keys = @[
                 @[@[@"1"], @[@"2"], @[@"3"], @[@"4"], @[@"5"], @[@"6"], @[@"7"], @[@"8"], @[@"9"], @[@"0"]/*, @[@"Del"]*/],
                 @[@[@"@"], @[@"#"], @[@"¥"], @[@"-"], @[@"*"], @[@"("], @[@")"], @[@"「"], @[@"」"]/*, @[@"Return"]*/],
                 @[/*@[@"Shift"],*/ @[@"^_^"], @[@"%"], @[@"〜"], @[@"…"], @[@"/"], @[@";"], @[@":"], @[@"！", @"、"], @[@"？", @"。"]]
                 ];
    } else {
        keys = @[
                 @[@[@"q"], @[@"w"], @[@"e"], @[@"r"], @[@"t"], @[@"y"], @[@"u"], @[@"i"], @[@"o"], @[@"p"]/*, @[@"Del"]*/],
                 @[@[@"a"], @[@"s"], @[@"d"], @[@"f"], @[@"g"], @[@"h"], @[@"j"], @[@"k"], @[@"l"]/*, @[@"Return"]*/],
                 @[/*@[@"Shift"],*/ @[@"z"], @[@"x"], @[@"c"], @[@"v"], @[@"b"], @[@"n"], @[@"m"], @[@"@"], @[@"."], @[@"-"]]
                 ];
    }
    
    CGFloat w = [UIScreen mainScreen].bounds.size.width;
    CGFloat width = MIN(MAX(w/11, 65), 85);
    CGFloat height = width;
    CGFloat leftMargin = (w - width * 11) / 2;
    CGFloat top = AccessoryViewHeightDefault;
    
    NSUInteger row = 0;
    for(NSArray *keyRow in keys) {
        NSUInteger left = leftMargin;
        if(row == 1) {
            left += width / 2;
        }
        
        if(row == 2) {
            //shift
            //shift
            if(_shiftOn) {
                self.shiftButton = [self darkgrayButtonWithTitle:@"" image: [UIImage imageNamed:@"shift_on"]];
            } else {
                self.shiftButton = [self whiteButtonWithTitle:nil image:[UIImage imageNamed:@"shift"]];
            }
            [self.shiftButton setFrame:CGRectMake(left, top, width, height)];
            [self addSubview: self.shiftButton];
            [self.shiftButton addTarget:self action:@selector(handleShiftButton:) forControlEvents:UIControlEventTouchDown];
            left += width;
        } else if(row == 3) {
            self.leftFuncButton = [self darkgrayButtonWithTitle:@".?123" image: nil];
            [self.leftFuncButton setFrame:CGRectMake(left, top, width, height)];
            [self addSubview: self.leftFuncButton];
            [self.returnButton addTarget:self action:@selector(handLeftFuncButton:) forControlEvents:UIControlEventTouchDown];
            left += width;
        }
        for(NSArray *keys in keyRow) {
            NSString *keyTitle = [keys firstObject];
            if([keys count] == 2) {
                if(!_shiftOn) {
                    keyTitle = [NSString stringWithFormat:@"%@\n%@", keyTitle, [keys objectAtIndex:1]];
                }
            }
            if(_shiftOn) {
                keyTitle = [keyTitle uppercaseString];
            }
            KeyboardButton *button = [self whiteButtonWithTitle:keyTitle image:nil];
            [button addTarget:self action:@selector(handleButtonUp:) forControlEvents:UIControlEventTouchUpInside];
            [button setFrame:CGRectMake(left, top, width, height)];
            [self addSubview: button];
            left += width;
        }
        if(row == 0) {
            KeyboardButton *button = [self darkgrayButtonWithTitle:@"" image: [UIImage imageNamed:@"del"]];
            [button setFrame:CGRectMake(left, top, w - leftMargin - left, height)];
            [self addSubview: button];
            [button addTarget:self action:@selector(handleDeleteButton:) forControlEvents:UIControlEventTouchDown];
        } else if(row == 1) {
            self.returnButton = [self darkgrayButtonWithTitle:@"開く" image: nil];
            [self.returnButton setFrame:CGRectMake(left, top, w - leftMargin - left, height)];
            [self addSubview: self.returnButton];
            [self.returnButton addTarget:self action:@selector(handleReturn:) forControlEvents:UIControlEventTouchDown];
        }
        
        row++;
        top += height;
    }
    NSUInteger left = leftMargin;
    
    KeyboardButton *button = nil;
    if(!_leftFuncOn) {
        button = [self darkgrayButtonWithTitle:@".?123" image:nil];
    } else {
        button = [self darkgrayButtonWithTitle:@"abc" image:nil];
    }
    [button setFrame:CGRectMake(left, top, width, height)];
    [button addTarget:self action:@selector(handLeftFuncButton:) forControlEvents:UIControlEventTouchDown];
    [self addSubview: button];
    left += width;
    
    //close
    button = [self darkgrayButtonWithTitle:nil image:[UIImage imageNamed:@"keyboard"]];
    [button setFrame:CGRectMake(w - width, top, width, height)];
    [button addTarget:self action:@selector(handleCloseButton:) forControlEvents:UIControlEventAllTouchEvents];
    [self addSubview: button];
    
    self.nextIMEButton = [self darkgrayButtonWithTitle:nil image:[UIImage imageNamed:@"global"]];
    [self.nextIMEButton setFrame:CGRectMake(left, top, width, height)];
    [self.nextIMEButton addTarget:self action:@selector(handleInputModeListFromView:withEvent:) forControlEvents:UIControlEventAllTouchEvents];
    [self addSubview: self.nextIMEButton];
    
    //right func button
    if(!_leftFuncOn && !_rightFuncOn) {
        self.rightFuncButton = [self darkgrayButtonWithTitle:@"abc" image:nil];
    } else {
        self.rightFuncButton = [self darkgrayButtonWithTitle:@"abc" image:nil];
    }
    [self.rightFuncButton addTarget:self action:@selector(handRightFuncButton:) forControlEvents:UIControlEventTouchDown];
    [self.rightFuncButton setFrame:CGRectMake(w - width - width - 4, top, width + 4, height)];
    [self addSubview: self.rightFuncButton];
    
    //space
    self.spaceButton = [self whiteButtonWithTitle:@"" image:nil];
    [self.spaceButton setFrame:CGRectMake(CGRectGetMaxX(self.nextIMEButton.frame), top, CGRectGetMinX(self.rightFuncButton.frame) - CGRectGetMaxX(self.nextIMEButton.frame), height)];
    [self.spaceButton addTarget:self action:@selector(handRightFuncButton:) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview: self.spaceButton];
}

-(void) setKanaLayout {
    NSLog(@"Keyboard-setKanaLayout");
    NSArray *keys = nil;
    if(_leftFuncOn) {
        keys = @[
                 @[@[@"1"], @[@"2"], @[@"3"], @[@"4"], @[@"5"], @[@"6"], @[@"7"], @[@"8"], @[@"9"], @[@"0"]/*, @[@"Del"]*/],
                 @[@[@"@"], @[@"#"], @[@"¥"], @[@"-"], @[@"*"], @[@"("], @[@")"], @[@"「"], @[@"」"]/*, @[@"Return"]*/],
                 @[/*@[@"Shift"],*/ @[@"^_^"], @[@"%"], @[@"〜"], @[@"…"], @[@"/"], @[@";"], @[@":"], @[@"！", @"、"], @[@"？", @"。"]]
                 ];
    } else if(_rightFuncOn){
        keys = @[
                 @[@[@"q"], @[@"w"], @[@"e"], @[@"r"], @[@"t"], @[@"y"], @[@"u"], @[@"i"], @[@"o"], @[@"p"]/*, @[@"Del"]*/],
                 @[@[@"a"], @[@"s"], @[@"d"], @[@"f"], @[@"g"], @[@"h"], @[@"j"], @[@"k"], @[@"l"]/*, @[@"Return"]*/],
                 @[/*@[@"Shift"],*/ @[@"z"], @[@"x"], @[@"c"], @[@"v"], @[@"b"], @[@"n"], @[@"m"], @[@"!", @","], @[@"?", @"."], @[@"-"]]
                 ];
    } else {
        keys = @[
                 @[@[@"q"], @[@"w"], @[@"e"], @[@"r"], @[@"t"], @[@"y"], @[@"u"], @[@"i"], @[@"o"], @[@"p"]/*, @[@"Del"]*/],
                 @[@[@"a"], @[@"s"], @[@"d"], @[@"f"], @[@"g"], @[@"h"], @[@"j"], @[@"k"], @[@"l"]/*, @[@"Return"]*/],
                 @[/*@[@"Shift"],*/ @[@"z"], @[@"x"], @[@"c"], @[@"v"], @[@"b"], @[@"n"], @[@"m"], @[@"！", @"、"], @[@"？", @"。"], @[@"ー"]]
                 ];
    }
    
    CGFloat w = [UIScreen mainScreen].bounds.size.width;
    CGFloat width = MIN(MAX(w/11, 65), 85);
    CGFloat height = width;
    CGFloat leftMargin = (w - width * 11) / 2;
    CGFloat top = AccessoryViewHeightDefault;
    
    NSUInteger row = 0;
    for(NSArray *keyRow in keys) {
        NSUInteger left = leftMargin;
        if(row == 1) {
            left += width / 2;
        }
        
        if(row == 2) {
            //shift
            //shift
            if(_shiftOn) {
                self.shiftButton = [self darkgrayButtonWithTitle:@"" image: [UIImage imageNamed:@"shift_on"]];
            } else {
                self.shiftButton = [self whiteButtonWithTitle:nil image:[UIImage imageNamed:@"shift"]];
            }
            [self.shiftButton setFrame:CGRectMake(left, top, width, height)];
            [self addSubview: self.shiftButton];
            [self.shiftButton addTarget:self action:@selector(handleShiftButton:) forControlEvents:UIControlEventTouchDown];
            left += width;
        }
        
        for(NSArray *keys in keyRow) {
            NSString *keyTitle = [keys firstObject];
            if([keys count] == 2) {
                if(!_shiftOn) {
                    keyTitle = [NSString stringWithFormat:@"%@\n%@", keyTitle, [keys objectAtIndex:1]];
                }
            }
            if(_shiftOn) {
                keyTitle = [keyTitle uppercaseString];
            }
            KeyboardButton *button = [self whiteButtonWithTitle:keyTitle image:nil];
            [button addTarget:self action:@selector(handleButtonUp:) forControlEvents:UIControlEventTouchUpInside];
            [button setFrame:CGRectMake(left, top, width, height)];
            [self addSubview: button];
            left += width;
        }
        if(row == 0) {
            KeyboardButton *button = [self darkgrayButtonWithTitle:@"" image: [UIImage imageNamed:@"del"]];
            [button setFrame:CGRectMake(left, top, w - leftMargin - left, height)];
            [self addSubview: button];
            [button addTarget:self action:@selector(handleDeleteButton:) forControlEvents:UIControlEventTouchDown];
        } else if(row == 1) {
            self.returnButton = [self darkgrayButtonWithTitle:@"改行" image: nil];
            [self.returnButton setFrame:CGRectMake(left, top, w - leftMargin - left, height)];
            [self addSubview: self.returnButton];
            [self.returnButton addTarget:self action:@selector(handleReturn:) forControlEvents:UIControlEventTouchDown];
        }
        
        row++;
        top += height;
    }
    NSUInteger left = leftMargin;
    
    KeyboardButton *button = nil;
    if(!_leftFuncOn) {
        button = [self darkgrayButtonWithTitle:@".?123" image:nil];
    } else {
        button = [self darkgrayButtonWithTitle:@"あいう" image:nil];
    }
    [button setFrame:CGRectMake(left, top, width, height)];
    [button addTarget:self action:@selector(handLeftFuncButton:) forControlEvents:UIControlEventTouchDown];
    [self addSubview: button];
    left += width;
    
    button = [self darkgrayButtonWithTitle:nil image: [UIImage imageNamed:@"hand"]];
    [button setFrame:CGRectMake(left, top, width, height)];
    [self addSubview: button];
    [button addTarget:self action:@selector(handHandwritingButton:) forControlEvents:UIControlEventTouchDown];
    left += width;
    
    button = [self darkgrayButtonWithTitle:nil image:[UIImage imageNamed:@"keyboard"]];
    [button setFrame:CGRectMake(w - width, top, width, height)];
    [button addTarget:self action:@selector(handleCloseButton:) forControlEvents:UIControlEventAllTouchEvents];
    [self addSubview: button];
    
    self.nextIMEButton = [self darkgrayButtonWithTitle:nil image:[UIImage imageNamed:@"global"]];
    [self.nextIMEButton setFrame:CGRectMake(left, top, width, height)];
    [self.nextIMEButton addTarget:self action:@selector(handleInputModeListFromView:withEvent:) forControlEvents:UIControlEventAllTouchEvents];
    [self addSubview: self.nextIMEButton];
    
    //right func button
    if(!_leftFuncOn && !_rightFuncOn) {
        self.rightFuncButton = [self darkgrayButtonWithTitle:@"abc" image:nil];
    } else {
        self.rightFuncButton = [self darkgrayButtonWithTitle:@"あいう" image:nil];
    }
    [self.rightFuncButton addTarget:self action:@selector(handRightFuncButton:) forControlEvents:UIControlEventTouchDown];
    [self.rightFuncButton setFrame:CGRectMake(w - width - width - 4, top, width + 4, height)];
    [self addSubview: self.rightFuncButton];
    
    //space
    self.spaceButton = [self whiteButtonWithTitle:@"" image:nil];
    [self.spaceButton setFrame:CGRectMake(CGRectGetMaxX(self.nextIMEButton.frame), top, CGRectGetMinX(self.rightFuncButton.frame) - CGRectGetMaxX(self.nextIMEButton.frame), height)];
    [self.spaceButton addTarget:self action:@selector(handRightFuncButton:) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview: self.spaceButton];
    
}

#pragma mark - Button Event
-(void) handleHandwritingClearButton:(id) sender {
    [_drawView clearPoints];
    [_handwritingController clear];
}

-(void) handleQwertButton:(id)sender {
    [self setInputMode:KeyboardInputModeKana];
}

-(void) handHandwritingButton:(id)sender {
    [self setInputMode:KeyboardInputModeHandWriting];
}

-(void) handleCloseButton:(id)sender {
    [self.delegate dismissKeyboard];
}

-(void) handleSpaceButton :(id)sender{
    NSString *markedText = self.markedText;
    NSUInteger length = markedText.length;
    if (length == 0) {
        [self.delegate keyboardView:self didAcceptCandidate:@" "];
    } else {
        [self.candidateBar selectNextCandidate];
    }
}

-(void) handLeftFuncButton:(id)sender {
    _leftFuncOn = !_leftFuncOn;
    [self setInputMode:self.inputMode];
}

-(void) handRightFuncButton:(id)sender {
    if(_leftFuncOn) {
        _leftFuncOn = NO;
        _rightFuncOn = NO;
    } else {
        _rightFuncOn = !_rightFuncOn;
        if(!_rightFuncOn) {
            _leftFuncOn = NO;
        }
    }
    
    [self setInputMode:self.inputMode];
}

-(void) handleShiftButton:(id)sender {
    _shiftOn = !_shiftOn;
    [self setInputMode:self.inputMode];
}

-(void) handleDeleteButton:(id)sender {
    NSString *markedText = self.markedText;
    NSUInteger length = markedText.length;
    if (length == 0) {
        [self.delegate keyboardViewDidInputDelete:self];
        [self.spaceButton setTitle:@"" forState:UIControlStateNormal];
    } else {
        [self.inputEngine backspace];
        
        self.markedText = [markedText substringToIndex:length - 1];
        if (self.markedText.length > 0) {
            [self.inputManager requestCandidatesForInput:self.markedText];
        } else {
            [self.spaceButton setTitle:@"" forState:UIControlStateNormal];
        }
    }
}

-(void) handleButtonUp:(id) button {
    NSString *input = [button titleForState:UIControlStateNormal];
    input = [[input componentsSeparatedByString:@"\n"] lastObject];
    NSLog(@"key:%@", input);
    if (self.inputMode == KeyboardInputModeKana) {
        if(_rightFuncOn) {
          [self.delegate keyboardView:self didAcceptCandidate:input];
        } else {
            [self.inputEngine insertCharacter:input];
        }
    } else {
        [self.delegate keyboardView:self didAcceptCandidate:input];
    }
}
#pragma mark -
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
    
    button.titleLabel.font = self.buttonTitleFont;
    button.titleLabel.textAlignment = NSTextAlignmentCenter;
    button.titleLabel.numberOfLines = 2;
    [button setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    
    [button setBackgroundImage:backgroundImage forState:UIControlStateNormal];
    [button setBackgroundImage:highlightedBackgroundImage forState:UIControlStateHighlighted];
    
    [button setTitle:title forState:UIControlStateNormal];
    [button setImage:image forState:UIControlStateNormal];
    
    return button;
}

- (UIFont *)buttonTitleFont {
    return [UIFont systemFontOfSize:22];
}
@end
