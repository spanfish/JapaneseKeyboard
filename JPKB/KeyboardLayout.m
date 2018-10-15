//
//  KeyboardLayout.m
//  JapaneseKeyboardKit
//
//  Created by kishikawa katsumi on 2014/09/28.
//  Copyright (c) 2014 kishikawa katsumi. All rights reserved.
//

#import "KeyboardLayout.h"
#import "KeyboardView.h"
#import "KeyboardButton.h"
#import "DrawView.h"
#import "HandWritingController.h"

@interface KeyboardLayout () {
    @protected
    CGFloat keyboardViewWidth;
    BOOL _shiftOn;
    UIView *_keyboardView;
}
@property(nonatomic) DrawView *handWritingDrawView;
@property (nonatomic) NSArray *inputButtons;
@property (nonatomic) NSArray *functionButtons;

@property (nonatomic) KeyboardButton *nextKeyboardButton;
@property (nonatomic) KeyboardButton *toggleInputModeButton;
@property (nonatomic) KeyboardButton *shiftButton;
@property (nonatomic) KeyboardButton *spaceButton;
@property (nonatomic) KeyboardButton *commaButton;
@property (nonatomic) KeyboardButton *periodButton;
@property (nonatomic) KeyboardButton *deleteButton;
@property (nonatomic) KeyboardButton *returnButton;
@property (nonatomic) KeyboardButton *dismissButton;
@property (nonatomic) KeyboardButton *previousCandidateButton;
@property (nonatomic) KeyboardButton *nextCandidateButton;
@property (nonatomic) KeyboardButton *previousCursorButton;
@property (nonatomic) KeyboardButton *nextCursorButton;
@property (nonatomic) KeyboardButton *handwritingButton;
@property (nonatomic) KeyboardButton *handwritingClearButton;
@property (nonatomic) KeyboardButton *handwritingUndoButton;

@property (nonatomic) NSArray *keycaps;
@property (nonatomic) UIFont *buttonTitleFont;

@property (nonatomic) UIImage *nextKeyboardImage;
@property (nonatomic) UIImage *shiftImage;
@property (nonatomic) UIImage *highlightedShiftImage;
@property (nonatomic) UIImage *shiftLockImage;
@property (nonatomic) UIImage *deleteImage;
@property (nonatomic) UIImage *returnImage;
@property (nonatomic) UIImage *dismissImage;

@property (nonatomic) CGRect nextKeyboardButtonFrame;
@property (nonatomic) CGRect toggleInputModeButtonFrame;
@property (nonatomic) CGRect shiftButtonFrame;
@property (nonatomic) CGRect spaceButtonFrame;
@property (nonatomic) CGRect commaButtonFrame;
@property (nonatomic) CGRect periodButtonFrame;
@property (nonatomic) CGRect deleteButtonFrame;
@property (nonatomic) CGRect returnButtonFrame;
@property (nonatomic) CGRect dismissButtonFrame;
@property (nonatomic) CGRect previousCandidateButtonFrame;
@property (nonatomic) CGRect nextCandidateButtonFrame;
@property (nonatomic) CGRect previousCursorButtonFrame;
@property (nonatomic) CGRect nextCursorButtonFrame;
@property (nonatomic) CGRect handwritingButtonFrame;
@property (nonatomic) CGRect handwritingClearButtonFrame;
@property (nonatomic) CGRect handwritingUndoButtonFrame;

@end

@implementation KeyboardLayout

+ (KeyboardLayout *)keyboardLayout
{
    KeyboardLayout *layout = [[self alloc] init];
    return layout;
}

- (instancetype)initWithDelegate:(id) delegate {
    self = [super init];
    if (self) {
//        [self setupInputButtons];
//        [self setupFunctionButtons];
//        [self setupHandwritingView];
        self.delegate = delegate;
    }
    
    return self;
}

#pragma mark -
-(void) setupHandwritingView {
    self.handWritingDrawView = [[DrawView alloc] initWithFrame:CGRectMake(100, 0, 300, 300)];
    [self.handWritingDrawView setTranslatesAutoresizingMaskIntoConstraints:NO];
}

- (void)setupInputButtons
{
    NSArray *keycaps = self.keycaps;
    
    NSMutableArray *inputButtons = [[NSMutableArray alloc] init];
    NSUInteger index = 0;
    for (NSUInteger i = 0; i < keycaps.count; i++) {
        NSArray *row = keycaps[i];
        for (NSUInteger j = 0; j < row.count; j++) {
            NSArray *col = row[j];
            NSString *title = [col componentsJoinedByString:@"\n"];
            
            KeyboardButton *button = [self whiteButtonWithTitle:title image:nil];
            button.layoutMargins = UIEdgeInsetsMake(4, 4, 4, 4);
            button.keyIndex = index;
            [inputButtons addObject:button];
            
            index++;
        }
    }
    
    self.inputButtons = inputButtons;
}

