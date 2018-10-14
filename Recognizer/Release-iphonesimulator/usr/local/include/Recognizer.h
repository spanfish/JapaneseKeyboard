/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      Recognizer.h
クラス名        Recognizer
解説            文字列認識クラス
担当者          朱碧蘭

=============================================================================
履歴
05/05/08        作成
05/05/08        作成
05/06/13        OutGapクラス, Contextクラスを追加
05/06/20        SrResultクラスを追加
05/06/25        Back関数を修正
05/11/07        searchNode関数においてLINE_HEADの確率を追加 by 朱
07/05/02		ファイル保存位置変更関数(SupplyPath.h)に対応 by 織田，寺田
07/07/20        担当者を織田から朱に変更
07/07/30		Trigramの処理を追加
07/08/17        行の間も文脈処理を行うように変更
07/09/14        GetResult関数のメモリ確保変更
07/11/20        文字列スコアの計算に隣接する文字パタン間の位置情報の確率を入れるため，
				BinaryFeatureを追加
07/11/27		SetWaitWithBounds関数, SetWaitWithoutBounds関数を追加
08/06/08        認識処理の重み変数qを2時限に変更
09/06/27		SetContextDictionaryを追加
=============================================================================
*/

#ifndef RecognizerH
#define RecognizerH

#include "ViterbiSolver.h"
#include "Context.h"
#include "BinaryFeature.h"
#include "SrResult.h"
#include "ArrayList.h"
#include <map>
using namespace std;

//---------------------------------------------------------------------------
const int SEARCH_COUNT = 1;
//---------------------------------------------------------------------------
class Recognizer : public ViterbiSolver
{
	private :
		SrResult    	   *mySrResult;
		double 		threshhold;
		double 		highestScore;

		// 抽象関数の定義
		void        searchNode(LatticeNode *node);
		void        back(LatticeNode *node);
		double      getProbability(LatticeNode *prevNode, int prevIndex,
								LatticeNode *currentNode, int currentIndex);
		char        *Result;
		void		recogAll(LatticeNode *current, LatticeNode *prev, int prevIndex,
						double score, string result, multimap<double, string> &m);

		void searchTrigramNode(LatticeNode *node);
		void searchTrigramNodeOne(LatticeNode *node);
		void backTrigram(LatticeNode *node);
		int searchPosition(double *highestScore, double score, int *check, int count);

		ArrayList<LatticeNode> result;
		ArrayList<unsigned short> codeResult;
		vector<char> myContextFileName;

	public :
		Context     *myContext;
		Context     *myOriginalContext;
		BinaryFeature      *myBinaryFeature;
		ArrayList<LatticeNode*> Node;
		bool 		IsEmpty;

		void        Recognize();
		void        RecognizeAll(const int index);
		void        Recognize(const int index);
		char        *GetResult();
		const LatticeNode *GetResultNode();
		int         GetResultNodeCount();
		SR_RESULT*  GetSrResult();

		void 		SetWaitWithBounds(double q[3][2]);
		void 		SetWaitWithoutBounds(double q[3][2]);
		void        SetContextDictionary(char *fileName);

		double		q[3][2], q1[3][2], q2[3][2];
		//double		TriThre;

        Recognizer();
        Recognizer(InkManager *ink, LatticeManager *lattice);
		void SetRecognitionCode(const char *str);
		void WriteDictionary(const char dicPathName[]);

        ~Recognizer();
};
//---------------------------------------------------------------------------
#endif
