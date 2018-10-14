/*
=============================================================================
プロジェクト名  MRFOnlineRecognition
ファイル名      MRFOnlineRecognizer.h
クラス名        MRFOnlineRecognizer
解説            MRFOnline文字認識クラス
担当者          朱碧蘭
=============================================================================
履歴
08/11/24        作成
=============================================================================
*/

#ifndef MRFOnlineRecognizerH
#define MRFOnlineRecognizerH

#if defined(WIN32)
#include <windows.h>
#else
#include "MemoryMappedMode.h"
#define MAX_PATH 512
#endif

#include <stdio.h>
#include <math.h>

#include <vector>
//#include "..\CharacterRecognizer.h"
#include "crlibp2pcc.h"
#include "OnLinePatternProcesser.h"
#include "Sorter.h"

using namespace std;

//#define UNARY_DIM  2
//#define BINARY_DIM 2
//#define GAUSS_COUNT 1
const unsigned char SamplingVolume = 1;
//const unsigned short OffFeatureDim = 256;
//#define MAX_CHARCTER_COUNT 10868 //8978

#define DICTIONARY_FILE "ja_JP_w_onlineFine.res"
#define DICTIONARY_COUNT_FILE "ja_JP_w_onlineIndex.res"

//---------------------------------------------------------------------------

struct Result
{
	unsigned short Code;
	float Score;

	Result(float score, unsigned short code)
	{
		Score = score;
		Code = code;
	}
	Result(float score)
	{
		Score = score;
		Code = 0;
	}
	Result(void)
	{
	}
	~Result(void)
	{
	}
};

struct Model
{
	unsigned short Code;
	State **StatesP;
    //MS 20151129 IO操作はINTで行われいるなので
	short Count;
    //int Count;
    //ME 20151129
	char *StatesCount;
	
	void Write(FILE* fp)
	{
		if(fp == NULL) return;
		fwrite((char *)&Count, sizeof(int), 1, fp);
		fwrite((char *)&Code, sizeof(unsigned short), 1, fp);
		for(int i = 0; i < Count; i++)
		{
			fwrite((char *)&StatesCount[i], sizeof(char), 1, fp);
			for(int j = 0; j < StatesCount[i]; j++) StatesP[i][j].Write(fp);
		}
	}
//#if !defined(MM_FILE_READ) && !defined(MM_FILE_USE)
	void Read(FILE* fp)
	{
		if(fp == NULL) return;

		if(fp == NULL) return;
		fread((char *)&Count, sizeof(int), 1, fp);
		fread((char *)&Code, sizeof(unsigned short), 1, fp);
		if(Code >= 0x889f)
		{
			StatesP = new State*[Count];
			StatesCount = new char[Count];
			for(int i = 0; i < Count; i++)
			{
				fread((char *)&StatesCount[i], sizeof(char), 1, fp);
				StatesP[i] = new State[StatesCount[i]];
				for(int j = 0; j < StatesCount[i]; j++) 
				{
					StatesP[i][j].SetCharId();
					StatesP[i][j].Read(fp);
				}
			}
		}
		else {
			StatesP = new State*[Count];
			StatesCount = new char[Count];
			for(int i = 0; i < Count; i++)
			{
				fread((char *)&StatesCount[i], sizeof(char), 1, fp);
				StatesP[i] = new State[StatesCount[i]];
				for(int j = 0; j < StatesCount[i]; j++) 
				{
					StatesP[i][j].SetNoCharId();
					StatesP[i][j].Read(fp);
				}
			}
		}
	}

	void Reset(void)
	{
		for(int i = 0; i < Count; i++)
			delete []StatesP[i];
		if(Count != 0) 
		{
			delete []StatesP;
			delete []StatesCount;
		}
		StatesP = NULL;
		Count = 0;
		StatesCount = NULL;
	}

	Model(const Model &model)
	{
		Code = model.Code;

		if(model.Count != 0)
		{
			if(Code >= 0x889f)
			{
				Count = model.Count;
				StatesP = new State*[Count];
				StatesCount = new char[Count];
				for(int i = 0; i < Count; i++)
				{
					StatesCount[i] = model.StatesCount[i];
					StatesP[i] = new State[StatesCount[i]];
					for(int j = 0; j < StatesCount[i]; j++) 
					{
						StatesP[i][j] = model.StatesP[i][j];
					}
				}
			}
			else {
				Count = model.Count;
				StatesP = new State*[Count];
				StatesCount = new char[Count];
				for(int i = 0; i < Count; i++)
				{
					StatesCount[i] = model.StatesCount[i];
					StatesP[i] = new State[StatesCount[i]];
					for(int j = 0; j < StatesCount[i]; j++) 
					{
						StatesP[i][j] = model.StatesP[i][j];
					}
				}
			}
		}
		else
		{
			StatesP = NULL;
			Count = 0;
			StatesCount = NULL;
		}
	}