- (void)setupFunctionButtons
{
    NSMutableArray *functionButtons = [[NSMutableArray alloc] init];
    KeyboardButton *button;
    
    button = [self darkgrayButtonWithTitle:nil image:nil];
    button.keyIndex = KeyboardButtonIndexNextKeyboard;
    [functionButtons addObject:button];
    self.nextKeyboardButton = button;
    
    button = [self darkgrayButtonWithTitle:@"123" image:nil];
    [button setTitle:@"ABC" forState:UIControlStateSelected];
    [button setTitle:@"ABC" forState:UIControlStateHighlighted | UIControlStateSelected];
    [button setBackgroundImage:[UIImage imageNamed:@"key_white"] forState:UIControlStateHighlighted | UIControlStateSelected];
    button.keyIndex = KeyboardButtonIndexToggleInputMode;
    [functionButtons addObject:button];
    self.toggleInputModeButton = button;
    
    button = [self darkgrayButtonWithTitle:nil image:nil];
    [button setBackgroundImage:[UIImage imageNamed:@"key_white"] forState:UIControlStateSelected];
    [button setBackgroundImage:[UIImage imageNamed:@"key_white"] forState:UIControlStateHighlighted | UIControlStateSelected];
    button.keyIndex = KeyboardButtonIndexShift;
    [functionButtons addObject:button];
    self.shiftButton = button;
    
    button = [self whiteButtonWithTitle:NSLocalizedString(@"space", nil) image:nil];
    button.keyIndex = KeyboardButtonIndexSpace;
    [functionButtons addObject:button];
    self.spaceButton = button;
    
    button = [self whiteButtonWithTitle:NSLocalizedString(@",", nil) image:nil];
    button.keyIndex = KeyboardButtonIndexComma;
    [functionButtons addObject:button];
    self.commaButton = button;
    
    button = [self whiteButtonWithTitle:NSLocalizedString(@".", nil) image:nil];
    button.keyIndex = KeyboardButtonIndexPeriod;
    [functionButtons addObject:button];
    self.periodButton = button;
    
    button = [self darkgrayButtonWithTitle:nil image:nil];
    button.keyIndex = KeyboardButtonIndexDelete;
    [functionButtons addObject:button];
    self.deleteButton = button;
    
    button = [self blueButtonWithTitle:nil image:nil];
    button.keyIndex = KeyboardButtonIndexReturn;
    [functionButtons addObject:button];
    self.returnButton = button;
    
    button = [self darkgrayButtonWithTitle:nil image:nil];
    button.keyIndex = KeyboardButtonIndexDismiss;
    [functionButtons addObject:button];
    self.dismissButton = button;
    
    button = [self darkgrayButtonWithTitle:@"前候補" image:nil];
    button.keyIndex = KeyboardButtonIndexPreviousCandidate;
    [functionButtons addObject:button];
    self.previousCandidateButton = button;
    
    button = [self darkgrayButtonWithTitle:@"次候補" image:nil];
    button.keyIndex = KeyboardButtonIndexNextCandidate;
    [functionButtons addObject:button];
    self.nextCandidateButton = button;
    
    button = [self darkgrayButtonWithTitle:@"＜" image:nil];
    button.keyIndex = KeyboardButtonIndexPreviousCursor;
    [functionButtons addObject:button];
    self.previousCursorButton = button;
    
    button = [self darkgrayButtonWithTitle:@"＞" image:nil];
    button.keyIndex = KeyboardButtonIndexNextCursor;
    [functionButtons addObject:button];
    self.nextCursorButton = button;
    
    //handwritingButton
    button = [self darkgrayButtonWithTitle:@"手書き" image:nil];
    button.keyIndex = KeyboardButtonIndexHandwriting;
    [functionButtons addObject:button];
    self.handwritingButton = button;
    
    button = [self darkgrayButtonWithTitle:@"手書き削除" image:nil];
    button.keyIndex = KeyboardButtonIndexHandwritingClear;
    [functionButtons addObject:button];
    self.handwritingClearButton = button;
    
    button = [self darkgrayButtonWithTitle:@"" image: [UIImage imageNamed:@"undo"]];
    button.keyIndex = KeyboardButtonIndexHandwritingUndo;
    [functionButtons addObject:button];
    self.handwritingUndoButton = button;
    
    self.functionButtons = functionButtons;
}

- (void)setupKeyboardButtonsWithView:(UIView *)view
{
//    keyboardViewWidth = view.frame.size.width;
//    
//    [view addSubview:self.handWritingDrawView];
//    HandWritingController *controller = [HandWritingController controller];
//    controller.drawView = self.handWritingDrawView;
//    NSLayoutConstraint *leftSideConstraint = [NSLayoutConstraint constraintWithItem: self.handWritingDrawView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeLeft multiplier:1.0 constant:keyboardViewWidth/10];
//    NSLayoutConstraint *rightSideConstraint = [NSLayoutConstraint constraintWithItem:self.handWritingDrawView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeRight multiplier:1.0 constant:-keyboardViewWidth/10];
//    NSLayoutConstraint *bottomConstraint = [NSLayoutConstraint constraintWithItem:self.handWritingDrawView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0.0];
//    NSLayoutConstraint *topConstraint = [NSLayoutConstraint constraintWithItem:self.handWritingDrawView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeTop multiplier:1.0 constant:40.0];
//    
//    [view addConstraints:@[leftSideConstraint, rightSideConstraint, bottomConstraint, topConstraint]];
//    self.handWritingDrawView.hidden = YES;
//    NSArray *buttons = [self.inputButtons arrayByAddingObjectsFromArray:self.functionButtons];
//    for (KeyboardButton *button in buttons) {
//        [button addTarget:view action:@selector(buttonDidTouchDown:) forControlEvents:UIControlEventTouchDown];
//        [button addTarget:view action:@selector(buttonDidTouchUp:) forControlEvents:UIControlEventTouchUpInside];
//        [view addSubview:button];
//    }
//    
//    [self.shiftButton addTarget:view action:@selector(buttonDidTouchDownRepeat:) forControlEvents:UIControlEventTouchDownRepeat];
    
    
}

