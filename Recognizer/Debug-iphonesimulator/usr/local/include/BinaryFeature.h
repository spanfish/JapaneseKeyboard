/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      BinaryFeature.cpp
クラス名        BinaryFeature
解説            文脈処理クラス
担当者          朱 碧蘭

=============================================================================
履歴
07/11/05       作成

=============================================================================
*/

//---------------------------------------------------------------------------
#ifndef BinaryFeatureH
#define BinaryFeatureH

//#include "..\LatticeManager\HandsCharacterRecognizer\Common\OnLinePatternProcesser.h"
#include "Crlibp2pcc.h"

#define MAX_CHARCTER_NUM 8238
#define BINARY_FEATURE_DICT "ja_JP_w_binaryFeature.res"
//---------------------------------------------------------------------------
class BinaryFeatureException
{
    private:

        // 例外を発生した行数
        int line;
        // 例外を発生したファイル名
        char * fileName;

    public:

		BinaryFeatureException(int line, char *fileName)
        {
            this->line = line;
            this->fileName = fileName;
        }
		~BinaryFeatureException() throw(){ }
};
//---------------------------------------------------------------------------
class BinaryFeature
{
    private:

		int dim;
		short index2DicIndex[MAX_CHARCTER_NUM];
		int categoryNum;
		char *charBinaryCategory;
		int classNum;
		char *binaryFeatureIndex;
		int existingBinaryCategoryNum;

		double *vector;
		float *mean;
		double *eigv;

		void Initialize(char *BinaryFeatureDict);
		unsigned short coindex(unsigned char *s);

    public:
    
		bool IsEmpty;

		double GetProbability(PAT_POS firstRect, PAT_POS secondRect,
			unsigned short firstCode, unsigned short secondCode,
			double averageSize);
		double GetProbability(float *feature, unsigned short firstCode,
			unsigned short secondCode);

		BinaryFeature();
		BinaryFeature(char *BinaryFeatureDict);
        ~BinaryFeature();
};
#endif
