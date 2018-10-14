/*
=============================================================================
プロジェクト名  OnLinePatternProcesser
ファイル名      OnLinePatternProcesser.h
クラス名        OnLinePatternProcesser
解説            オンラインデータの定義
担当者          朱碧蘭
=============================================================================
履歴
10/06/30        作成
=============================================================================
*/

#ifndef OnLinePatternProcesserH
#define OnLinePatternProcesserH

#if defined(WIN32)
#include <windows.h>
#else
#define MAX_PATH 512
#include "InkStroke.h"
#endif

#include <stdio.h>
#include <vector>
#include <math.h>
#include "crlibp2pcc.h"
#include "MemoryMappedMode.h"

using namespace std;

#define MAX_CHARCTER_COUNT 10868
#define UNARY_DIM  2
#define BINARY_DIM 2
#define GAUSS_COUNT 1

//---------------------------------------------------------------------------
enum ProcessingStatus{
	SRE_NoMatter 	 = 0,// 問題なく，処理は成功した
	SRE_NotAvailable = 1,// その時点では利用できない API 関数を呼出した
	SRE_MemoryAlloc  = 2,// 必要なメモリが確保できなかった
	SRE_FileOpen	 = 3,// ファイルが開けなかった
	SRE_IllegalArg	 = 4,// 関数に渡す引数が正しくない
	SRE_Other		 = 5 // その他の理由で失敗した
};
//---------------------------------------------------------------------------
struct Node
{
	float Score;
	Node *PrevNode;
	int Id;
	Node(void)
	{
		PrevNode = NULL;
		Score = 0;
	}
	~Node(void)
	{
	}
};
//---------------------------------------------------------------------------
struct Stroke
{
	vector<POINT> Point;
	vector<POINT> FeaturePoint;
	Stroke(void)
	{
		Point.clear();
		FeaturePoint.clear();
	}
	~Stroke(void)
	{
	}
};
//---------------------------------------------------------------------------
struct Feature
{
	short UnaryFeature[UNARY_DIM];
	short BinaryFeature[BINARY_DIM];
	Node *NodeP;
	short StartId;
	short EndId;
	Feature(void)
	{
		;
	}
	~Feature(void)
	{
	}
};
//---------------------------------------------------------------------------
struct State
{
	//float TransitionProb[3];
	//short UnaryMean[UNARY_DIM * GAUSS_COUNT];
	//float UnaryWeight[4];
	//short BinaryMean[3][BINARY_DIM * GAUSS_COUNT];
	//float BinaryWeight[3][4];

	unsigned char *CharId;
	unsigned short *NoCharId;
	
	void Write(FILE* fp)
	{
		if(fp == NULL) return;
		/*fwrite((char *)TransitionProb, sizeof(float) * 3, 1, fp);
		fwrite((char *)UnaryMean, sizeof(short) * UNARY_DIM * GAUSS_COUNT, 1, fp);
		fwrite((char *)BinaryMean[0], sizeof(short) * BINARY_DIM * GAUSS_COUNT, 1, fp);
		fwrite((char *)BinaryMean[1], sizeof(short) * BINARY_DIM * GAUSS_COUNT, 1, fp);
		fwrite((char *)BinaryMean[2], sizeof(short) * BINARY_DIM * GAUSS_COUNT, 1, fp);
		fwrite((char *)UnaryWeight, sizeof(float) * 4, 1, fp);
		fwrite((char *)BinaryWeight[0], sizeof(float) * 4, 1, fp);
		fwrite((char *)BinaryWeight[1], sizeof(float) * 4, 1, fp);
		fwrite((char *)BinaryWeight[2], sizeof(float) * 4, 1, fp);*/

		if(CharId != NULL) fwrite((char *)CharId, sizeof(unsigned char), 9, fp);
		if(NoCharId != NULL) fwrite((char *)NoCharId, sizeof(unsigned short), 9, fp);
	}
	void Read(FILE* fp)
	{
		if(fp == NULL) return;
		/*fread((char *)TransitionProb, sizeof(float) * 3, 1, fp);
		fread((char *)UnaryMean, sizeof(short) * UNARY_DIM * GAUSS_COUNT, 1, fp);
		fread((char *)BinaryMean[0], sizeof(short) * BINARY_DIM * GAUSS_COUNT, 1, fp);
		fread((char *)BinaryMean[1], sizeof(short) * BINARY_DIM * GAUSS_COUNT, 1, fp);
		fread((char *)BinaryMean[2], sizeof(short) * BINARY_DIM * GAUSS_COUNT, 1, fp);
		fread((char *)UnaryWeight, sizeof(float) * 4, 1, fp);
		fread((char *)BinaryWeight[0], sizeof(float) * 4, 1, fp);
		fread((char *)BinaryWeight[1], sizeof(float) * 4, 1, fp);
		fread((char *)BinaryWeight[2], sizeof(float) * 4, 1, fp);*/

		if(CharId != NULL) fread((char *)CharId, sizeof(unsigned char), 9, fp);
		if(NoCharId != NULL) fread((char *)NoCharId, sizeof(unsigned short), 9, fp);

		CheckWeight();
	}