#pragma mark -
-(void) setKanaLayout {
    NSLog(@"Keyboard-setKanaLayout");
    NSArray *keys = @[
             @[@[@"q"], @[@"w"], @[@"e"], @[@"r"], @[@"t"], @[@"y"], @[@"u"], @[@"i"], @[@"o"], @[@"p"]/*, @[@"Del"]*/],
             @[@[@"a"], @[@"s"], @[@"d"], @[@"f"], @[@"g"], @[@"h"], @[@"j"], @[@"k"], @[@"l"]/*, @[@"Return"]*/],
             @[/*@[@"Shift"],*/ @[@"z"], @[@"x"], @[@"c"], @[@"v"], @[@"b"], @[@"n"], @[@"m"], @[@"！", @"、"], @[@"？", @"。"], @[@"ー"]]
             ];
    
    NSUInteger left = 0;
    NSUInteger top = 0;
    NSUInteger width = 65;
    NSUInteger height = 65;
    for(NSArray *keyRow in keys) {
        left = 0;
        for(NSArray *keys in keyRow) {
            NSString *keyTitle = [keys firstObject];
            if([keys count] == 2) {
                if(!_shiftOn) {
                    keyTitle = [NSString stringWithFormat:@"%@\n%@", keyTitle, [keys objectAtIndex:1]];
                }
            }
            
            KeyboardButton *button = [self whiteButtonWithTitle:keyTitle image:nil];
            [button setFrame:CGRectMake(left, top, width, height)];
            [self.delegate buttonDidCreated:button];
            left += width;
        }
        top += height;
    }
    //del
    //shift
    //
    KeyboardButton *button = [self darkgrayButtonWithTitle:nil image:[UIImage imageNamed:@"global"]];
    [button setFrame:CGRectMake(left, top, 65, 65)];
    [button addTarget:self action:@selector(buttonDidKeyDown:) forControlEvents:UIControlEventAllTouchEvents];
    button.keyIndex = KeyboardButtonIndexNextKeyboard;
    [self.delegate buttonDidCreated:button];
}

-(void) buttonDidKeyDown:(KeyboardButton *) button {
//    [self.delegate buttonDidTouchDown:button];
}
//KeyboardInputModeKana,
//KeyboardInputModeAlphabet,
//KeyboardInputModeNumberPunctual,
//KeyboardInputModeSymbol,
//KeyboardInputModeNumber,
//KeyboardInputModeEmail,
//KeyboardInputModeKataKana,
//KeyboardInputModeHandWriting

- (void)updateKeycaps {
    
    
    if(self.inputMode == KeyboardInputModeHandWriting) {
        //NSArray *buttons = [self.inputButtons arrayByAddingObjectsFromArray:self.functionButtons];
        
        //clear
        
        //
        return;
    }
    //手書き
    self.handWritingDrawView.hidden = YES;
    [self.handwritingButton setImage:nil forState:UIControlStateNormal];
    [self.handwritingButton setTitle:@"手書き" forState:UIControlStateNormal];
    
    NSArray *keycaps = self.keycaps;
    
    NSUInteger index = 0;
    for (NSUInteger i = 0; i < keycaps.count; i++) {
        NSArray *row = keycaps[i];
        for (NSUInteger j = 0; j < row.count; j++) {
            NSArray *col = row[j];
            NSString *title = [col componentsJoinedByString:@"\n"];
            KeyboardButton *button = self.inputButtons[index];
            [button setTitle:title forState:UIControlStateNormal];
            
            index++;
        }
    }
    
    self.toggleInputModeButton.selected = self.inputMode == KeyboardInputModeNumberPunctual;
}

- (CGRect)inputButtonFrameForRow:(NSInteger)row column:(NSInteger)column
{
    return CGRectZero;
}

- (void)updateFunctionButtonFrames
{
    
}

