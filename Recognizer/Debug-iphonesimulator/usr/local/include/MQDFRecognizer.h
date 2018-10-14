/*
=============================================================================
プロジェクト名  MQDFRecognizer
ファイル名      MQDFRecognizer.h
クラス名        MQDFRecognizer
解説            MQDFオンライン文字認識
担当者          朱　碧蘭

=============================================================================
履歴
10/06/11        作成

=============================================================================
*/

#ifndef MQDFRecognizerH
#define MQDFRecognizerH

//#include "FirstOnlineRecognizer.h"
#include "QDF.h"
#include "OffLineFeatureExtraction.h"

//#define MAX_CHARCTER_NUM 10868
#define MAX_UTF8_CHARCTER_COUNT 71936

//---------------------------------------------------------------------------
class MQDFRecognizer
{
    private:
	
		CQDF *theQDF;
		CQDF *theQDFOff;
		CQDF *theQDFOn1;
		CQDF *theQDFOn2;
		double *comVectorOff, *comVectorOn, *comVector;
		int firstCandidateCount;
		int cNum;
		unsigned short *dicCountToCode;
		unsigned int *dicCountToUTF8Code;
		short indexToDicCount[MAX_CHARCTER_COUNT];
		short indexUTF8ToDicCount[MAX_UTF8_CHARCTER_COUNT];
		OffLineFeatureExtraction *feaExtra;
		OffLineFeatureExtraction *feaExtra256;

		int recog(short *ftrVct ,int *resu, double *qd, int candidateCount);
		int eigRecog( short* ftr, int dim, int* index, int* euclid
							 , int cnum, CQDF* pQDF,int *resu,double *qd,int num);
		bool addCode(unsigned int UTF8code, unsigned short code, short id);
		bool addCode(unsigned short code, short id);
		bool deleteCode(unsigned short index);

		int getCandidate(short *fea, CQDF* pQDF, unsigned short *code
				 , int preClassifyCount, int count, int dim);
		int getCandidate(short *fea, CQDF* pQDF, int *index
				 , int preClassifyCount, int count, int dim);
		int getCandidate(short *fea, CQDF* pQDF1, CQDF* pQDF2, int *index
									  , int preClassifyCount
									  , int count, int dim1, int dim2);
		void compressData(double *vec, short *data, int dim, short *dataTo, int dimTo);
		void setCandidate(void);
		int codeToStr(unsigned int code, char *str);

	public:
		int dim;
		int dimOff, dimOn1, dimOn2;
		short feature[600];
		bool IsCheck;
		short *Candidate;
		int FirstCount;

		int ErrCode;
		bool IsEmpty;

		void Recognize(Pattern &pat, unsigned short *code, double *score,
							  int candidateCount);
		double Recognize(Pattern &pat, unsigned short code);
		void Recognize(unsigned short *code, int *score,
							  int candidateCount);
		void Recognize(int *index, int *score, int candidateCount);
		void RecognizeRe(int *index, int *score, int candidateCount);
		int Recognize(int *index, int *score, int candidateCount, int count);
		//unsigned short coindex(unsigned short code);
		int CoarseClassify(Pattern &pat, unsigned short *code, int *score,
									int preClassifyCount);
		void SetIsCheck(bool isCheck);
		void SetBoundingSize(short size);
    
		bool AddCharacter(short *intMn, int *intEig, short* intVec,
			int intVar, unsigned int UTF8code, unsigned short code);
		bool AddCharacter(short *intMn, int *intEig, short* intVec,
			int intVar, unsigned short code);
		bool AddCharacterOff(short *intMn, int *intEig, short* intVec,
			int intVar, unsigned short code);
		bool AddCharacterOn1(short *intMn, int *intEig, short* intVec,
			int intVar, unsigned short code);
		bool AddCharacterOn2(short *intMn, int *intEig, short* intVec,
			int intVar, unsigned short code);

		bool DeleteCharacter(unsigned short code);
		void FeatureExtraction(Pattern &pat);
		int CoarseClassifyOn(Pattern &pat, unsigned short *code
									  , int preClassifyCount, int count);
		int CoarseClassifyOff(Pattern &pat, unsigned short *code
									  , int preClassifyCount, int count);
		int CoarseClassifyOn(Pattern &pat,  int *index
									  , int preClassifyCount, int count);
		int CoarseClassifyOff(Pattern &pat,  int *index
									  , int preClassifyCount, int count);
		unsigned short GetCode(int id);
		int GetMaxScore(void);
		bool ExtractPartCharacters(short *indexToDic, int count);
		bool WriteDictionary(const char dicPathName[]);

		void FeatureConnectedExtraction(Pattern &pat, int dimOn);
		int GetUFT8Str(unsigned short code, char *str);
		unsigned int GetUTF8CodeId(unsigned int code);
		unsigned int GetUTF8CodeId(char *str);
		unsigned short GetUTF8CodeDicId(char *str);
		int GetCodeDicId(unsigned short code);
		
		bool AddTemplate(short *intMn, int *intEig
								, short* intVec,int intVar, unsigned short code);
		bool AddTemplateOn1(short *intMn, int *intEig
								, short* intVec,int intVar, unsigned short code);
		bool AddTemplateOn2(short *intMn, int *intEig
								, short* intVec,int intVar, unsigned short code);
		bool AddTemplateOff(short *intMn, int *intEig
								, short* intVec,int intVar, unsigned short code);

        MQDFRecognizer();
		MQDFRecognizer(const char dicName[], const char dicCompreName[], const char dicCountName[]);
        //20130828 
		//MQDFRecognizer::MQDFRecognizer(const char dicName[], const char dicCodebook[],const char dicCompreName[]
		//					   , const char dicCountName[]);
        MQDFRecognizer(const char dicName[], const char dicCodebook[],const char dicCompreName[]
                                   , const char dicCountName[]);
        ~MQDFRecognizer();
};
//---------------------------------------------------------------------------
#endif