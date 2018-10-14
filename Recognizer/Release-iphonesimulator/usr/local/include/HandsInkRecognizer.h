//
//  HandsInkRecognizer.h
//  HandsInkRecognizer
//
//  Created by ポトス on 10/10/08.
//  Copyright 2010 Pothos. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <time.h>
#import "RecognitionContextWithThread.h"
#import "RecognitionContextWithOutThread.h"
#import "DictionaryPath.h"
//#import "CHandsInkRecognizer.h"
#import "HandsInkRecognizeType.h"

@interface HandsInkRecognizer : NSObject {
	bool                            Inited;
    bool                            HandsInkThreadingMode;
    bool                            IsOneCharacterRecognize;
    ProcessingStatus                MyProStatus;
    HandsInkRecognizeType           RecognizerType;
}
@property (readonly) bool Inited;
@property bool HandsInkThreadingMode;
@property (readonly)HandsInkRecognizeType RecognizerType;
//エンジンをロードする
-(bool)HandsInkInitialize:(NSString*)path;
-(bool)HandsInkAddBoundingRect:(int)left top:(int)top right:(int)right bottom:(int)bottom;
-(bool)HandsInkClearBoundingRect;
//エンジンをクローズする。
-(void)HandsInkClose;
//認識枠を設定する
-(bool)HandsInkSetResolution:(int) width height:(int)height;
//単文字認識
//加点
-(bool)HandsInkAddPage;
-(bool)HandsInkAddStroke;
-(bool)HandsInkRemoveLastStroke;
-(bool)HandsInkAddPoint:(int)x y:(int)y;
-(bool)HandsInkAddPoints:(const POINT*)points count:(int)count;
//点データをクリアする
-(void)HandsInkClear;
//認識する
-(void)HandsInkRecognizeDo;
-(NSString*)HandsInkRecognize;
-(const RecognitionResult*) HandsInkGetRecognitionResult;
//字種設定
-(void)HandsInkSetHiragana:(bool)flag;
-(void)HandsInkSetKatakana:(bool)flag;
-(void)HandsInkSetAlphabet:(bool)flag;
-(void)HandsInkSetJis1Kanji:(bool)flag;
-(void)HandsInkSetJis2Kanji:(bool)flag;
-(void)HandsInkSetNumeric:(bool)flag;
-(void)HandsInkSetSymbol:(bool)flag;
-(void)HandsInkSetGreek:(bool)flag;
-(void)HandsInkSetPunctuation:(bool)flag;
//字種取得
-(bool)HandsInkGetHiragana;
-(bool)HandsInkGetKatakana;
-(bool)HandsInkGetAlphabet;
-(bool)HandsInkGetJis1Kanji;
-(bool)HandsInkGetJis2Kanji;
-(bool)HandsInkGetNumeric;
-(bool)HandsInkGetSymbol;
-(bool)HandsInkGetGreek;
-(bool)HandsInkGetPunctuation;
//自定義文字を設定する
-(void) HandsInkSetCustomFilter:(NSString*)str;
-(void) HandsInkSetCustomFilterCode:(const char*)nullTerminatedShiftJISFullwidthCode;//nullTerminatedShiftJISFullwidthCode:全角のShiftJISコード、０x００で終了
-(void) HandsInkClearCustomFilter;
-(NSString*)HandsInkGetCustomFilter;
//OneLine認識
-(bool)HandsInkSetOneLineRecognize;
-(bool)HandsInkSetOneCharacterRecognize;
-(bool)HandsInkSetFreeRecognize;
-(bool)HandsInkSetMultRectRecognize;
@end