- (void)updateButtonLayout
{
    NSArray *keycaps = self.keycaps;
    
    NSUInteger index = 0;
    for (NSUInteger i = 0; i < keycaps.count; i++) {
        NSArray *row = keycaps[i];
        for (NSUInteger j = 0; j < row.count; j++) {
            KeyboardButton *button = self.inputButtons[index];
            
            button.frame = [self inputButtonFrameForRow:i column:j];
            button.hidden = CGRectIsEmpty(button.frame);
            
            button.titleLabel.font = self.buttonTitleFont;
            
            index++;
        }
    }
    
    self.nextKeyboardButton.frame = self.nextKeyboardButtonFrame;
    [self.nextKeyboardButton setImage:self.nextKeyboardImage forState:UIControlStateNormal];
    
    self.toggleInputModeButton.frame = self.toggleInputModeButtonFrame;
    
    self.shiftButton.frame = self.shiftButtonFrame;
    [self.shiftButton setImage:self.shiftImage forState:UIControlStateNormal];
    
    self.handwritingButton.frame = self.handwritingButtonFrame;
    self.handwritingClearButton.frame = self.handwritingClearButtonFrame;
    self.handwritingUndoButton.frame = self.handwritingUndoButtonFrame;
    
    self.spaceButton.frame = self.spaceButtonFrame;
    self.commaButton.frame = self.commaButtonFrame;
    self.periodButton.frame = self.periodButtonFrame;
    
    self.deleteButton.frame = self.deleteButtonFrame;
    [self.deleteButton setImage:self.deleteImage forState:UIControlStateNormal];
    
    self.returnButton.frame = self.returnButtonFrame;
    [self.returnButton setImage:self.returnImage forState:UIControlStateNormal];
    
    self.dismissButton.frame = self.dismissButtonFrame;
    [self.dismissButton setImage:self.dismissImage forState:UIControlStateNormal];
    
    self.previousCandidateButton.frame = self.previousCandidateButtonFrame;
    self.nextCandidateButton.frame = self.nextCandidateButtonFrame;
    
    self.previousCursorButton.frame = self.previousCursorButtonFrame;
    self.nextCursorButton.frame = self.nextCursorButtonFrame;
    
    for (KeyboardButton *button in self.functionButtons) {
        button.hidden = CGRectIsEmpty(button.frame);
        button.titleLabel.font = self.buttonTitleFont;
    }
    
    if(self.inputMode == KeyboardInputModeHandWriting) {
        for (KeyboardButton *button in self.inputButtons) {
            button.hidden = YES;
        }
        
        for (KeyboardButton *button in self.functionButtons) {
            button.hidden = button != self.handwritingButton;
        }
        
        [self.handwritingButton setImage:[UIImage imageNamed:@"keyboard"] forState:UIControlStateNormal];
        [self.handwritingButton setTitle:@"" forState:UIControlStateNormal];
        self.handWritingDrawView.hidden = NO;
        [self.handWritingDrawView setNeedsLayout];
        [self.handWritingDrawView setNeedsDisplay];
        
        self.deleteButton.hidden = NO;
        self.spaceButton.hidden = NO;
        self.handwritingClearButton.hidden = NO;
        self.handwritingUndoButton.hidden = NO;
    } else {
        self.handwritingClearButton.hidden = YES;
        self.handwritingUndoButton.hidden = YES;
    }
}

- (void)updateShiftButton
{
    if (self.shiftLocked) {
        self.shiftButton.selected = YES;
        [self.shiftButton setImage:self.shiftLockImage forState:UIControlStateNormal];
        [self.shiftButton setImage:self.shiftLockImage forState:UIControlStateSelected];
        [self.shiftButton setImage:self.shiftLockImage forState:UIControlStateHighlighted | UIControlStateSelected];
    } else if (self.shifted) {
        self.shiftButton.selected = YES;
        [self.shiftButton setImage:self.shiftImage forState:UIControlStateNormal];
        [self.shiftButton setImage:self.highlightedShiftImage forState:UIControlStateSelected];
        [self.shiftButton setImage:self.highlightedShiftImage forState:UIControlStateHighlighted | UIControlStateSelected];
    } else {
        self.shiftButton.selected = NO;
        [self.shiftButton setImage:self.shiftImage forState:UIControlStateNormal];
        [self.shiftButton setImage:nil forState:UIControlStateSelected];
        [self.shiftButton setImage:nil forState:UIControlStateHighlighted | UIControlStateSelected];
    }
}

#pragma mark -

- (void)setMetrics:(KeyboardMetrics)metrics
{
    _metrics = metrics;
    [self updateFunctionButtonFrames];
    [self updateButtonLayout];
}

-(void) clearKeys {
    NSArray *keycaps = self.keycaps;
    
    NSUInteger index = 0;
    for (NSUInteger i = 0; i < keycaps.count; i++) {
        NSArray *row = keycaps[i];
        for (NSUInteger j = 0; j < row.count; j++) {
            KeyboardButton *button = self.inputButtons[index];
            button.frame = CGRectZero;
            index++;
        }
    }
}

- (void)setInputMode:(KeyboardInputMode)inputMode
{
    _inputMode = inputMode;
//    [self updateKeycaps];
    //[self updateFunctionButtonFrames];
    
    switch (self.inputMode) {
        case KeyboardInputModeKana:
            [self setKanaLayout];
            break;
        case KeyboardInputModeAlphabet:
            
            break;
        case KeyboardInputModeNumberPunctual:
            
            break;
        case KeyboardInputModeNumber:
            
            break;
        case KeyboardInputModeEmail:
            
            break;
        case KeyboardInputModeKataKana:
            
            break;
        case KeyboardInputModeHandWriting:
            
            break;
        default:
            break;
    }
}

- (void)setShifted:(BOOL)shifted
{
    _shifted = shifted;
    [self updateShiftButton];
}

- (void)setShiftLocked:(BOOL)shiftLocked
{
    _shiftLocked = shiftLocked;
    if (!shiftLocked) {
        _shifted = NO;
    }
    [self updateShiftButton];
}

#pragma mark -

- (UIFont *)buttonTitleFont
{
    return [UIFont fontWithName:@"HiraKakuProN-W3" size:16.0];;
}

- (UIImage *)nextKeyboardImage
{
    if (self.metrics == KeyboardMetricsDefault) {
        return [UIImage imageNamed:@"global_portrait_phone"];
    } else {
        return [UIImage imageNamed:@"global_landscape_phone"];
    }
}

