/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      LatticeManager.h
クラス名        LatticeManager
                LatticeDocument
                LatticePage
                LatticeBlock
                LatticeNode
解説            Latticeデータ管理クラス
                Latticeデータクラス
担当者          朱碧蘭

=============================================================================
履歴
05/05/08        作成
05/05/31        LatticeNodeクラスにBoundingBox変数，WritingBox変数,
                AverageSize変数を追加
                LaticeDocumentクラス以下をLatticeDocument.hファイルに分離
                Latticeデータクラス群をLatticeDocument.hに分離
05/06/10        次のメンバを追加
                    SegmentLineクラス，CharacterStructureクラス
                    LineStructureクラス，CharacterRecognizerクラス
                    segment関数，CreateLattice関数，CreateBlock関数
05/06/23        次のメンバを追加
                    IsLatticeHead変数，IsLineHead変数, IsBlockHead変数
                    IsLatticeTail変数，IsLineTail変数, IsBlockTail変数
                CreateLink関数を前方リンクも生成するように改良
05/06/24        分割情報を生成する位置を変更
05/06/25        CreateLink関数のバグを修正
05/09/11        InkManagerパッケージの変更に伴う修正
05/09/26        LatticeDocumentクラスを削除
                ArrayList<LatticePage>クラスを追加
                CreateLink関数をLatticePageクラスへ移動
05/09/28        Create関数,SetPositionっ関数をLatticePageクラスへ移動
07/11/20        認識処理の重み変数qを追加　
				myLineStructを削除 by 朱
07/11/26		rotatedInk処理を削除(訂正インタフェースはしばらくやらない)
07/11/27		SetWaitWithBounds関数, SetWaitWithoutBounds関数を追加
08/06/08        認識処理の重み変数qを2時限に変更
08/06/08  　　  担当者は織田から朱へ変更
=============================================================================
*/
#ifndef __LATTICEMANAGER_H_
#define __LATTICEMANAGER_H_

#include "LatticePage.h"
#include "InkManager.h"
#include "SegmentLine.h"
#include "CharacterStructure.h"
#include "CombinationRecognizer.h"

#include "ArrayList.h"


//const int CANDIDATE_COUNT = 10;
const int FrameRatio = 2;          // 外接矩形の縦横比 1:FrameRatio
//---------------------------------------------------------------------------
class LatticeManager
{
	private:
		// 機能クラス
		SegmentLine         *mySegment;
		short				topLine;
		short				baseLine;
		bool				isSetGuideLines;

		//InkManager          *rotatedInk;

		// ラティス生成関数
		void createPage(LatticePage *latticePage, InkPage *inkPage);
		void getRecognitionCandidate(LatticePage *latticePage,
															InkPage *inkPage);
		unsigned short getCode(char *code);
		bool stored(PAT_POS bounds, InkStroke *stroke, int count);

	public:
		bool                isEmpty;
		bool				isHasDic;
		InkManager          *Ink;
		CharacterStructure  *myCharStruct;
		double	q[6][2], q1[6][2], q2[6][2];
		//TProgressBar 		*ProgressBar;
		//double 				ScoreThre;
		//int 	CorrectScore[1000];
		//int 	MisScore[1000];
		bool IsCheck;

		void		SetQ(double q[6][2]);
		void 		SetWaitWithBounds(double q[6][2]);
		void 		SetWaitWithoutBounds(double q[6][2]);
		void		SetOneLineRecognition(bool isOneLine);
		void		SetGuideLines(short topLine, short	baseLine);
		void SetHeavySegmentation(bool isHeavySegmentation);
		
		void OneCharacterRecognize(InkStroke *pStroke, int count, 
										    PAT_POS &writtingBox, PAT_POS &bound, char *candidate, 
										  unsigned short *code, double *score);

		//CharacterRecognizerAdapter *Recognizer;
		CombinationRecognizer *Recognizer;
		ArrayList<LatticePage> Page;

		// ラティス生成・消去関数
		void        Create();
		void        Clear();
		bool        IsEmpty();

		// ファイル入出力関数
		bool        ExportToFile(const char *fileName, const int index);
		bool        SaveToFile(const char *fileName);
		bool        LoadFromFile(const char *fileName);
		bool		AddFromFile(const char *fileName);

		// 訂正インタフェース用関数
		void        SelectNode(int page, int start, int end);
		void        SetAngle(int page, int start, int end, double angle);
		void        SetCode(int page, int start, int end, char *code);
		void        ReplaceStroke(int page, int start, int end,
												InkStroke *stroke, int count);

		void        RecreateLatticePage(int page);

		void 		Create(int index);

		void		UpdateLatticeResult(int index, const LatticeNode *result, int nResult);

		LatticeManager();
		LatticeManager(InkManager *ink);
		~LatticeManager();
};
//---------------------------------------------------------------------------
#endif