	Model &operator=(const Model &model)
	{
		for(int i = 0; i < Count; i++)
			delete []StatesP[i];
		if(Count != 0) 
		{
			delete []StatesP;
			delete []StatesCount;
		}

		Code = model.Code;

		if(model.Count == 0) 
		{
			StatesP = NULL;
			Count = 0;
			StatesCount = NULL;			
			return *this;
		}

		if(Code >= 0x889f)
		{
			Count = model.Count;
			StatesP = new State*[Count];
			StatesCount = new char[Count];
			for(int i = 0; i < Count; i++)
			{
				StatesCount[i] = model.StatesCount[i];
				StatesP[i] = new State[StatesCount[i]];
				for(int j = 0; j < StatesCount[i]; j++) 
				{
					StatesP[i][j] = model.StatesP[i][j];
				}
			}
		}
		else {
			Count = model.Count;
			StatesP = new State*[Count];
			StatesCount = new char[Count];
			for(int i = 0; i < Count; i++)
			{
				StatesCount[i] = model.StatesCount[i];
				StatesP[i] = new State[StatesCount[i]];
				for(int j = 0; j < StatesCount[i]; j++) 
				{
					StatesP[i][j] = model.StatesP[i][j];
				}
			}
		}
		return *this;
	}
//#endif

	Model(void)
	{
		StatesP = NULL;
		Count = 0;
		StatesCount = NULL;
	}
	~Model(void)
	{
#if (defined(MM_FILE_READ) || defined(MM_FILE_USE))
        for(int i = 0; i < Count; i++)
            delete []StatesP[i];
        if(Count != 0)
        {
            delete []StatesP;
            //delete []StatesCount;
        }
#else
        for(int i = 0; i < Count; i++)
            delete []StatesP[i];
        if(Count != 0)
        {
            delete []StatesP;
            delete []StatesCount;
        }
#endif

	}
};

/*//---------------------------------------------------------------------------
class RecognizerException
{
    private:

        // 例外を発生した行数
        int line;
        // 例外を発生したファイル名
        char * file_name;

    public:

        int GetRecognizerExceptionLine(void) const
        {
            return line;
        }

        const char *GetRecognizerExceptionFile(void) const
        {
            return file_name;
        }

        void print( void ) const
        {
            FILE *fp = fopen("RecognizerExceptionFile.txt", "w");
            if(fp != NULL){
                fprintf(fp,"Line:%d FileName:%s\n", line, file_name);
                fclose(fp);
            }
        }

        RecognizerException(int tline, char *tfile_name)
        {
            line = tline;
            file_name = tfile_name;
        }
        ~RecognizerException() throw(){ }
};*/
//---------------------------------------------------------------------------
#define SIZE_MODEL_LIST		40000000
    
typedef struct tagModelListHead {
    int count;
    int offsetHead;
    int offsetData;
    int dataSize;
        
    // 20130127 AS zhaojian
    int offsetBookData;// 20130127 Add for Samll dic by zhaojian（offsetBookData =元々のdataSize）offsetBookDataはmeanCodeBook等のデータの開始位置
    //2013.02.04 AS zhaojian
    int offsetMeanCodeBook_NoChar;
    int offsetWeightCodeBook_NoChar;
    int offsetMeanCodeBookB_NoChar;
    int offsetWeightCodeBookB_NoChar;
    int offsetProbCodeBook;
    int offsetMeanCodeBook_Char;
    int offsetWeightCodeBook_Char;
    int offsetMeanCodeBookB_Char;
    int offsetWeightCodeBookB_Char;
    //
    int p_offsetMeanCodeBook_NoChar;
    int p_offsetWeightCodeBook_NoChar;
    int p_offsetMeanCodeBookB_NoChar;
    int p_offsetWeightCodeBookB_NoChar;
    int p_offsetProbCodeBook;
    int p_offsetMeanCodeBook_Char;
    int p_offsetWeightCodeBook_Char;
    int p_offsetMeanCodeBookB_Char;
    int p_offsetWeightCodeBookB_Char;
    //2013.02.04 AE
        // 20130127 AS
} ModelListHead;
    
    
typedef struct tagModelList {
    ModelListHead head;
    unsigned char data[1];
} ModelList;
    