- (UIImage *)shiftImage
{
    if (self.metrics == KeyboardMetricsDefault) {
        return [UIImage imageNamed:@"shift_portrait_phone"];
    } else {
        return [UIImage imageNamed:@"shift_landscape_phone"];
    }
}

- (UIImage *)highlightedShiftImage
{
    if (self.metrics == KeyboardMetricsDefault) {
        return [UIImage imageNamed:@"shift_portrait_phone_highlighted"];
    } else {
        return [UIImage imageNamed:@"shift_landscape_phone_highlighted"];
    }
}

- (UIImage *)shiftLockImage
{
    if (self.metrics == KeyboardMetricsDefault) {
        return [UIImage imageNamed:@"shift_lock_portrait_phone"];
    } else {
        return [UIImage imageNamed:@"shift_lock_landscape_phone"];
    }
}

- (UIImage *)deleteImage
{
    if (self.metrics == KeyboardMetricsDefault) {
        return [UIImage imageNamed:@"delete_portrait_skinny"];
    } else {
        return [UIImage imageNamed:@"delete_landscape_phone"];
    }
}

- (UIImage *)returnImage
{
    return [UIImage imageNamed:@"return_phone"];
}

- (UIImage *)dismissImage
{
    return [UIImage imageNamed:@"dismiss_landscape_phone"];
}

#pragma mark -

