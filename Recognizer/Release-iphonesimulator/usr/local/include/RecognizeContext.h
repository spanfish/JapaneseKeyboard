//
//  HandsInkContextRecognizer.h
//  HandsInkRecognizer
//
//  Created by �|�g�X on 10/12/02.
//  Copyright 2010 �|�g�X�������. All rights reserved.
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
	// �g�p�t���O
	bool			bUsed;
	
	// �𑜓x
	int				nWidth;
	int				nHeight;
	
	// �F�����E
	ArrayList<RECT>	Bounds;
	
	// ����t���O
	bool			bHiragana;
	bool			bKatakana;
	bool			bAlphabet;
	bool			bJis1Kanji;
	bool			bJis2Kanji;
	bool			bNumeric;
	bool			bSymbol;
	bool			bGreek;
	bool			bPunctuation;
	
	// �J�X�^���R�[�h
	char			*pCustomCodes;
	
	// �X�g���[�N�̐��ƃX�g���[�N�f�[�^
	//		int				nStroke;
	ArrayList<ContextStroke>	Strokes;
	
	// �y���f�B���O������
	int				nPending;
	
	// �m��ς݃X�g���[�N�̍Ō�
	int				nFixed;
	
	// �R���e�L�X�g���ł̔F���Ăяo����
	int				nRecognize;
	
	// �O��̔F������
	RecognitionResult FixedResult;
	RecognitionResult LastResult;
	
} RecognizeContext;


//---------------------------------------------------------------------------
#endif

