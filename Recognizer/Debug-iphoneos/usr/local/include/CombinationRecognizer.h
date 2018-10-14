/*
=============================================================================
プロジェクト名  HandsRecognizer
ファイル名      CombinationRecognizer.h
クラス名        CombinationRecognizer
解説            統合認識クラス
担当者          朱　碧蘭

=============================================================================
履歴
10/06/18        作成
=============================================================================
*/

#ifndef CombinationRecognizerH
#define CombinationRecognizerH

#include <string>
#include "MRFOnlineRecognizer.h"
#include "MQDFRecognizer.h"
#include "PrivateCharacterRegister.h"
#include "ProbabilityTable.h"
#include "InkPage.h"
#include "Sorter.h"
#include "RecognitionCharacterFilter.h"

//---------------------------------------------------------------------------
class CharacterRecognitionResult
{
    public:
        char    Candidate[3];
        double  Score[2];
        double  Probability;
		unsigned short Code;

    CharacterRecognitionResult()
    {
        Candidate[0] = '\0';
        Candidate[1] = '\0';
        Candidate[2] = '\0';
		Score[0]        = 0;
		Score[1]        = 0;
        Probability  = 0;
		Code         = 0;
    }
    ~CharacterRecognitionResult(){};
};
//---------------------------------------------------------------------------
struct Range
{
	short start;
	short end;
	Range()
	{

	}
	Range(short s, short e)
	{
		start = s;
		end = e;
	}
};
//---------------------------------------------------------------------------
class CombinationRecognizer
{
    private:
		ProbabilityTable *offlineTable;	
		ProbabilityTable *onlineTable;

		MRFOnlineRecognizer    *onLine;
		vector<double> weight; 
		int weightCount;

        CharacterRecognitionResult *result;
        int     candidateCount;
		PAT_POS pos;
		POINT_W *myPoints;
		long myPointsCount;

		//short *indexToDicCount;
		short indexToDicCount[MAX_CHARCTER_COUNT];
		vector<Range> recogRange;
		// カテゴリフィルタ
		bool	flagHiragana;
		bool	flagKatakana;
		bool	flagAlphabet;
		bool	flagJis1Kanji;
		bool	flagJis2Kanji;
		bool	flagNumeric;
		bool	flagSymbol;
		bool	flagGreek;
		bool	flagPunctuation;
		bool	flagCustom;

		vector<unsigned short> customCode;
		string customString;

		short *data;
		short **hash;
		short *hashCount;

		Sorter sort;

		void setCategoryFilter(void);
		void setFilter(unsigned short codeS, unsigned short codeE
									  , CharacterCategory cate);
		void addRange(unsigned short codeS, unsigned short codeE);
		void setCustomFilterCode(const unsigned short *code, int count);

		void transformPattern(PATTERN_W &m_patw, Pattern &pat);
		void setPattern(InkStroke *inkStroke, int count, PATTERN_W &ptw);
		double getConbinationScore(int scoreOn, int scoreOff, unsigned short code);
		double getConbinationScore(int scoreOn, int scoreOff);
		double sigmod(double x);
		int sortByScore(int *code, int *score, int preCount, int count);
		int sortByScore(int *code, long *score, int preCount, int count);
		int fastSort(short *index, int *score, int preCount, int count);
		int fastSort(short *index, long *score, int preCount, int count);
		int sortByLtmScore(int *code, int *score, int preCount, int count);
		bool onlineRecognize(PATTERN_W &ptw, int *index, int *score, int count);
		int onlineRecognize(PATTERN_W &ptw, int *index, 
								 short *candidate, int candCount, int count);
		void freeDictionaryData(void);
		void readDictionarys(void);
		bool onlineRecognize(PATTERN_W &ptw, unsigned short *code,
								 int *score, int count);

	public:

		PrivateCharacterRegister *Register;
		MQDFRecognizer   *offLine;
		double  q;
		bool IsCheck;
		bool IsEmpty;

		// コードフィルター関数
		void SetCustomFilterCode(const char *code);
		void ClearCustomFilter();
		const char* GetCustomFilter();
		void setCustomFilterCode(void);
		void SetRecognitionFilter(vector<RecognitionCharacterFilter*> &filter);

		void	SetHiragana(bool flag);
		void	SetKatakana(bool flag);
		void	SetAlphabet(bool flag);
		void	SetJis1Kanji(bool flag);
		void	SetJis2Kanji(bool flag);
		void	SetNumeric(bool flag);
		void	SetSymbol(bool flag);
		void	SetGreek(bool flag);
		void	SetPunctuation(bool flag);

		bool	GetHiragana();
		bool	GetKatakana();
		bool	GetAlphabet();
		bool	GetJis1Kanji();
		bool	GetJis2Kanji();
		bool	GetNumeric();
		bool	GetSymbol();
		bool	GetGreek();
		bool	GetPunctuation();

		bool Recognize(PATTERN_W &ptw);
		bool RecognizeNew(PATTERN_W &ptw);
		void Recognize(InkStroke *inkStroke, int count);
		const CharacterRecognitionResult* GetResult();
		void GetResult(char candidate[], unsigned short code[],
			double probability[]);
		void SetCandidateCount(int count);
		void SetBoundBox(PAT_POS boundBox);
		void SetBoundingSize(short size);
		void SetBoundBox(int left, int top, int right, int bottom);
		int GetCandidateCount(void);
		bool MakeRegister(InkStroke *inkStroke, int count
				, const unsigned short code	, const CharacterCategory category);
		bool Unregister(unsigned short code);
		int GetMaxCandidateScore(InkStroke *inkStroke, int count
			, unsigned short *code
			, int *scoreOn, int *scoreOff, int preClassifyCount);
		void SetRecognitionCode(const char *code);
		void WriteDictionarys(const char dicPathName[]);
		void InitIndexTable(short *indexToDicCount);
		void SetIndexTable(short *indexToDicCount);
		bool MakeRegister(InkStroke *inkStroke, int count
										  , const unsigned short code);
		bool MakeRegister(InkStroke *inkStroke, int count
										  , const unsigned int UTF8code, const unsigned short code);

        CombinationRecognizer();
        ~CombinationRecognizer();
};
//---------------------------------------------------------------------------
#endif