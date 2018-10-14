/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      SegmentLine.h
クラス名        SegmentLine
解説            手書き文字列を行単位に分割するクラス
担当者          小沼 元輝

=============================================================================
履歴
05/05/08        雛形を作成
05/05/11        担当者を織田から小沼に変更
05/05/26        一通りの機能を実装、ただし方向変化点なし
05/06/24		多少修正
05/06/24b		バッファオーバーを修正
05/06/26		バッファオーバーを修正
05/06/26b		ループ終了条件の順序が異なっていたので修正
05/09/23    	ストローク数が0だと落ちるバグを修正 by 織田
05/11/05        平均サイズの計算でストロークサイズの計算方法を変更
 　　　　　　　 行分割処理方法を変更 by 朱
				担当者を小沼から朱に変更
07/05/02		文字分割クラスの辞書ファイル名を指定するコンストラクタを追加 by 織田
07/11/27		Execute関数に枠有り認識の場合の処理を追加 by 織田
=============================================================================
*/

//---------------------------------------------------------------------------
#include "InkPage.h"
#include "SegmentCharacter.h"
#include "DetectLine.h"

#if defined(WIN32)
#else
typedef long LONG;
typedef short SHORT;
#endif

#ifndef SegmentLineH
#define SegmentLineH
//---------------------------------------------------------------------------
class SegmentLine
{
    protected:

    private:
        LONG charAveSize;
		DetectLine *detectLine;

        long GetAverageSize(InkStroke *inkStroke, int inkStrCount);
        long SetRetDetect(InkStroke *inkStroke, int inkStrCount, long aveSize);
        long SetCharacterOrientation(InkStroke *inkStroke, int inkStrCount, long aveSize);

        long EstimationCharacterOrientation(InkStroke *inkStroke, int inkStrCount, long aveSize);
        long RottationStroke(InkStroke *inkStroke, int inkStrCount, long aveSize, long Angle);
        long SetLineDirection(InkStroke *inkStroke, int inkStrCount, long aveSize);
	long SetRetDetect_Former(InkStroke *inkStroke, int inkStrCount, long aveSize);

		double getPointDistance(POINT& point1, POINT& point2);
		double getDistance(InkStroke *inkStroke, int count);
		void interpolation(InkStroke *inkStroke, int count);
		void writeDb1(char *fName, InkStroke *inkStroke, int count);

//        void GetLineRect(InkStroke *inkStroke, int inkStrCount, POINT *CenterPt, RECT *RectBox);

        //
        SHORT Enabled;

        //平均サイズ用配列
        LONG *AveSizeA;
        LONG AveSizeACount;
        LONG LineCount;

        //フラグ
        enum { m_DiviNum = 12};
        //行方向の指定(横書き限定，縦書き限定，筆記方向自由 etc)

        long SetLineAlpha(InkStroke *inkStroke, int inkStrCount, long aveSize);
        long SetLineAlpha_d1(InkStroke *inkStroke, int inkStrCount, long aveSize);
        LONG lGetOvelapRate(const RECT& rcBound1, const RECT& rcBound2, long dir);
        long SetLineAlpha_d2(InkStroke *inkStroke, int inkStrCount, long aveSize);
        long SetLineAlpha_d2a(InkStroke *inkStroke, int inkStrCount, long aveSize);
    
        void resamplePoint(vector<POINT> &points);
        void resampling(InkStroke *strokes, int strokeNum);
    
    public:
		SegmentCharacter *mySegCharacter;
        bool IsEmpty;
		LONG LastError;
		bool IsOneLine;
        void Execute(InkPage *inkPage);

    	int GetPageAvarageSize(InkPage *inkPage);
	    int GetLineCount();
    	int GetLineAvarageSize(InkStroke *inkStroke, int inkStrCount);

		SegmentLine();
		SegmentLine(char *fileName);
        ~SegmentLine();
};

#endif
