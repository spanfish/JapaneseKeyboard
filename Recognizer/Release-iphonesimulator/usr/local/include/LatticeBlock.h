/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      LatticeBlock.h
クラス名        LatticeBlock
解説            Latticeデータクラス
担当者          朱碧蘭

  =============================================================================
  履歴
  05/09/26        LatticeDocument.hから分離
  08/06/08  　　  担当者は織田から朱へ変更
  =============================================================================
*/

#ifndef LatticeBlockH
#define LatticeBlockH

#include <stdio.h>
#include "LatticeNode.h"
#include "ArrayList.h"
#include "InkStroke.h"
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
class SegmentPosition
{
public:
	int Start;
	int End;
	bool Changed;
	
	//15 WANG
	SegmentStatus Status;
	SegmentStatus pSegment;
	SegmentPosition(int start, int end)
	{
		Start = start;
		End   = end;
		pSegment = COMBINE;
		Status = NEW_LINE;
	}
	SegmentPosition(int start, int end, SegmentStatus p, SegmentStatus s)
	{
		Start = start;
		End   = end;
		pSegment = p;
		Status = s;
	}
};
//---------------------------------------------------------------------------
class LatticeBlock 
{
public:
	//16 Wang
	//LatticeNode    **Node;          // *Dataを可変長二次元配列に
	ArrayList<LatticeNode *> Node;
	//LatticeNode    *Data;           // 分割候補のデータ
	ArrayList<LatticeNode> Data;	// Wang
	//int            dLength;         // Dataの数
	//int            nLength;         // 節の数
	//int            *nCount;         // 各節のノードの数
	ArrayList<int> nCount;
	
	void Create(SegmentPosition *segment, int nLength, ArrayList<InkStroke> &stroke);
	void Modify(SegmentPosition *segment, int nLength, int pLength, ArrayList<InkStroke> &stroke);
	LatticeBlock Split(SegmentPosition *segment, int first_length, bool remain, ArrayList<InkStroke> &stroke);
	LatticeBlock         &operator=(const LatticeBlock &latticeBlock);

	// 入出力関数
        istream&    Read(istream &in);
        ostream&    Write(ostream &out);
	
        friend ostream  &operator<<(ostream &stream, LatticeBlock &latticeBlock);

	LatticeBlock(const LatticeBlock &latticeBlock);
	LatticeBlock();
	~LatticeBlock();
};
//---------------------------------------------------------------------------
#endif