	void SetCharId(void)
	{
		if(CharId != NULL) delete []CharId;
		CharId = new unsigned char[9];

		if(NoCharId != NULL) delete []NoCharId;
		NoCharId = NULL;
	}

	void SetNoCharId(void)
	{
		if(NoCharId != NULL) delete []NoCharId;
		NoCharId = new unsigned short[9];

		if(CharId != NULL) delete []CharId;
		CharId = NULL;
	}

	void CheckWeight(void)
	{
		/*int i;
		for( i = 0; i < 3; i++) 
		{
			for(int j = 0; j < 4; j++)
			{
				if(BinaryWeight[i][j] < -8888)
				{
					for(int k = 0; k < 4; k++)
						BinaryWeight[i][k] = -8888;
					break;
				}
			}
		}
		for(i = 0; i < 3; i++) 
		{
			if(UnaryWeight[i] < -8888)
			{
				for(int k = 0; k < 4; k++)
					UnaryWeight[k] = -8888;
				break;
			}
		}*/
	}

	static void SetOutputWeight(float *w, short *m, double *v, float corr, float weight)
	{
		float v1 = v[0] * v[0];
		float v2 = v[1] * v[1];
		float p = 1 - corr * corr;

		if(fabs(p) <= 0.000001 || fabs(corr) >= 1)
		{
			w[2] = 0;
			if(v1 != 0)
			{
				w[0] = 1.0 / (v1 * -2);
				w[1] = 0;
				w[3] = log(v1) / -2;
			}
			else if(v2 == 0)
			{
				w[1] = 0;
				w[0] = 0;
				w[3] = 0;				
			}
			else {
				w[1] = 1.0 / (v2 * -2);
				w[0] = 0;
				w[3] = log(v2) / -2;
			}

			return;
		}

		w[0] = 1.0 / (v1 * p * -2); 
		w[1] = 1.0 / (v2 * p * -2);
		w[2] = corr / (v[0] * v[1] * p);		
		w[3] = log(v1 * v2 * p) / -2;
	}

	void Reset(short *unaryMean, short binaryMean[3][BINARY_DIM])
	{
		/*for(int i = 0; i < 3; i++) 
		{
			TransitionProb[i] = 0;
			double v[BINARY_DIM];
			for(int j = 0; j < BINARY_DIM; j++)
				v[j] = 1;
			SetOutputWeight(BinaryWeight[i], binaryMean[i], v, 0, 1);
		}
		double v[UNARY_DIM];
		for(int j = 0; j < UNARY_DIM; j++)
			v[j] = 1;
		SetOutputWeight(UnaryWeight, UnaryMean, v, 0, 1);*/
	}

	/*State(short *unaryMean, short binaryMean[3][BINARY_DIM])
	{
		for(int i = 0; i < 3; i++) 
		{
			TransitionProb[i] = 0;
			double v[BINARY_DIM];
			for(int j = 0; j < BINARY_DIM; j++)
				v[j] = 1;
			SetOutputWeight(BinaryWeight[i], binaryMean[i], v, 0, 1);
		}
		double v[UNARY_DIM];
		for(int j = 0; j < UNARY_DIM; j++)
			v[j] = 1;
		SetOutputWeight(UnaryWeight, UnaryMean, v, 0, 1);
	}*/

