/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      SrResult.h
クラス名
解説
担当者          小沼 元輝

=============================================================================
履歴
05/06/14        作成
                担当者を小沼から織田に変更
                GetRotateDataクラスを元に作成
05/06/20        機能追加
05/06/20a       コンストラクタの呼び出し失敗を変更
05/09/26        InkManagerパッケージの仕様変更に伴う変更 by 織田
=============================================================================
*/
#ifndef SrResultH
#define SrResultH

#include "InkManager.h"
#include "LatticeManager.h"
#include <vector>

using namespace std;
//---------------------------------------------------------------------------
/* 一文字が持つ結果 */
typedef struct tagSR_ONECHAR
{
    BYTE Code[3];	//Word = Code[0]*0x100 + Code[1]; //Code[2] = '\0';
} SR_ONECHAR, *PSR_ONECHAR;
//---------------------------------------------------------------------------
typedef struct tagSR_CHARINFO
{
	LONG    lID;            //----- 文字識別ID
	BYTE    pCode[3];       //----- 文字コード
	PSR_ONECHAR pCands;     //----- 文字候補
	LONG*   pCompStrokes;   //----- 文字に含まれるストローク番号の集合
	LONG    lStrokeCount;   //----- 文字に含まれるストローク数
	LONG    lSkew;          //----- 文字傾斜角度
	LONG    lDir;           //----- 行方向
	POINT   ptBound[4];     //----- 外接矩形
	POINT   ptSizChar;      //----- サイズ
	POINT   ptCenter;       //----- 中心点
} SR_CHARINFO, *PSR_CHARINFO;
//---------------------------------------------------------------------------
/* 結果行情報 */
typedef struct tagSR_LINE
{
	LONG    lID;
	LONG*   lCharID;
	LONG    lSkew;          //----- 文字傾斜角度
	LONG    lDir;           //----- 行方向
	POINT   ptAveSiz;       //----- 平均サイズ
} SR_LINE, *PSR_LINE;
//---------------------------------------------------------------------------
/* 結果文字列 */
typedef struct tagSR_RESULT
{
	LONG            lCharCount;
	BYTE*           pText;
	PSR_CHARINFO*   pChar;
	PSR_LINE*       pLine;
} SR_RESULT, *PSR_RESULT;

//---------------------------------------------------------------------------
class SrResult
{
    protected:
    private:
        InkManager  *myInk;
        POINT       Bound[4];
        POINT       SizChar;
        POINT       Center;
        SR_RESULT   result;
        long        pCharCount;
        long        pCharAddCount;
        long        pCharIndex;
        long        Direct;

        // 適当に書いたので一応確認してください
        PSR_CHARINFO getSR_CHARINFO(LatticeNode *node, int index);

        void InputStroke(InkStroke *inkStroke, int inkStrCount, LONG lSkew);
        void GetRotationBoundingBox(POINT ptBound[4], POINT *ptSizChar, POINT *ptCenter, long *Dir);
        void deleteSR_CHARINFO(SR_CHARINFO *charInfo);

        long CandidateSize;
        void Create(InkManager *ink);
    public:

        void Clear();
        void CreateSrResult();
        void AddCharInfo(LatticeNode *node, int index);
        SR_RESULT* GetResult();
        void SetInk(InkManager *ink);
        SrResult(InkManager *ink);
        SrResult();
        ~SrResult();
};
//IDを定義する：
//    今回認識時の入力順にしてある
//    内部での区別にしか使っていない(早い話ハンドル)
//    オブジェクトのポインタにする事も可能

#endif