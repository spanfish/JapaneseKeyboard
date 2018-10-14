/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      CharacterStructure.cpp
クラス名        CharacterStructure
解説            字形判定クラス
担当者          朱 碧蘭

=============================================================================
履歴
05/05/30        雛形を作成
05/05/30        担当者を織田から朱に変更
05/06/09        CharacterStructure管理のソースを作成
07/07/30		文字構造スコアに重みを追加
07/11/20        位置情報の確率の計算を追加
07/11/26        CHARACTER_STRUCTURE_DICT，CHARACTER_STRUCTURE_DICT_NEWの定義を
				ヘッダに移動(他のソースから参照する)by織田
07/12/16		初期化時にCHARACTER_STRUCTURE_DICT_NEWのパスを渡すように変更
=============================================================================
*/
//---------------------------------------------------------------------------
#ifndef CharacterStructureH
#define CharacterStructureH

//#include "InkDocument.h"
#include "InkPage.h"
//#include "CrLibXp.h"
#include "Crlibp2pcc.h"

#define INDEX_NUMBER 8883
#define MAX_CHARCTER_NUM 8238

#define CHARACTER_STRUCTURE_DICT "ja_JP_w_characterStructure.res"
#define CHARACTER_STRUCTURE_DICT_NEW "ja_JP_w_characterPosition.res"
//---------------------------------------------------------------------------
class CharacterStructureException
{
    private:

        // 例外を発生した行数
        int line;
        // 例外を発生したファイル名
        char * fileName;

    public:

        CharacterStructureException(int line, char *fileName)
        {
            this->line = line;
            this->fileName = fileName;
        }
        ~CharacterStructureException() throw(){ }
};
//---------------------------------------------------------------------------
enum SizeType{
	SmallCharacter 	 = 0,
	MiddleCharacter  = 1,
	BigCharacter     = 2
};
//---------------------------------------------------------------------------
enum PositionType{
	LowCharacter 	 = 0,
	NormalCharacter  = 1,
	HighCharacter    = 2
};
//---------------------------------------------------------------------------
class CharacterStructure
{
    private:

        char divisionNumber;
        unsigned char *patternInnerGaps[INDEX_NUMBER];
        int *patternSize[INDEX_NUMBER];
        int threshold;
        int powerThreshold;
        int lastThreshold;
        int PBW;
        int PBH;
		char *image;

		short index2DicIndex[MAX_CHARCTER_NUM];
		int categoryNum;
		int dim;
		double *vector;
		float *mean;
		double *eigv;

		void Initialize(const char *CharacterStructureDict,const char *CharacterStructureDictNew);
		void getInnerGap(RECT *strokeBound, int count, int *innerGap, PAT_POS boundingBox);
        void setInnerGap(int length, int size, char innerGapType, int psition, int *innerGap);
        void setStrokeBound(InkStroke *inkStroke, int count, RECT *strokeBound);
		bool isSpaceLeftTop(RECT &rect, int &bx, int &by);
		bool isSpaceLeftBottom(RECT &rect, int &bx, int &by);
		bool isSpaceRightTop(RECT &rect, int &bx, int &by);
		bool isSpaceRightBottom(RECT &rect, int &bx, int &by);
    	unsigned short coindex(unsigned char *s);
		double getPositionProbability(float *feature, unsigned short characterCode);

    public:
    
		bool IsEmpty;
        void GetProbability(InkStroke *inkStroke, int count,
			int averageSize, PAT_POS boundingBox,  int centerHigh,
			unsigned short *characterCode,
            double *characterScore, int candidateNumber = 10);
        bool PruneNode(InkStroke *inkStroke, int count, int averageSize);
		bool GetPosition(unsigned short code, float f[2]);
		bool GetSize(unsigned short code, double &w, double &h);
		PositionType GetPositionType(unsigned short code);
		SizeType GetSizeType(unsigned short code);

        CharacterStructure();
		CharacterStructure(char *CharacterStructureDict, char *CharacterStructureDictNew);
        ~CharacterStructure();
};
#endif
