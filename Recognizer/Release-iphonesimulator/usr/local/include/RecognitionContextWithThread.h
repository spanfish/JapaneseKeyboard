/*
=============================================================================
�t�@�C����  RecognitionContextWithThread.h
�N���X��    RecognitionContextWithThread
���        �ėp������F�����C�u����
�S����      ��ɗ�

=============================================================================
����
11/11/17    �쐬
=============================================================================
*/

//---------------------------------------------------------------------------
#include "RecognitionContext.h"

#if defined(WIN32)
#include <process.h>
#else
#include <pthread.h>
#endif

#ifndef RecognitionContextWithThreadH
#define RecognitionContextWithThreadH
//---------------------------------------------------------------------------
class RecognitionContextWithThread : public RecognitionContext
{
    private:
#if defined(WIN32)
    int	thread_id;
#else
    pthread_t thread_id;
#endif

		void setFilter(void);

    public:

		void Recognize();
		const CharacterBlockResult* GetCharacterBlock();

		bool SetResolution(int width, int height);
		void SetOneLineRecognition(bool isOneLine);
		void SetRecognitionCode(const char *code);
		//void WriteDictionaries(const char *dicPathName);
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

        RecognitionContextWithThread(HandsInk *handsInk);
        ~RecognitionContextWithThread();
};
#endif
