//
//  HandsInkContextRecognizer.h
//  HandsInkRecognizer
//
//  Created by ポトス on 10/12/02.
//  Copyright 2010 ポトス株式会社. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HandsInkRecognizer.h"
#import "RecognizeContext.h"

@interface HandsInkContextRecognizer : NSObject {
	HandsInkRecognizer *handsInkRecognizer;
	int numContexts;
	RecognizeContext contexts[MAX_CONTEXTS];
}
-(id)InitialWithRecognizer:(HandsInkRecognizer*)recognizer;

//Context Open
-(int)HandsInkOpenContext;

//エンジンをクローズする。コンテキストを削除する。認識エンジンはメモリにある
-(void)HandsInkContextClose:(int)handle;

-(bool)HandsInkContextAddBoundingRect:(int)handle left:(int)left top:(int)top right:(int)right bottom:(int)bottom;
-(void)HandsInkContextClearBoundingRect:(int)handle;

//認識枠を設定する
-(bool)HandsInkContextSetResolution:(int)handle width:(int)width height:(int)height;
//加点
-(bool)HandsInkContextAddStroke:(int)handle;
-(bool) HandsInkContextAddPoint:(int)handle x:(int)x y:(int)y;
-(bool)HandsInkContextAddPoints:(int)handle points:(const POINT*)points count:(int)count;
//点データをクリアする
-(void)HandsInkContextClear:(int) handle;
//認識する
-(NSString*)HandsInkContextRecognize:(int) handle;
-(const RecognitionResult*)HandsInkContextGetRecognitionResult:(int)handle;

-(bool)HandsInkContextSetPendingNum:(int)handle num:(int)num;
//字種設定
-(void)HandsInkContextSetHiragana:(int)handle flag:(bool)flag;
-(void)HandsInkContextSetKatakana:(int)handle flag:(bool)flag;
-(void)HandsInkContextSetAlphabet:(int)handle flag:(bool)flag;
-(void)HandsInkContextSetJis1Kanji:(int)handle flag:(bool)flag;
-(void)HandsInkContextSetJis2Kanji:(int)handle flag:(bool)flag;
-(void)HandsInkContextSetNumeric:(int)handle flag:(bool)flag;
-(void)HandsInkContextSetSymbol:(int)handle flag:(bool)flag;
-(void)HandsInkContextSetGreek:(int)handle flag:(bool)flag;
-(void)HandsInkContextSetPunctuation:(int)handle flag:(bool)flag;
//字種取得
-(bool)HandsInkContextGetHiragana:(int)handle;
-(bool)HandsInkContextGetKatakana:(int)handle;
-(bool)HandsInkContextGetAlphabet:(int)handle;
-(bool)HandsInkContextGetJis1Kanji:(int)handle;
-(bool)HandsInkContextGetJis2Kanji:(int)handle;
-(bool)HandsInkContextGetNumeric:(int)handle;
-(bool)HandsInkContextGetSymbol:(int)handle;
-(bool)HandsInkContextGetGreek:(int)handle;
-(bool)HandsInkContextGetPunctuation:(int)handle;
//自定義文字を設定する
-(void) HandsInkContextSetCustomFilter:(int) handle str:(NSString*)str;
-(void)HandsInkContextSetCustomFilterCode:(int) handle nullTerminatedShiftJISFullwidthCode:(const char*)nullTerminatedShiftJISFullwidthCode;
-(void)HandsInkContextClearCustomFilter:(int) handle;
-(const char*)HandsInkContextGetCustomFilterCode:(int)handle;
-(NSString*)HandsInkContextGetCustomFilter:(int)handle;
-(bool)ContextClearData:(RecognizeContext*)pContext;
-(bool)ContextInitContext:(RecognizeContext*)pContext;
-(bool)ContextInitialize;

@end

