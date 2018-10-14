//
//  HandsInkContextRecognizer.h
//  HandsInkRecognizer
//
//  Created by ポトス on 10/12/02.
//  Copyright 2010 ポトス株式会社. All rights reserved.
//

#ifndef HandsInkDllH
#define HandsInkDllH

#define MAX_CONTEXTS	20
#define DEFAULT_PENDING	3
typedef struct tagContextStroke
{
	ArrayList<POINT>    Point;
} ContextStroke;

typedef struct tagRecognizeContext
{
	// 使用フラグ
	bool			bUsed;
	
	// 解像度
	int				nWidth;
	int				nHeight;
	
	// 認識境界
	ArrayList<RECT>	Bounds;
	
	// 字種フラグ
	bool			bHiragana;
	bool			bKatakana;
	bool			bAlphabet;
	bool			bJis1Kanji;
	bool			bJis2Kanji;
	bool			bNumeric;
	bool			bSymbol;
	bool			bGreek;
	bool			bPunctuation;
	
	// カスタムコード
	char			*pCustomCodes;
	
	// ストロークの数とストロークデータ
	//		int				nStroke;
	ArrayList<ContextStroke>	Strokes;
	
	// ペンディング文字数
	int				nPending;
	
	// 確定済みストロークの最後
	int				nFixed;
	
	// コンテキスト内での認識呼び出し回数
	int				nRecognize;
	
	// 前回の認識結果
	RecognitionResult FixedResult;
	RecognitionResult LastResult;
	
} RecognizeContext;


//---------------------------------------------------------------------------
#endif

