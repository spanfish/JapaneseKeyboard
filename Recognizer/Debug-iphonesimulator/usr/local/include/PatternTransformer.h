/*
=============================================================================
プロジェクト名  PatternTransformer
ファイル名      PatternTransformer.h
クラス名        PatternTransformer
解説            文字認識クラス
担当者          陳邊
=============================================================================
履歴
09/09/04        作成
=============================================================================
*/

#ifndef PatternTransformerH
#define PatternTransformerH

#include "MRFOnLineRecognizer.h"

#define MAXTRASFORMS 30

using namespace std;

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class PatternTransformer
{
	private:
		Pattern transformedPattern[MAXTRASFORMS*10+1];

		void changeDegree(double theta, Pattern &pattern, Pattern *pat);
		void paintTransform(Pattern &pattern, double rotate_theta, double theta1,
		int rotation_x, int rotation_y, Pattern &newPattern, int type);
		void matrixCalculator(int dimension,double matrix_in1[],double matrix_in2[],double matrix_out[]);
		void reversePatternX(Pattern &pattern);
		void reversePatternY(Pattern &pattern);
		void normalize(Pattern &pattern);
		void setPatternBounding(Pattern &pattern);

	public:

		Pattern* Transform(Pattern pattern, int &count);

		PatternTransformer();
		~PatternTransformer();
};
//---------------------------------------------------------------------------
#endif
