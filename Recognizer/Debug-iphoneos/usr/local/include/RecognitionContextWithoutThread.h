/*
=============================================================================
ファイル名  RecognitionContextWithoutThread.h
クラス名    RecognitionContextWithoutThread
解説        汎用文字列認識ライブラリ
担当者      朱碧蘭

=============================================================================
履歴
11/11/17    作成
=============================================================================
*/

//---------------------------------------------------------------------------
#include "RecognitionContext.h"

#ifndef RecognitionContextWithoutThreadH
#define RecognitionContextWithoutThreadH
//---------------------------------------------------------------------------
class RecognitionContextWithoutThread : public RecognitionContext
{
    private:

		void setFilter(void);

    public:

		void Recognize();
		const CharacterBlockResult* GetCharacterBlock();

		bool SetResolution(int width, int height);
		void SetOneLineRecognition(bool isOneLine);
		void SetRecognitionCode(const char *code);
		//void WriteDictionaries(const char *dicPathName);//20130828 by Pothos
		bool AddBoundingBox(int left, int top, int right, int bottom);
		void ClearBoundingBox();
		bool AddPoints(const POINT* points, int count);
		bool AddPage();
		bool AddStroke();
		bool AddPoint(int x, int y);
		bool RemoveLastStroke();
		void Clear();
		void ClearInk();
		void ClearLattice();
		void ClearRecognitionResult();
		bool PrivateCharacterRegister(const unsigned short code, const CharacterCategory category);
		bool PrivateCharacterUnregister(const unsigned short code);
		int GetPrivateCharacterRegisterCount(void);
		const PrivateCharacter* GetOnePrivateCharacterRegister(int id);
		const RegisteredPrivateCharacter* GetPrivateCharacterRegister(void);
		const RecognitionResult* OneCharacterRecognize();
		bool SetInputLinePosition(short top, short bottom);
		void SetGuideLines(short topLine, short	baseLine);
		const RecognitionResult* GetRecognitionResult();
		const char* GetSegmentationResult();
		void SetCustomFilterCode(const char *code);
		void ClearCustomFilter();
		const char* GetCustomFilter();
		void SetHiragana(bool flag);
		void SetKatakana(bool flag);
		void SetAlphabet(bool flag);
		void SetJis1Kanji(bool flag);
		void SetJis2Kanji(bool flag);
		void SetNumeric(bool flag);
		void SetSymbol(bool flag);
		void SetGreek(bool flag);
		void SetPunctuation(bool flag);
		bool GetHiragana();
		bool GetKatakana();
		bool GetAlphabet();
		bool GetJis1Kanji();
		bool GetJis2Kanji();
		bool GetNumeric();
		bool GetSymbol();
		bool GetGreek();
		bool GetPunctuation();
		void SetContextDictionary(char *fileName);
		ProcessingStatus AttachDictionary(Context* contextDict);
		ProcessingStatus DetachDictionary(Context* contextDict);
		void RegisterString(const char *code);
		bool CharacterRegister(const unsigned short code);
		void SetHeavySegmentation(bool isHeavySegmentation);
		bool CharacterRegister(const unsigned int UTF8code, const unsigned short code);

        RecognitionContextWithoutThread(HandsInk *handsInk);
        ~RecognitionContextWithoutThread();
};
#endif
