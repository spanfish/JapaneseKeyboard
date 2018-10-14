/*
=============================================================================
プロジェクト名  Normalizer
ファイル名      Normalizer.h
クラス名        Normalizer
解説            Noliner Normalizer
担当者          朱　碧蘭

=============================================================================
履歴
10/11/28        作成

=============================================================================
*/

#ifndef NormalizerH
#define NormalizerH

//#include "FirstOnlineRecognizer.h"
#include "OnLinePatternProcesser.h"

//---------------------------------------------------------------------------
class Normalizer
{
    private:

		double *proxj[3], *proyj[3];
		double *wy[2], *wx[2];
		double B;
		short boxSize;
		double ax[4], ay[4];

		void smoothing(Pattern &pattern);
		void getProjection(Pattern &pattern, double *prox, double *proy);
		void getMoment(double *prox, double *proy, int w, int h,
							   double &x_c, double &y_c, double &dx, double &dy);
		double getMoment(double *pro, int l, double &c, double &d);
		void setProjection(double *prox, double *proy, /*int w, int h,*/ int x0, int x, int y0, int y);
		void momentNormalization(Pattern &pattern);

		int getCentroid(double *pro, int l, double &c);
		void getBiMoment(double *pro, int l, double &c, 
							 double &d0, double &d1, double sum);

		double getDeterminant(double *a0, double *a1, double *a2);
		void getKuramerureSolution(double a[3][3], double x[3], double b[3]);
		double getDeterminant(double *a0, double *a1);
		void getKuramerureSolution(double d0, double c, double d1, double x[3]);
		double getQuadFunctionResult(double a[3], double x);

		void getBasicQuadFunction(double c, double x[2]);
		void getQuadFunction(double d0, double c, double d1, double x[4]);
		void Output(Pattern &pattern, int size, double a1[4], double a2[4], int w, int h);

		void getWeight(double *w[2], int l, double c, double d1);
		void getProjection(Pattern &pattern, double x_c, double y_c);
		void setProjection(double *prox[3], double *proy[3], double d, double x_c, double y_c
			, int x0, int x1, int y0, int y1, double *wx[2], double *wy[2]);
		void setProjection(double *prox[3], double *proy[3], double x_c, double y_c,
							   int x, int y, double *wx[2], double *wy[2]);
		void setProjection(double *prox[3], double *proy[3], double x_c, double y_c
							   , int x0, int x1, int y0, int y1, double *wx[2], double *wy[2]);
		void Output(Pattern &pattern, int size, double a1[3][4], double a2[3][4]
						, int w, int h, double x_c, double y_c);

		void normalizeOld(Pattern &pattern);

	public:

		bool IsLinearNorma;

		void SetBoundingSize(short size);
		void Normalize(Pattern &pattern, int size);
		void BimomentNormalization(Pattern &pattern, int size);
		void Normalize(Pattern &pattern, Pattern &pattern0, int size);
		void Normalize(Pattern &pattern, int size, short feature[18]);

        Normalizer();
        ~Normalizer();
};
//---------------------------------------------------------------------------
#endif