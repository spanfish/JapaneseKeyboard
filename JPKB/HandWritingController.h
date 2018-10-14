//
//  HandWritingController.h
//  JPKB
//
//  Created by xwang on 10/3/18.
//  Copyright © 2018 kishikawa katsumi. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "DrawView.h"

@protocol HandWritingControllerDelegate <NSObject>
@optional
- (void)handWritingRecognized:(NSString *)str;
@end

@class HandsInkRecognizer;
@interface HandWritingController : NSObject {
    HandsInkRecognizer *recognizer;
}

@property(nonatomic, weak) id<HandWritingControllerDelegate> delegate;
//@property(nonatomic, strong) DrawView *drawView;

//+(id) controller;

//文字認識エンジンを初期化します。
-(BOOL)HandsInkInitialize;

-(BOOL)Inited;

//手書き文字認識ライブラリを終了します。
-(void)HandsInkClose;

//指定後，枠あり（単文字）認識が機能します。
-(bool)HandsInkAddBoundingRect:(int)left top:(int)top right:(int)right bottom:(int)bottom;

//枠をクリアします。設定後，枠なし認識（自由記載）が機能します。
-(bool)HandsInkClearBoundingRect;

//入力されているストロークデータと、直前の認識結果を削除します。
-(void)HandsInkClear;

//認識する文字を構成するストロークデータを入力します。本関数を使用する場合、続けて次項のHandsInkAddPoint関数を使用してください。
-(void)HandsInkAddStroke;

//ストロークを構成する点列データを入力します。
-(void)HandsInkAddPoint:(int)x y:(int)y;

//認識処理を行います。
-(NSString *)HandsInkRecognize;

//文字認識の詳細な結果を取得します。
-(NSString *)HandsInkGetRecognitionResult;

-(void)HandsInkRecognizeDo;

//全ての文字カテゴリフィルタを設定します。
-(void)HandsInkSetAll:(bool)flag;

//ひらがなの文字カテゴリフィルタを設定します。
-(void)HandsInkSetHiragana:(bool)flag;

//カタカナの文字カテゴリフィルタを設定します。
-(void)HandsInkSetKatakana:(bool)flag;

//アルファベットの文字カテゴリフィルタを設定します。
-(void)HandsInkSetAlphabet:(bool)flag;

//JIS第一水準漢字の文字カテゴリフィルタを設定します。
-(void)HandsInkSetJis1Kanji:(bool)flag;

//JIS第二水準漢字の文字カテゴリフィルタを設定します。
-(void)HandsInkSetJis2Kanji:(bool)flag;

//数字の文字カテゴリフィルタを設定します。
-(void)HandsInkSetNumeric:(bool)flag;

//記号の文字カテゴリフィルタを設定します。
-(void)HandsInkSetSymbol:(bool)flag;

//ギリシャ文字の文字カテゴリフィルタを設定します。
-(void)HandsInkSetGreek:(bool)flag;

//句読点の文字カテゴリフィルタを設定します。
-(void)HandsInkSetPunctuation:(bool)flag;

//ひらがなの文字カテゴリフィルタを取得します。
-(BOOL)HandsInkGetHiragana;

//カタカナの文字カテゴリフィルタを取得します。
-(BOOL)HandsInkGetKatakana;

//アルファベットの文字カテゴリフィルタを取得します。
-(BOOL)HandsInkGetAlphabet;

//JIS第一水準漢字の文字カテゴリフィルタを取得します。
-(BOOL)HandsInkGetJis1Kanji;

//JIS第二水準漢字の文字カテゴリフィルタを取得します。
-(BOOL)HandsInkGetJis2Kanji;

//数字の文字カテゴリフィルタを設定します。
-(BOOL)HandsInkGetNumeric;

//記号の文字カテゴリフィルタを取得します。
-(BOOL)HandsInkGetSymbol;

//ギリシャ文字の文字カテゴリフィルタを取得します。
-(BOOL)HandsInkGetGreek;

//句読点の文字カテゴリフィルタを取得します。
-(BOOL)HandsInkGetPunctuation;

//与えられた文字列に含まれる字種をフィルタとして設定します。
-(void)HandsInkSetCustomFilter:(NSString *)code;

//与えられた文字列に含まれる字種をフィルタとして設定します。
-(void)HandsInkSetCustomFilterCode:(const char *)code;

//HandsInkSetCustomFilterCode関数で設定されたフィルタを解除します。
-(void)HandsInkClearCustomFilter;

//HandsInkSetCustomFilterCode関数で設定されたカスタムフィルタを取得します。
-(NSString *)HandsInkGetCustomFilter;

//単文字認識を設定します。
-(void)HandsInkSetOneCharacterRecognize;

//一行認識を設定します。
-(void)HandsInkSetOneLineRecognize;

//自由記載認識を設定します
-(void)HandsInkSetFreeRecognize;

//逐次認識の場合はHandsInkThreadModeを設定します。
-(void)HandsInkThreadingMode:(bool)flag;

-(void) recognize;

-(void) clear;

-(void) undo;
@end
