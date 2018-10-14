/*
=============================================================================
�t�@�C����  RecognitionContext.h
�N���X��    RecognitionContext
���        �ėp������F�����C�u����
�S����      ��ɗ�

=============================================================================
����
11/10/29    �쐬
=============================================================================
*/

//---------------------------------------------------------------------------
#include "UnitHandsInk.h"

#ifndef RecognitionContextH
#define RecognitionContextH
//---------------------------------------------------------------------------
typedef struct tagRecognitionCandidate
{
		// �Ώۂ̕��������p�^�[��
		int             Start;        // �����p�^�[���̐擪�X�g���[�N
		int             End;          // �����p�^�[���̏I�[�X�g���[�N�@

		// �F������
		char            Result[CANDIDATE_COUNT * 2 + 1];

		double          Score[CANDIDATE_COUNT];
		unsigned short  Code[CANDIDATE_COUNT];
		char			Str[CANDIDATE_COUNT][5];

		// ���`���
		int				BoundsLeft;
		int				BoundsTop;
		int				BoundsRight;
		int				BoundsBottom;
} RecognitionCandidate;
//---------------------------------------------------------------------------
typedef struct tagRecognitionResult
{
	char			     *Result;
	RecognitionCandidate *Candidate;
	int			  		 Count;
}RecognitionResult;
//---------------------------------------------------------------------------
typedef struct tagCharacterCandidate
{
	double        Score;
	unsigned short  Code;
	char Str[5];
}CharacterCandidate;
//---------------------------------------------------------------------------
typedef struct tagCharacterBlock
{
	int 				Start;        // �����p�^�[���̐擪�X�g���[�N
	int 				End;          // �����p�^�[���̏I�[�X�g���[�N�@
	int					Left;
	int					Right;
	CharacterCandidate	Candidate[CANDIDATE_COUNT];
	CharacterCandidate*	pCandidate[CANDIDATE_COUNT];
	int					SelectedIndex;

	tagCharacterBlock()
	{
		for(int i = 0; i < CANDIDATE_COUNT; i++)
			pCandidate[i] = &Candidate[i];
	}
}CharacterBlock;
//---------------------------------------------------------------------------
typedef struct tagCharacterBlockResult
{
	char  		*Result;
	short  		*ResultBlockId;
	CharacterBlock 	*Block;
	CharacterBlock 	*BlockIterator;
	int	  	Count;
	int     ReCount;
}CharacterBlockResult;
//---------------------------------------------------------------------------
/*struct PrivateStrokeA
{
	POINT           *Points;// �X�g���[�N�̕M�_��
	int             Count; // �X�g���[�N�M�_��̐�
};
//---------------------------------------------------------------------------
struct PrivateCharacterA
{
	PrivateStrokeA    *Strokes; // �����p�^���̃X�g���[�N
	int               Count;   // �����p�^���̃X�g���[�N�̐�
	unsigned short    Code;     // �����R�[�h
	CharacterCategory Category;	// �o�^����̃J�e�S��
};
//---------------------------------------------------------------------------
struct RegisteredPrivateCharacterA
{
	PrivateCharacterA  *Character; // �o�^�ς݂̊O��
	int                Count;     //�o�^�ς݂̊O���̐�
};
//---------------------------------------------------------------------------*/
class RecognitionContext
{
    private:

    protected:
		//vector<PrivateCharacterA> characters;
		//RegisteredPrivateCharacterA privateCharacterA;
		vector<RecognitionCandidate> vCandidate;
		RecognitionResult rc;
		vector<char> Segment;

		vector<short> blockId;
		vector<char> resultText;
		vector<CharacterBlock> block;
		CharacterBlockResult blockResult;

		short inputLineTop;
		short inputLineBottom;
		vector<RecognitionCharacterFilter *> filter;

		void freePrivateCharacterA();

    public:

        InkManager       *Ink;
		InkPage			inkPage;
        Context			*MyContext;
		HandsInk		*MyHandsInk;
		short			TopLine;
		short			BaseLine;
		bool			IsSetGuideLines;
		ProcessingStatus MyProStatus;
		short indexToDicCount[MAX_CHARCTER_COUNT];
		bool isHeavySegmentation;

		void addStrokes(void);

		virtual bool SetResolution(int width, int height) = 0;
		virtual void SetOneLineRecognition(bool isOneLine) = 0;
		virtual void SetRecognitionCode(const char *code) = 0;
		//virtual void WriteDictionaries(const char *dicPathName) = 0;
		virtual bool AddBoundingBox(int left, int top, int right, int bottom) = 0;
		virtual void ClearBoundingBox() = 0;
		virtual bool AddPoints(const POINT* points, int count) = 0;
		virtual bool AddPage() = 0;
		virtual bool AddStroke() = 0;
		virtual bool AddPoint(int x, int y) = 0;
		virtual bool RemoveLastStroke() = 0;
		virtual void Clear() = 0;
		virtual void ClearInk() = 0;
		virtual void ClearLattice() = 0;
		virtual void ClearRecognitionResult() = 0;
		virtual bool PrivateCharacterRegister(const unsigned short code, const CharacterCategory category) = 0;
		virtual bool PrivateCharacterUnregister(const unsigned short code) = 0;
		virtual int GetPrivateCharacterRegisterCount(void) = 0;
		virtual const PrivateCharacter* GetOnePrivateCharacterRegister(int id) = 0;
		virtual const RegisteredPrivateCharacter* GetPrivateCharacterRegister(void) = 0;
		virtual const RecognitionResult* OneCharacterRecognize() = 0;
		virtual bool SetInputLinePosition(short top, short bottom) = 0;
		virtual void SetGuideLines(short topLine, short	baseLine) = 0;
		virtual void Recognize() = 0;
		virtual const RecognitionResult* GetRecognitionResult() = 0;
		virtual const char* GetSegmentationResult() = 0;
		virtual const CharacterBlockResult* GetCharacterBlock() = 0;
		virtual void SetCustomFilterCode(const char *code) = 0;
		virtual void ClearCustomFilter() = 0;
		virtual const char* GetCustomFilter() = 0;
		virtual void SetHiragana(bool flag) = 0;
		virtual void SetKatakana(bool flag) = 0;
		virtual void SetAlphabet(bool flag) = 0;
		virtual void SetJis1Kanji(bool flag) = 0;
		virtual void SetJis2Kanji(bool flag) = 0;
		virtual void SetNumeric(bool flag) = 0;
		virtual void SetSymbol(bool flag) = 0;
		virtual void SetGreek(bool flag) = 0;
		virtual void SetPunctuation(bool flag) = 0;
		virtual bool GetHiragana() = 0;
		virtual bool GetKatakana() = 0;
		virtual bool GetAlphabet() = 0;
		virtual bool GetJis1Kanji() = 0;
		virtual bool GetJis2Kanji() = 0;
		virtual bool GetNumeric() = 0;
		virtual bool GetSymbol() = 0;
		virtual bool GetGreek() = 0;
		virtual bool GetPunctuation() = 0;
		virtual void SetContextDictionary(char *fileName) = 0;
		virtual ProcessingStatus AttachDictionary(Context* contextDict) = 0;
		virtual ProcessingStatus DetachDictionary(Context* contextDict) = 0;
		virtual void setFilter(void) = 0;
		virtual void RegisterString(const char *code) = 0;
		virtual bool CharacterRegister(const unsigned short code) = 0;
		virtual void SetHeavySegmentation(bool isHeavySegmentation) = 0;
		virtual bool CharacterRegister(const unsigned int UTF8code, const unsigned short code) = 0;

		ProcessingStatus AttachFilter(RecognitionCharacterFilter *filter);
		ProcessingStatus DetachFilter();

        RecognitionContext(HandsInk *handsInk);
        ~RecognitionContext();
};
#endif
