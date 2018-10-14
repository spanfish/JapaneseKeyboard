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
  07/11/15		SegmentByBounds関数ContainingBoundingBox関数を追加
  08/06/08  　　  担当者は織田から朱へ変更
  =============================================================================
*/
//---------------------------------------------------------------------------
#ifndef InkPageH
#define InkPageH

#include <iostream>

#if defined(WIN32)
#include <windows.h>
#endif

#include <string>
using namespace std;

#include "ArrayList.h"
#include "InkStroke.h"

//---------------------------------------------------------------------------
class InkPage
{
private:
	
	
public:
	int			Index;
	
	string      Text;
	ArrayList<InkStroke>    Stroke;
	ArrayList<RECT>			Bounds;
	ArrayList<InkStroke>    OldStroke;

	int						OldPosition;
	
	int         Width, Height;
	int         Left, Top, Right, Bottom;
	
	void        CopyTo(InkPage &inkPage);
	istream&    Read(istream &in);
	ostream&    Write(ostream &out);
	bool		ExportToTextFile(const char* fileName);
	void		RemoveFigure();
	void		SegmentByBounds();
	RECT		ContainingBoundingBox(int index);
	void		Normalize(void);
	
	friend ostream  &operator<<(ostream &stream, InkPage inkPage);
	InkPage         &operator=(const InkPage &inkPage);
	
	InkPage(const InkPage &inkPage);
	InkPage();
	~InkPage();
	
	//1 Wang: segment information
	bool IsFirst;
	int LastStrokeNum;
	ArrayList<int> ChangePosition;
	int NewSegmentPosition;
	int LastLatticePosition;
	int NewLatticePosition;
	ArrayList<int> LatticePosition;
	ArrayList<SegmentStatus> LastSegment;
	// recog segment infor
	ArrayList<int> RecogSegment;
};

#endif