- (NSArray *)keycaps
{
    static NSArray *alphabet;
    if (!alphabet) {
        alphabet = @[
                     @[@[@"Q"], @[@"W"], @[@"E"], @[@"R"], @[@"T"], @[@"Y"], @[@"U"], @[@"I"], @[@"O"], @[@"P"]],
                     @[@[@"A"], @[@"S"], @[@"D"], @[@"F"], @[@"G"], @[@"H"], @[@"J"], @[@"K"], @[@"L"]],
                     @[@[@"Z"], @[@"X"], @[@"C"], @[@"V"], @[@"B"], @[@"N"], @[@"M"]],
                     ];
    }
    static NSArray *numberPunctual;
    if (!numberPunctual) {
        numberPunctual = @[
                           @[@[@"1"], @[@"2"], @[@"3"], @[@"4"], @[@"5"], @[@"6"], @[@"7"], @[@"8"], @[@"9"], @[@"0"]],
                           @[@[@"-"], @[@"/"], @[@":"], @[@";"], @[@"("], @[@")"], @[@"¥"], @[@"&"], @[@"@"]],
                           @[@[@"."], @[@","], @[@"?"], @[@"!"], @[@"'"], @[@"["], @[@"]"]],
                           ];
    }
    
    static NSArray *number;
    if (!number) {
        number = @[
                           @[@[@"1"], @[@"2"], @[@"3"]],
                           @[@[@"4"], @[@"5"], @[@"6"]],
                           @[@[@"7"], @[@"8"], @[@"9"]],
                           @[@[@"0"]],
                           ];
    }
    
    if (self.inputMode == KeyboardInputModeKana) {
        return alphabet;
    } else if (self.inputMode == KeyboardInputModeNumber) {
        return number;
    } else {
        return numberPunctual;
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

@end

@implementation KeyboardLayoutPhone5

- (CGRect)inputButtonFrameForRow:(NSInteger)row column:(NSInteger)column
{
    if (self.metrics == KeyboardMetricsDefault) {
        CGFloat top = 40.0;
        CGFloat left = 0.0;
        CGFloat width = 32.0;
        CGFloat height = 55.0;
        if (row == 1) {
            left = 16.0;
        } else if (row == 2) {
            left = 48.5;
        }
        return CGRectMake(left + column * width, top + height * row, width, height);
    } else if (self.metrics == KeyboardMetricsLandscape568) {
        CGFloat top = 30.0;
        CGFloat left = 0.0;
        CGFloat width = 56.5;
        CGFloat height = 41.0;
        if (row == 1) {
            left = 28.0;
        } else if (row == 2) {
            left = 83.5;
        }
        return CGRectMake(left + column * width, top + height * row, width, height);
    } else {
        CGFloat top = 30.0;
        CGFloat left = 0.0;
        CGFloat width = 48.0;
        CGFloat height = 41.0;
        if (row == 1) {
            left = 24.0;
        } else if (row == 2) {
            left = 72.0;
        }
        return CGRectMake(left + column * width, top + height * row, width, height);
    }
}

- (void)updateFunctionButtonFrames
{
    if (self.metrics == KeyboardMetricsDefault) {
        CGFloat top = 40.0;
        CGFloat width = 45.5;
        CGFloat height = 55.0;
        
        self.toggleInputModeButtonFrame = CGRectMake(0.0, top + height * 3, width, height);
        self.nextKeyboardButtonFrame = CGRectMake(width, top + height * 3, width, height);
        self.shiftButtonFrame = CGRectMake(0.0, top + height * 2, width, height);
        self.spaceButtonFrame = CGRectMake(width * 2, top + height * 3, width * 2, height);
        self.commaButtonFrame = CGRectMake(width * 4, top + height * 3, width, height);
        self.periodButtonFrame = CGRectMake(width * 5, top + height * 3, width, height);
        self.deleteButtonFrame = CGRectMake(width * 6, top + height * 2, width, height);
        self.returnButtonFrame = CGRectMake(width * 6, top + height * 3, width, height);
        self.previousCandidateButtonFrame = CGRectZero;
        self.nextCandidateButtonFrame = CGRectZero;
        self.previousCursorButtonFrame = CGRectZero;
        self.nextCursorButtonFrame = CGRectZero;
        self.dismissButtonFrame = CGRectZero;
    } else if (self.metrics == KeyboardMetricsLandscape568) {
        CGFloat top = 30.0;
        CGFloat width = 58.0;
        CGFloat height = 41.0;
        
        self.toggleInputModeButtonFrame = CGRectMake(0.0, top + height * 3, width, height);
        self.nextKeyboardButtonFrame = CGRectMake(56.0, top + height * 3, 84.0, height);
        self.shiftButtonFrame = CGRectMake(0.0, top + height * 2, 84.0, height);
        self.spaceButtonFrame = CGRectMake(139.5, top + height * 3, 56.0 * 4 + 1.5, height);
        self.commaButtonFrame = CGRectMake(141.0 + 56.0 * 4, top + height * 3, width, height);
        self.periodButtonFrame = CGRectMake(142.0 + 56.0 * 5, top + height * 3, width, height);
        self.deleteButtonFrame = CGRectMake(87.0 + 56.0 * 7, top + height * 2, 86.0, height);
        self.returnButtonFrame = CGRectMake(87.0 + 56.0 * 7, top + height * 3, 86.0, height);
        self.previousCandidateButtonFrame = CGRectZero;
        self.nextCandidateButtonFrame = CGRectZero;
        self.previousCursorButtonFrame = CGRectZero;
        self.nextCursorButtonFrame = CGRectZero;
        self.dismissButtonFrame = CGRectZero;
    } else {
        CGFloat top = 30.0;
        CGFloat width = 48.0;
        CGFloat height = 41.0;
        
        self.toggleInputModeButtonFrame = CGRectMake(0.0, top + height * 3, width, height);
        self.nextKeyboardButtonFrame = CGRectMake(width, top + height * 3, width, height);
        self.shiftButtonFrame = CGRectMake(0.0, top + height * 2, width, height);
        self.spaceButtonFrame = CGRectMake(width * 2, top + height * 3, width * 5, height);
        self.commaButtonFrame = CGRectMake(width * 7, top + height * 3, width, height);
        self.periodButtonFrame = CGRectMake(width * 8, top + height * 3, width, height);
        self.deleteButtonFrame = CGRectMake(width * 9, top + height * 2, width, height);
        self.returnButtonFrame = CGRectMake(width * 9, top + height * 3, width, height);
        self.previousCandidateButtonFrame = CGRectZero;
        self.nextCandidateButtonFrame = CGRectZero;
        self.previousCursorButtonFrame = CGRectZero;
        self.nextCursorButtonFrame = CGRectZero;
        self.dismissButtonFrame = CGRectZero;
    }
}

@end

@implementation KeyboardLayoutPhone6

- (CGRect)inputButtonFrameForRow:(NSInteger)row column:(NSInteger)column
{
    if (self.metrics == KeyboardMetricsDefault) {
        CGFloat top = 40.0;
        CGFloat left = 0.0;
        CGFloat width = 37.5;
        CGFloat height = 55.0;
        if (row == 1) {
            left = 19.0;
        } else if (row == 2) {
            left = 56.5;
        }
        return CGRectMake(left + column * width, top + height * row, width, height);
    } else {
        CGFloat top = 30.0;
        CGFloat left = 56.0;
        CGFloat width = 55.5;
        CGFloat height = 41.0;
        if (row == 1) {
            left = 84.0;
        } else if (row == 2) {
            left = 139.5;
        }
        return CGRectMake(left + column * width, top + height * row, width, height);
    }
}

- (void)updateFunctionButtonFrames
{
    if (self.metrics == KeyboardMetricsDefault) {
        CGFloat top = 40.0;
        CGFloat width = 47.0;
        CGFloat height = 55.0;
        
        self.toggleInputModeButtonFrame = CGRectMake(0.0, top + height * 3, width, height);
        self.nextKeyboardButtonFrame = CGRectMake(width, top + height * 3, width, height);
        self.shiftButtonFrame = CGRectMake(0.0, top + height * 2, width, height);
        self.spaceButtonFrame = CGRectMake(width * 2, top + height * 3, width * 3, height);
        self.commaButtonFrame = CGRectMake(width * 5, top + height * 3, width, height);
        self.periodButtonFrame = CGRectMake(width * 6, top + height * 3, width, height);
        self.deleteButtonFrame = CGRectMake(width * 7, top + height * 2, width, height);
        self.returnButtonFrame = CGRectMake(width * 7, top + height * 3, width, height);
        self.previousCandidateButtonFrame = CGRectZero;
        self.nextCandidateButtonFrame = CGRectZero;
        self.previousCursorButtonFrame = CGRectZero;
        self.nextCursorButtonFrame = CGRectZero;
        self.dismissButtonFrame = CGRectZero;
    } else {
        CGFloat top = 30.0;
        CGFloat left = 139.5;
        CGFloat width = 58.0;
        CGFloat height = 41.0;
        
        self.toggleInputModeButtonFrame = CGRectMake(0.0, top + height * 3, width, height);
        self.nextKeyboardButtonFrame = CGRectMake(56.0, top + height * 3, 84.0, height);
        self.shiftButtonFrame = CGRectMake(56.0, top + height * 2, 84.0, height);
        self.spaceButtonFrame = CGRectMake(left, top + height * 3, 55.5 * 6, height);
        self.commaButtonFrame = CGRectMake(0.0, top + height * 2, width, height);
        self.periodButtonFrame = CGRectMake(54.0 + 55.5 * 10, top + height * 2, width, height);
        self.deleteButtonFrame = CGRectMake(139.0 + 55.5 * 7, top + height * 2, 82.0, height);
        self.returnButtonFrame = CGRectMake(left + 55.5 * 6, top + height * 3, 111.0, height);
        self.dismissButtonFrame = CGRectZero;
        self.previousCandidateButtonFrame = CGRectMake(0.0, top, width, height);
        self.nextCandidateButtonFrame = CGRectMake(0.0, top + height, width, height);
        self.previousCursorButtonFrame = CGRectMake(54.0 + 55.5 * 10, top, width, height);
        self.nextCursorButtonFrame = CGRectMake(54.0 + 55.5 * 10, top + height, width, height);
        self.dismissButtonFrame = CGRectMake(left + 55.5 * 8, top + height * 3, 84.0, height);
    }
}

@end

@implementation KeyboardLayoutPhone6Plus

- (CGRect)inputButtonFrameForRow:(NSInteger)row column:(NSInteger)column
{
    if (self.metrics == KeyboardMetricsDefault) {
        CGFloat top = 40.0;
        CGFloat left = 0.0;
        CGFloat width = 41.4;
        CGFloat height = 57.0;
        if (row == 1) {
            left = 20.5;
        } else if (row == 2) {
            left = 62.0;
        }
        return CGRectMake(left + column * width, top + height * row, width, height);
    } else {
        CGFloat top = 30.0;
        CGFloat left = 61.0;
        CGFloat width = 61.0;
        CGFloat height = 41.0;
        if (row == 1) {
            left = 91.5;
        } else if (row == 2) {
            left = 152.5;
        }
        return CGRectMake(left + column * width, top + height * row, width, height);
    }
}

- (void)updateFunctionButtonFrames
{
    if (self.metrics == KeyboardMetricsDefault) {
        CGFloat top = 40.0;
        CGFloat width = 51.7;
        CGFloat height = 57.0;
        
        self.toggleInputModeButtonFrame = CGRectMake(0.0, top + height * 3, width, height);
        self.nextKeyboardButtonFrame = CGRectMake(width, top + height * 3, width, height);
        self.shiftButtonFrame = CGRectMake(0.0, top + height * 2, width, height);
        self.spaceButtonFrame = CGRectMake(width * 2, top + height * 3, width * 3, height);
        self.commaButtonFrame = CGRectMake(width * 5, top + height * 3, width, height);
        self.periodButtonFrame = CGRectMake(width * 6, top + height * 3, width, height);
        self.deleteButtonFrame = CGRectMake(width * 7, top + height * 2, width, height);
        self.returnButtonFrame = CGRectMake(width * 7, top + height * 3, width, height);
        self.previousCandidateButtonFrame = CGRectZero;
        self.nextCandidateButtonFrame = CGRectZero;
        self.previousCursorButtonFrame = CGRectZero;
        self.nextCursorButtonFrame = CGRectZero;
        self.dismissButtonFrame = CGRectZero;
    } else {
        CGFloat top = 30.0;
        CGFloat left = 152.5;
        CGFloat width = 61.0;
        CGFloat height = 41.0;
        
        self.toggleInputModeButtonFrame = CGRectMake(0.0, top + height * 3, width, height);
        self.nextKeyboardButtonFrame = CGRectMake(width, top + height * 3, 92.0, height);
        self.shiftButtonFrame = CGRectMake(width, top + height * 2, 92.0, height);
        self.spaceButtonFrame = CGRectMake(left, top + height * 3, width * 7, height);
        self.commaButtonFrame = CGRectMake(0.0, top + height * 2, width, height);
        self.periodButtonFrame = CGRectMake(width * 11, top + height * 2, width, height);
        self.deleteButtonFrame = CGRectMake(left + width * 7, top + height * 2, 92.0, height);
        self.returnButtonFrame = CGRectMake(left + width * 7, top + height * 3, 92.0, height);
        self.dismissButtonFrame = CGRectZero;
        self.previousCandidateButtonFrame = CGRectMake(0.0, top, width, height);
        self.nextCandidateButtonFrame = CGRectMake(0.0, top + height, width, height);
        self.previousCursorButtonFrame = CGRectMake(width * 11, top, width, height);
        self.nextCursorButtonFrame = CGRectMake(width * 11, top + height, width, height);
        self.dismissButtonFrame = CGRectMake(width * 11, top + height * 3, width, height);
    }
}

@end

#pragma mark - iPad
@implementation KeyboardLayoutiPad

- (CGRect)inputButtonFrameForRow:(NSInteger)row column:(NSInteger)column
{
    if (self.metrics == KeyboardMetricsDefault) {
        CGFloat screenWidth = MIN([UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height);
        
        CGFloat top = 40.0;
        CGFloat left = 0.0;
        CGFloat width = screenWidth / 10;// 41.4;
        CGFloat height = width;//57.0;
        
        if(self.inputMode == KeyboardInputModeNumber) {
            left = (keyboardViewWidth - width * 3)/2;
            if(row == 3) {
                left += width;
            }
        } else {
            if (row == 1) {
                left = (keyboardViewWidth - width * 9) / 2; //20.5;
            } else if (row == 2) {
                //left = 62.0;
                left = (keyboardViewWidth - width * 7) / 2;
            }
        }
        return CGRectMake(left + column * width, top + height * row, width, height);
    } else {
        CGFloat top = 30.0;
        CGFloat left = 61.0;
        CGFloat width = 61.0;
        CGFloat height = 41.0;
        if (row == 1) {
            left = 91.5;
        } else if (row == 2) {
            left = 152.5;
        }
        return CGRectMake(left + column * width, top + height * row, width, height);
    }
}

- (void)updateFunctionButtonFrames
{
    if (self.metrics == KeyboardMetricsDefault) {
        CGFloat top = 40.0;
        CGFloat width = keyboardViewWidth / 10;//51.7;
        CGFloat height = width;//57.0;
        
        if(self.inputMode == KeyboardInputModeNumber) {
            self.handwritingButtonFrame = CGRectZero;
            self.toggleInputModeButtonFrame = CGRectZero;
            self.nextKeyboardButtonFrame = CGRectZero;
            self.shiftButtonFrame = CGRectZero;
            self.spaceButtonFrame =  CGRectZero;
            self.commaButtonFrame = CGRectZero;
            self.periodButtonFrame = CGRectZero;
            self.returnButtonFrame = CGRectZero;
            
            self.previousCandidateButtonFrame = CGRectZero;
            self.nextCandidateButtonFrame = CGRectZero;
            self.previousCursorButtonFrame = CGRectZero;
            self.nextCursorButtonFrame = CGRectZero;
            self.dismissButtonFrame = CGRectZero;
        } else {
            self.handwritingButtonFrame = CGRectMake(0, top + height * 3, width, height);
            self.handwritingClearButtonFrame = CGRectMake(keyboardViewWidth - width, top, width, height);
            self.handwritingUndoButtonFrame = CGRectMake(keyboardViewWidth - width, top + height, width, height);
            
            self.toggleInputModeButtonFrame = CGRectMake(width, top + height * 3, width, height);
            
            self.nextKeyboardButtonFrame = CGRectMake(width + width, top + height * 3, width, height);
            self.shiftButtonFrame = CGRectMake(0.0, top + height * 2, width, height);
            self.spaceButtonFrame = CGRectMake(width * 3, top + height * 3, keyboardViewWidth - width * 6, height);//CGRectMake(width * 2, top + height * 3, width * 3, height);
            self.commaButtonFrame = CGRectMake(keyboardViewWidth - width * 2/*width * 5*/, top + height * 3, width, height);
            self.periodButtonFrame = CGRectMake(keyboardViewWidth - width * 3/*width * 6*/, top + height * 3, width, height);
            self.deleteButtonFrame = CGRectMake(keyboardViewWidth - width,/* width * 7,*/ top + height * 2, width, height);
            self.returnButtonFrame = CGRectMake(keyboardViewWidth - width/*width * 7*/, top + height * 3, width, height);
            self.previousCandidateButtonFrame = CGRectZero;
            self.nextCandidateButtonFrame = CGRectZero;
            self.previousCursorButtonFrame = CGRectZero;
            self.nextCursorButtonFrame = CGRectZero;
            self.dismissButtonFrame = CGRectZero;
        }
        
    } else {
        CGFloat top = 30.0;
        CGFloat left = 152.5;
        CGFloat width = 61.0;
        CGFloat height = 41.0;
        
        self.toggleInputModeButtonFrame = CGRectMake(0.0, top + height * 3, width, height);
        self.nextKeyboardButtonFrame = CGRectMake(width, top + height * 3, 92.0, height);
        self.shiftButtonFrame = CGRectMake(width, top + height * 2, 92.0, height);
        self.spaceButtonFrame = CGRectMake(left, top + height * 3, width * 7, height);
        self.commaButtonFrame = CGRectMake(0.0, top + height * 2, width, height);
        self.periodButtonFrame = CGRectMake(width * 11, top + height * 2, width, height);
        self.deleteButtonFrame = CGRectMake(left + width * 7, top + height * 2, 92.0, height);
        self.returnButtonFrame = CGRectMake(left + width * 7, top + height * 3, 92.0, height);
        self.dismissButtonFrame = CGRectZero;
        self.previousCandidateButtonFrame = CGRectMake(0.0, top, width, height);
        self.nextCandidateButtonFrame = CGRectMake(0.0, top + height, width, height);
        self.previousCursorButtonFrame = CGRectMake(width * 11, top, width, height);
        self.nextCursorButtonFrame = CGRectMake(width * 11, top + height, width, height);
        self.dismissButtonFrame = CGRectMake(width * 11, top + height * 3, width, height);
    }
    
    if(self.inputMode == KeyboardInputModeHandWriting) {
        CGRect frame = CGRectMake(keyboardViewWidth - self.handwritingButtonFrame.size.width, self.handwritingButtonFrame.origin.y, self.handwritingButtonFrame.size.width, self.handwritingButtonFrame.size.height);
        self.spaceButtonFrame = frame;
    }
}

@end
