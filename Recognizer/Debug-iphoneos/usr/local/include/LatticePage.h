/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      LatticePage.h
クラス名        LatticePage
解説            Latticeデータクラス
担当者          朱碧蘭

=============================================================================
履歴
05/09/26        LatticeDocument.hから分離
                CreateLink関数をLatticeManagerクラスから移動
05/09/28        Create関数,SetPositionっ関数をLatticeManagerクラスから移動                
07/11/26		HasBounds関数を追加
08/06/08  　　  担当者は織田から朱へ変更
=============================================================================
*/

#ifndef LatticePageH
#define LatticePageH
#include "InkManager.h"
#include "LatticeBlock.h"
#include "TUATList.h"

#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
class LatticePage{
	private:
		void setBlock(LatticeBlock &prevBlock, LatticeBlock &block
			, SegmentStatus presentSegment, SegmentStatus nextSegment);
		void setBlockLink(LatticeBlock *pBlock, LatticeBlock *block);

		bool hasBounds;
	public:
		TUATList<LatticeBlock> Block;  // ブロック
		//double	TrueProbability[7];
		//int TrueCharterNum;
		//PAT_POS Rect[200];
		//unsigned short Code[200];

		bool HasBounds();

		void Create(InkPage *inkPage);
		void SetPosition(InkPage *inkPage);
		void CreateLink();

		istream&    Read(istream &in);
		ostream&    Write(ostream &out);

		friend ostream  &operator<<(ostream &stream, LatticePage &latticePage);
		LatticePage     &operator=(const LatticePage &latticePage);

        LatticePage(const LatticePage &latticePage);
        LatticePage();
        ~LatticePage();

	// Wang 2011-6-27
	int SearchPosition;
};
#endif