typedef struct tagRModelHead {
    unsigned short Code;
    short Count;
    int offsetStatesP;
    int offsetStatesCount;
} RModelHead;

class MRFOnlineRecognizer
{

    private:
#if defined(MM_FILE_USE)
    int		hFile;
    int		map_size;
    //HANDLE		hMMMap;
#endif
#if defined(MM_FILE_WRITE) || defined(MM_FILE_READ) || defined(MM_FILE_USE)
    ModelList *pData;		// ADD K.Iwakura 2010/12/08
#endif
		int candidateCount;
		//float threshold;
		vector<Model> models;
		float weight[3];
		Node *nodeDate;
		int maxStateCount;
		double minDis;
		Sorter sort;

		//short maxMean, minMean;
		//float maxWeight[4], minWeight[4];
		//float maxProb, minProb;

		short **meanCodeBook;
		float **weightCodeBook;
		short **meanCodeBookB;
		float **weightCodeBookB;
		float **probCodeBook;

		short **meanCodeBook_Char;
		float **weightCodeBook_Char;
		short **meanCodeBookB_Char;
		float **weightCodeBookB_Char;

		short **meanCodeBook_NoChar;
		float **weightCodeBook_NoChar;
		short **meanCodeBookB_NoChar;
		float **weightCodeBookB_NoChar;

		void openDictionary(const char dicName[]) throw (RecognizerException);
#if defined(MM_FILE_READ) || defined(MM_FILE_USE)
        void setBookData(ModelList *pData);
#endif
		void freeDictionary(void);
		//double getPointDistance(POINT& point, double *line);
		//void setFeaturePoint(POINT *point, int count, vector<POINT> &newPoint);
		//void setPatternBounding(Pattern &pattern);
		float getDirection(int sx, int sy);
		float getSimility(vector<Feature> &features, State *state, char statesCount);
		float dpMatching(vector<Feature> &features, State *state, char statesCount);
		float getBinaryProbability(short *feature, State &state, int fNum);
		float getUnaryProbability(short *feature, State &state);
		void getBinaryFeature(short *feature, POINT &p1, POINT &p2);
		bool setPoints(vector<Feature> &features, Pattern &pattern);
		float getOutputProbability(short sx, short sy, short *v, float corr);
		void setOutputWeight(float *w, short *v, float corr);
		float getOutputProbability(short sx, short sy, float *w);
		float getOutputProbability(short *f, float *w);
		//void transformPattern(PATTERN_W &ptw, Pattern &pat);
		float getStateProb(State &state, int fNum);

	public:
		bool IsEmpty;
		short IndexToDicCount[MAX_CHARCTER_COUNT];

		//unsigned short coindex(unsigned short code);
		void SetCandidateCount(int candidateCount);
		//void EatractPatternFeature(Pattern &pattern);
		void Normalize(Pattern &pattern);
		void NormalizePoint(Pattern &pattern);
		void GetDicPattern(Pattern &dicPattern, int id, int subId);
		int GetDicPatternCount(void);
		int GetSubDicPatternCount(int id);
		vector<Model> &GetModels(void);
		int GetStateCount(int id, int subId);
		void SetWeight(float *weight);
		int GetMaxStateCount(void);
		void ResetModels(void);
		void ResetModels(int id);
		float GetSimilityWithModel(PATTERN_W &ptw, int index);
		void GetSimilityWithModel(PATTERN_W &ptw, int *index,
												double *score, int count);
		void GetSimilityWithModel(Pattern &pattern, int *index,
												double *score, int count);
		void Recognize(PATTERN_W &ptw, vector<Result> &result,
									vector<short> &firstCandidate);
		bool Recognize(Pattern &pattern, unsigned short *code, 
								 int *score, int count);
		bool Recognize(Pattern &pattern, int *index, 
								 int *score, int count);
		bool Recognize(vector<Feature> &features, int *index, 
								 int *score, int count);
		int GetCandidate(Pattern &pattern, short *candidate, short *recogIndex);

		int Recognize(Pattern &pattern, int *index, 
								 int *score, int count, int smallCount);
		int GetMaxScore(void);
		void ExtractPartCharacters(short *indexToDicCount, int count);
		void WriteDictionary(const char dicName[], const char dicCountName[]);
		void ReWriteDictionary(const char dicName[]);

		MRFOnlineRecognizer();
		MRFOnlineRecognizer(const char dicName[], const char dicCountName[]);
		~MRFOnlineRecognizer();
};
//---------------------------------------------------------------------------
#endif