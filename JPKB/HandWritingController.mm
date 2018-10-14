//
//  HandWritingController.m
//  JPKB
//
//  Created by xwang on 10/3/18.
//  Copyright © 2018 kishikawa katsumi. All rights reserved.
//

#import "HandWritingController.h"
#import "HandsInkRecognizer.h"

@implementation HandWritingController

//+(id) controller {
//    static dispatch_once_t once;
//    static HandWritingController *sharedInstance;
//    dispatch_once(&once, ^{
//        sharedInstance = [[HandWritingController alloc] init];
//    });
//    return sharedInstance;
//}
-(BOOL)HandsInkInitialize{
    
    if (recognizer.Inited){
        [recognizer HandsInkClear];
        [recognizer HandsInkClose];
    }
    
    recognizer = [[HandsInkRecognizer alloc] init];
    recognizer.HandsInkThreadingMode = true;
    NSString *path = [[NSBundle mainBundle] bundlePath];
    bool suc = [recognizer HandsInkInitialize:path];
    
    return suc;
}

-(BOOL)Inited{
    return recognizer.Inited;
}

-(void)HandsInkClose{
    
    if (recognizer.Inited) {
        [recognizer HandsInkClose];
    }
}

-(bool)HandsInkAddBoundingRect:(int)left top:(int)top right:(int)right bottom:(int)bottom{
    return [recognizer HandsInkAddBoundingRect:left top:top right:right bottom:bottom];
}

-(bool)HandsInkClearBoundingRect{
    return [recognizer HandsInkClearBoundingRect];
}

-(void)HandsInkClear{
    if (recognizer.Inited) {
        [recognizer HandsInkClear];
    }
}

-(void)HandsInkAddStroke{
    [recognizer HandsInkAddStroke];
}

-(void)HandsInkAddPoint:(int)x y:(int)y{
    
    [recognizer HandsInkAddPoint:x y:y];
}


-(NSString *)HandsInkRecognize{
    
    [self HandsInkRecognizeDo];
    
    [self HandWait];
    
    if (recognizer.Inited) {
        NSString *str = [recognizer HandsInkRecognize];
        
        str = [str stringByReplacingOccurrencesOfString:@"\r\n" withString:@""];
        return str;
    } else {
        return @"エンジンをロードしてください。";
    }
}

-(NSString *)HandsInkGetRecognitionResult{
    
    NSString *str = @"";
    if (recognizer.Inited) {
        
        const RecognitionResult* result = [recognizer HandsInkGetRecognitionResult];
        
        int len = result->Count;
        RecognitionCandidate *pcans = result->Candidate;
        RecognitionCandidate can;
        NSMutableString *all = [[NSMutableString alloc] init];
        for (int i = 0; i < len; i++) {
            //[all setString:@""];
            can = pcans[i];
            
            NSString *txt = [NSString stringWithCString:can.Result encoding:NSShiftJISStringEncoding];
            [all appendString:txt];
            [all appendString:@","];
        }
        
        str = all;
        
        str = [str stringByReplacingOccurrencesOfString:@"\r\n" withString:@""];
        return str;
    } else {
        return @"エンジンをロードしてください。";
    }
}

-(void)HandsInkRecognizeDo{
    if(recognizer.Inited){
        [recognizer HandsInkRecognizeDo];
    }
}

-(void)HandWait{
    
    [NSThread sleepForTimeInterval:0.01];
}

-(void)HandsInkSetAll:(bool)flag{
    [recognizer HandsInkSetHiragana:flag];
    [recognizer HandsInkSetKatakana:flag];
    [recognizer HandsInkSetAlphabet:flag];
    [recognizer HandsInkSetJis1Kanji:flag];
    [recognizer HandsInkSetJis2Kanji:flag];
    [recognizer HandsInkSetNumeric:flag];
    [recognizer HandsInkSetSymbol:flag];
    [recognizer HandsInkSetGreek:flag];
    [recognizer HandsInkSetPunctuation:flag];
}

-(void)HandsInkSetHiragana:(bool)flag{
    [recognizer HandsInkSetHiragana:flag];
}
-(void)HandsInkSetKatakana:(bool)flag{
    [recognizer HandsInkSetKatakana:flag];
}
-(void)HandsInkSetAlphabet:(bool)flag{
    [recognizer HandsInkSetAlphabet:flag];
}
-(void)HandsInkSetJis1Kanji:(bool)flag{
    [recognizer HandsInkSetJis1Kanji:flag];
}
-(void)HandsInkSetJis2Kanji:(bool)flag{
    [recognizer HandsInkSetJis2Kanji:flag];
}
-(void)HandsInkSetNumeric:(bool)flag{
    [recognizer HandsInkSetNumeric:flag];
}
-(void)HandsInkSetSymbol:(bool)flag{
    [recognizer HandsInkSetSymbol:flag];
}
-(void)HandsInkSetGreek:(bool)flag{
    [recognizer HandsInkSetGreek:flag];
}
-(void)HandsInkSetPunctuation:(bool)flag{
    [recognizer HandsInkSetPunctuation:flag];
}

-(BOOL)HandsInkGetHiragana{
    return [recognizer HandsInkGetHiragana];
}

-(BOOL)HandsInkGetKatakana{
    return [recognizer HandsInkGetKatakana];
}

-(BOOL)HandsInkGetAlphabet{
    return [recognizer HandsInkGetAlphabet];
}

-(BOOL)HandsInkGetJis1Kanji{
    return [recognizer HandsInkGetJis1Kanji];
}

-(BOOL)HandsInkGetJis2Kanji{
    return [recognizer HandsInkGetJis2Kanji];
}

-(BOOL)HandsInkGetNumeric{
    return [recognizer HandsInkGetNumeric];
}

-(BOOL)HandsInkGetSymbol{
    return [recognizer HandsInkGetSymbol];
}

-(BOOL)HandsInkGetGreek{
    return [recognizer HandsInkGetGreek];
}

-(BOOL)HandsInkGetPunctuation{
    return [recognizer HandsInkGetPunctuation];
}

-(void)HandsInkSetCustomFilter:(NSString *)code{
    [recognizer HandsInkSetCustomFilter:code];
}

-(void)HandsInkSetCustomFilterCode:(const char *)code{
    [recognizer HandsInkSetCustomFilterCode:code];
}

-(void)HandsInkClearCustomFilter{
    [recognizer HandsInkClearCustomFilter];
}

-(NSString *)HandsInkGetCustomFilter{
    return [recognizer HandsInkGetCustomFilter];
}

-(void)HandsInkSetOneCharacterRecognize{
    [recognizer HandsInkSetOneCharacterRecognize];
}

-(void)HandsInkSetOneLineRecognize{
    [recognizer HandsInkSetOneLineRecognize];
}

-(void)HandsInkSetFreeRecognize{
    [recognizer HandsInkSetFreeRecognize];
}

-(void)HandsInkThreadingMode:(bool)flag{
    recognizer.HandsInkThreadingMode = flag;
}

-(void) recognize {
    if(!self.Inited) {
        [self HandsInkInitialize];
    }
    NSString *result = [self HandsInkRecognize];
    if(self.delegate && [self.delegate respondsToSelector:@selector(handWritingRecognized:)]) {
        [self.delegate handWritingRecognized:result];
    }
}


-(void) clear {
    [self HandsInkClear];
//    [self.drawView clearPoints];
}

-(void) undo {
//    [self HandsInkClear];
//    [self.drawView clearPoints];
//    [self recognize];
}
@end
