/*
=============================================================================
プロジェクト名  OffLineFeatureExtraction
ファイル名      OffLineFeatureExtraction.h
クラス名        OffLineFeatureExtraction
解説            オンライン文字パタンから肉付け変換なしに直接オフライン特徴値を抽出
担当者          朱　碧蘭

=============================================================================
履歴
10/06/11        作成

=============================================================================
*/

#ifndef OffLineFeatureExtractionH
#define OffLineFeatureExtractionH

//#include "OnlinePattern.h"
//#include "FirstOnlineRecognizer.h"
#include "Normalizer.h"
//#include "..\Common\OnLinePatternProcesser.h"
//#define DIV_COUNT 5
//const unsigned short Dim = 100;

//---------------------------------------------------------------------------
class OffLineFeatureExtraction
{
    private:
		short nomalizedSize;
		double filter[110][110];	// blurring mask //●
		int wn;
		float threshold;
		unsigned char *image;
		int penWid;
		short boxSize;
		int divCount;
		Normalizer normalizer;
		unsigned short *mat[8];
		int wei[2];
		unsigned short *mat0;
		unsigned short *mat1;
		unsigned short *mat2;
		int sax, say;
		float r;
		int v;
		int type;

		void setPatternBounding(Pattern &pattern);
		void setPatternImage(unsigned char *mat, int w, int h, Pattern &pattern);
		void getNewProjection(Pattern &pattern, 
			vector<double> &verProjection, vector<double> &horiProjection);
		void tsukumo( unsigned char* mat, int wid, int hei, 
					   vector<double> &horProb, vector<double>& verProb, RECT &r);
		void lineImage(unsigned char *mat, int w, int h, POINT &p1, POINT &p2);
		void spatialFtr( unsigned char* mat[8], int wid, int hei, int zn
					, short* ftr );
		void spatialFtr( unsigned short* mat[8], int wid, int hei, int zn
					, short* ftr );
		float getDirection(int sx, int sy);
		double getPointDistance(POINT& point, double *line);
		void setFeaturePoint(POINT *point, int count, vector<POINT> &newPoint);
		void dirDecompos( unsigned char* array, int wid, int hei
										   , unsigned char *dirPat[8] );
		void postSmooth( BYTE* mat, int wid, int hei );
		void nonlinNorm( BYTE* mat1, int wid1, int hei1,
							BYTE* mat2, int wid2, int hei2,
							vector<double> &verProb, vector<double> &horiProb, RECT &r);
		void drawDot(BYTE *mat, int wid, int hei, int x, int y, int w);
		void lineDirDecompos(unsigned char *mat0, unsigned char *mat1,
									int w, int h, POINT &p1, POINT &p2);
		void connectPattern(Pattern &pat);
		void featureExtraction(Pattern &pattern, short *feature);
		void getWeight(int w, int h, float wei[2]);
		void setMat(int x0, int x1, int y0, int y1);
		void setMatV(int x0, int x1, int y0, int y1);
		void setVector(int x0, int x1, int y0, int y1);
		void lineMat(int x0, int x1, int y0, int y1);
		void lineMatV(int x0, int x1, int y0, int y1);
		void lineMat1(int x0, int x1, int y0, int y1);
		void lineMat1V(int x0, int x1, int y0, int y1);
		void gradientFeature(unsigned char *image, int w, int h, short *feature);
		void getGradient(unsigned char *image, int w, int h, 	char *matx, char *maty);
		void setVector(char dx, char dy, int id);

	public:

		int OverCount;
		bool IsCheck;

		void EatractPatternFeature(Pattern &pattern);
		void ExtractOffFeatureNew(Pattern &pattern, short *feature);
		void ExtractOffFeatureOld(Pattern &pattern, short *feature);
		void ExtractOffFeature(Pattern &pattern, short *feature);
		void ExtractConnectedOffFeature(Pattern &pattern, short *feature);
		void NolinearNormalize(Pattern &pattern);
		void NolinearNormalizeOld(Pattern &pattern);
		void Normalize(Pattern &pattern);
		void NormalizeOld(Pattern &pattern);
		void NormalizePoint(Pattern &pattern);
		void SetBoundingSize(short size);

        OffLineFeatureExtraction(int divCount);
        ~OffLineFeatureExtraction();
};
//---------------------------------------------------------------------------
#endif