	State &operator=(const State &state)
	{
		if(state.CharId != NULL) 
		{
			if(CharId != NULL) delete []CharId;
			CharId = new unsigned char[9];
			memmove(CharId, state.CharId, sizeof(unsigned char) * 9);
		}
		if(state.NoCharId != NULL) 
		{
			if(NoCharId != NULL) delete []NoCharId;
			NoCharId = new unsigned short[9];
			memmove(NoCharId, state.NoCharId, sizeof(unsigned short) * 9);
		}

		/*for(int i = 0; i < 3; i++)
		{
			TransitionProb[i] = state.TransitionProb[i];			
			memmove(BinaryMean[i], state.BinaryMean[i], sizeof(short) * BINARY_DIM);
			memmove(BinaryWeight[i], state.BinaryWeight[i], sizeof(float) * 4);
		}
		memmove(UnaryMean, state.UnaryMean, sizeof(short) * UNARY_DIM);
		memmove(UnaryWeight, state.UnaryWeight, sizeof(float) * 4);*/
		
		return *this;
	}

	State(const State &state)
	{
		if(state.CharId != NULL) 
		{
			CharId = new unsigned char[9];
			memmove(CharId, state.CharId, sizeof(unsigned char) * 9);
		}
		if(state.NoCharId != NULL) 
		{
			NoCharId = new unsigned short[9];
			memmove(NoCharId, state.NoCharId, sizeof(unsigned short) * 9);
		}

		/*for(int i = 0; i < 3; i++)
		{
			TransitionProb[i] = state.TransitionProb[i];			
			memmove(BinaryMean[i], state.BinaryMean[i], sizeof(short) * BINARY_DIM);
			memmove(BinaryWeight[i], state.BinaryWeight[i], sizeof(float) * 4);
		}
		memmove(UnaryMean, state.UnaryMean, sizeof(short) * UNARY_DIM);
		memmove(UnaryWeight, state.UnaryWeight, sizeof(float) * 4);*/
	}

	State(void)
	{
		CharId = NULL;
		NoCharId = NULL;
	}
	~State(void)
	{
#if (!defined(MM_FILE_READ) && !defined(MM_FILE_USE))
		if(CharId != NULL) delete []CharId;
		if(NoCharId != NULL) delete []NoCharId;
#endif
	}
};
//---------------------------------------------------------------------------
struct Pattern
{
  public:  
	vector<Stroke> Str;
	bool IsExtractedFeature;
	unsigned short Code;
	RECT Bounding;
	bool IsSetBounding;

	vector<Feature> Features;
	char WhichClass;
	vector<State> States;

	void Clear(void)
	{
		IsExtractedFeature = false;
		IsSetBounding = false;
		Str.clear();
		Features.clear();
	}
	Pattern(void)
	{
		IsExtractedFeature = false;
		IsSetBounding = false;
		Str.clear();
		Features.clear();
		WhichClass = 0;
	}
	~Pattern(void)
	{
	}
};
//---------------------------------------------------------------------------
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
};
//---------------------------------------------------------------------------
class OnLinePatternProcesser
{
	private:
		
		//float threshold;

		static void setFeaturePoint(POINT *point, int count,
			vector<POINT> &newPoint, float threshold);
		static double getPointDistance(POINT& point, double *line);

    public:

		static void TransformToPattern(PATTERN_W &m_patw, Pattern &pat);
		static void SetOnlinePat(Pattern &pattern, PATTERN_W &m_patw);
		static void SetPatternBounding(Pattern &pattern);
		static unsigned short GetCodeId(unsigned short code);
		static void EatractPatternFeature(Pattern &pattern);
	
		OnLinePatternProcesser();
		~OnLinePatternProcesser();
};
//---------------------------------------------------------------------------
#endif