
/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      LatticeNode.h
クラス名        LatticeNode
解説            Latticeデータクラス
担当者          朱碧蘭

=============================================================================
履歴
05/09/26        LatticeDocument.hから分離
07/07/30        Candidateクラス追加，LatticeNodeにcandidateとNumを追加  by 朱
07/11/20        BaseNum，IsCheckScore，SegmentProbability，IsTrue，CenterHighを追加 by 朱
07/12/10        ノードあたりに最大何個かのパスを残す高速化処理のためのデータ追加 by 朱
08/06/08        NoSegmentProbabilityの追加 by朱
08/06/08  　　  担当者は織田から朱へ変更
=============================================================================
*/

#ifndef LatticeNodeH
#define LatticeNodeH


#include <stdio.h>
#include "Crlibp2pcc.h"
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
const int CANDIDATE_COUNT = 25;//20;//30;//60;//
const int MAX_PATH_COUNT = 20;//5;//20;//40;//
//---------------------------------------------------------------------------
// ノードの位置
enum NodePosition
{
	LATTICE_HEAD = 0,
	LINE_HEAD    = 1,
	BLOCK_HEAD   = 2,
	ELEMENT      = 3,
	BLOCK_TAIL   = 4,
	LINE_TAIL    = 5,
	LATTICE_TAIL = 6,
	SINGLE_NODE_LATTICE = 7,
	SINGLE_NODE_LINE    = 8,
	SINGLE_NODE_UNIT    = 9
};
//---------------------------------------------------------------------------
class LatticeNode;  // 先に宣言しとかないとViterbiFlagで参照できない
//---------------------------------------------------------------------------
class ViterbiFlag
{
public:
	LatticeNode *Path;
	int         Index;
	double      Probability;

	ViterbiFlag()
	{
		Path = NULL;
		Index = 0;
		Probability = -99999;
	}

	ViterbiFlag &operator=(const ViterbiFlag &flag)
	{
		Index = flag.Index;
		Probability = flag.Probability;
		Path = flag.Path;
		
		return *this;
	}
};
//---------------------------------------------------------------------------
class Candidate
{
public:
	Candidate 		**CandidateP;
	int		  	*SelectedIndex;
	double	  		*Probability;
	//int				*NodeNum;
	int 			*MaxPath;
	int			MaxPathNum;
	int       		Num;
	unsigned short  Code;
	LatticeNode 	*Node;
	int 		Index;

	Candidate()
	{
		Num = 0;
		MaxPathNum = 0;
	}
	~Candidate()
	{
		if(Num != 0)
		{
			delete []CandidateP;
			delete []SelectedIndex;
			delete []Probability;
			//delete []NodeNum;
			delete []MaxPath;
		}
	}
	Candidate &operator=(const Candidate &c)
	{
		MaxPathNum = c.MaxPathNum;
		int Num = Num;
		Code = c.Code;
		Index = c.Index;
		Node = c.Node;
		
		return *this;
	}
	void Free(void)
	{
		if(Num != 0)
		{
			delete []CandidateP;
			delete []SelectedIndex;
			delete []Probability;
			delete []MaxPath;
			//delete []NodeNum;
			MaxPathNum = 0;
		}
	}
};
//---------------------------------------------------------------------------
class LatticeNode
{
private:

public:
	// 対象の文字文字パターン
	int             Start;        // 文字パターンの先頭ストローク
	int             End;          // 文字パターンの終端ストローク　
	int 			BaseNum;

	// 認識結果
	char            Result[CANDIDATE_COUNT * 2 + 2 + 1];
	// 認識候補*10個+確定文字+'\0'
	double          NoStructScore[CANDIDATE_COUNT + 1];
	double          Score[CANDIDATE_COUNT + 1];
	unsigned short  Code[CANDIDATE_COUNT + 1];
	int				Num;
	Candidate       candidate[CANDIDATE_COUNT];
	//double			EachScore[4 * CANDIDATE_COUNT];

	// 字形情報
	// 05/05/31追加
	PAT_POS         BoundingBox;  // 外接矩形
	PAT_POS         WritingBox;   // 推定入力枠
	double          AverageSize;  // 属する行の平均文字サイズ
	//        (推定方法は仕様書を参考)
	bool			IsCheckScore;
	double			SegmentProbability;
	double			NoSegmentProbability;
	//bool			IsTrue;
	int			CenterHigh;

	// ノードの位置
	NodePosition    Position;
	bool            Enabled;
	bool            IsLatticeHead;
	bool            IsLineHead;
	bool            IsBlockHead;
	bool            IsBlockTail;
	bool            IsLineTail;
	bool            IsLatticeTail;

	// ノード間のパス
	LatticeNode     **Prev;       // 前方のリンク
	int             PrevCount;
	// Wang: not used
	LatticeNode     **Next;       // 後方のリンク
	int             NextCount;

	// DPマッチング用フラグ     // 名前分かりにくい。そのうち変える
	int             Tag;          // DPマッチング用

	ViterbiFlag     Flag[CANDIDATE_COUNT + 1];

	int             SelectedIndex;
	// 認識候補が確定した場合のフラグ
	char            FixedCode[3];
	bool            IsFixed;

	// 入出力関数
	istream&    Read(istream &in);
	ostream&    Write(ostream &out);

	friend ostream  &operator<<(ostream &stream, LatticeNode &latticeNode);
	LatticeNode         &operator=(const LatticeNode &latticeNode);

	LatticeNode(const LatticeNode &latticeNode);
	LatticeNode();
	~LatticeNode();

	//19 WANG
	bool IsSearch;
};
#endif
