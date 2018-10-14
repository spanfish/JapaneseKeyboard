/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      InkPage.h
クラス名        InkPage
解説            Inkデータクラス
担当者          朱碧蘭

=============================================================================
履歴
05/05/08        作成
05/09/11        InkDocument.hファイルから独立
07/11/15		GetCenterPoint関数を追加
07/11/20        NodeBound，WritingBox，AverageSize，Start，End，IsCheckScore，
				SegmentProbability，CenterHighを追加
08/06/08        NoSegmentProbabilityと過分割の変数の追加 by朱
08/06/08    　　担当者は織田から朱へ変更
=============================================================================
*/

//---------------------------------------------------------------------------


#ifndef InkStrokeH
#define InkStrokeH

#include "ArrayList.h"
#include <iostream>

#if defined(WIN32)
#include <windows.h>
#else
#include "CWinStruct.h"
#endif

//#include <wndb.h>
using namespace std;

struct InkBounds
{
	public:
	int Width, Height;
	int Left, Top, Right, Bottom;

	InkBounds(ArrayList<POINT>    &point)
	{
		Left =    999999;
		Top  =    999999;
		Right =  -999999;
		Bottom = -999999;

		for(int i = 0 ; i < point.GetCount() ; i++)
		{
			int x = point[i].x;
			int y = point[i].y;

			if(Left   > x) Left = x;
			if(Top    > y) Top  = y;
			if(Right  < x) Right = x;
			if(Bottom < y) Bottom = y;
		}

		Width = Right - Left;
		Height = Bottom - Top;
	}
};
//---------------------------------------------------------------------------
enum SegmentStatus
{
	COMBINE     = 0,	// 結合
	NEW_LINE    = 1,	// 改行
	VAGUE       = 2,	// 分割候補
	DIVIDE      = 3		// 分割
};
//---------------------------------------------------------------------------
class InkStroke
{
	private:

	public:
		//WNDB_STROKEAI 		Information;

        bool				IsFigure;
		RECT				Bound;
		WORD				TextTag;
		ArrayList<POINT>    Point;

		ArrayList<POINT>    ConvexBefore;
		ArrayList<POINT>    ConvexAfter;
		int					Overlap;
		int 				Distance;
		int 				IntersectLong;
		int					Feature[20];
		int 				Length;

		char                Code[3];
        SegmentStatus       Segment;  // 分割情報
        double              Angle;
		unsigned short      offStrokeTime;
		//bool 				isPrint;
		//int 				number;
		RECT				NodeBound;
		RECT	         	WritingBox;   // 推定入力枠
		double          	AverageSize;  // 属する行の平均文字サイズ
		double				SetAverageSize;
		int 				Start;
		int 				End;
		bool				IsCheckScore;
		double				SegmentProbability;
		double				NoSegmentProbability;
		int					CenterHigh;

		RECT				GetBounds();
		int					GetSize();
		POINT				GetCenterPoint();
        void                CopyTo(InkStroke &inkStroke);
		void  			    CopyToPoint(InkStroke &inkStroke);
        istream&            Read(istream &in);
        ostream&            Write(ostream &out);
        InkStroke           &operator=(const InkStroke &inkStroke);
        friend ostream      &operator<<(ostream &stream, InkStroke inkStroke);
		static				RECT GetBounds(InkStroke *stroke, int count);

        InkStroke(const InkStroke &inkStroke);
        InkStroke();
        ~InkStroke();
};
#endif
