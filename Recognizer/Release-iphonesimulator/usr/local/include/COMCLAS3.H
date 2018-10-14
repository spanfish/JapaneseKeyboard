/*
=============================================================================

					大分類ライブラリヘッダファイル

													version 3.00

											Copyright Katsuhiko Akiyama

=============================================================================
*/
/****************************************************************************
○大分類ライブラリの使用方法

１．大分類システムの初期化
まず，InitCoarseClassification()で大分類を初期化および辞書の読み込みをする．

２．大分類を行う（候補リストを得る）
大分類を行うには，まず候補リストを受け取るバッファを用意する．そして，
入力パターンとバッファとバッファのサイズ（個数）を指定して，
CoarseClassify()を呼出す．バッファに候補リストが返され，戻り値に
候補の数が返される．

３．候補リストを検索する
候補リストの中に，ある文字が含まれているかどうかを判定することで，
詳細分類処理の有無が決定できる．しかし，候補リストのままでは検索に
処理時間が掛かってしまう．
高速な検索を行うためには，まず候補検索表構造体と候補リスト，候補数を
渡してInitCandSearchTable() を呼び出し，候補検索表の初期化を行う．
次に，初期化した候補検索表と候補リスト，検索文字コードを渡して
IsCandidate() を呼び出し，その戻り値を調べる．戻り値は 0 から始まる
候補順位を返し，候補外なら負の値を返す．大分類の対象外文字かどうか
を調べるには，InClassDic() に検索文字コードを渡し，戻り値を調べる．
この検索表は必ず使わなければいけないわけではないので，自前で検索処理
を作成しても良い．
初期化した候補検索表は，使用後にFreeCandSearchTable()で廃棄する．

４．辞書学習
ある手書き文字パタンを大分類辞書に登録したい場合はStudyCoarseClassification()
に文字パタンとその文字コード，候補数閾値を渡して学習する．そのパタンが候補の
上位(候補数閾値以内)に入る場合は学習しない．
終了する前に学習した結果を大分類辞書に保存したい場合は
SaveCoarseClassificationDic()を使う．

５．システムの終了
最後にReleaseCoarseClassification()で大分類の辞書および関連する領域を
メモリから解放する．
*****************************************************************************/

#ifndef __comclas_h__

#define __comclas_h__

#include "crlib.h"

typedef struct{
	SHORT *linktbl;
	SHORT *hashtbl;
} CANDTBL;

// *********************************************************
// 				==== 関数の型宣言始まり ====
// *********************************************************
#ifdef __cplusplus
extern "C" {
#endif

// ========================= 大分類 API =============================
// 大分類システム初期化
// fname = 大分類辞書ファイル名
// 戻り値：成功 = 0, Error != 0
extern int InitCoarseClassification(char *fname);

// 大分類システム終了
extern void ReleaseCoarseClassification(void);

// 辞書ロード、以前の辞書は開放される
// 戻り値：成功 = 0, Error != 0
extern int LoadCoarseClassificationDic(char *fname);

// 大分類辞書保存
// 戻り値：成功 = 0, Error != 0
extern int SaveCoarseClassificationDic(char *fname);

// 大分類処理
// arguments : pat = pattern, kouho = result(code list) buffer,
// 			num = buffer count
// return value : result count, error < 0
// 候補リストは距離値順に格納される、互換性のために用意
extern int CoarseClassification(
		PATTERN_W *pat, unsigned short *kouho, int num);

// 大分類処理
// arguments : pat = pattern, cands = result(code list) buffer,
// 			dist = 距離値を格納するバッファ, num = buffer count
// return value : result count, error < 0
// 候補リストは距離値順に格納される、cands と dist は NULL でも良い
extern int CoarseClassify(PATTERN_W *pat, WORD *cands, long *dist, int num);

// 大分類学習
// 引数：pat = パターン, code = 文字コード, abandnum = この順位以内
// 		に入らない場合学習する
// 戻り値:学習結果に応じて次のビットを立てて返す
// 0	学習しなかった(必要がないので)
// 1	画数最大値				:1
// 2	縦方向ストローク長最小値:2
// 4	その他オンライン特徴	:4
// 8	方向特徴ベクトル		:8
// 16	新規文字学習			:16
// -1	エラー					:-1
extern int StudyCoarseClassification(
		PATTERN_W *pat, unsigned short code, int abandnum);

// ======================= 候補検索表 API ===========================
// 候補検索表を開放する
extern void FreeCandSearchTable(CANDTBL *ct);

// 候補検索表を生成する
// ct = 候補検索表構造体
// cand = 候補リスト、CoarseClassify() の処理結果
// n = 候補数、CoarseClassify() の戻り値
// 戻り値：エラー != 0
extern int InitCandSearchTable(CANDTBL *ct, WORD *cand, int n);

// 候補リストと候補検索表から文字コードを高速に検索する
// ct = 候補検索表、InitCandSearchTable() で初期化したもの
// cand = 候補リスト, code = 検索する文字コード
// 戻り値：候補順位 >= 0，候補外 < 0
extern int IsCandidate(CANDTBL *ct, WORD *cand, WORD code);

// 文字コードが辞書に含まれているかどうかを高速に調べる
// 戻り値：辞書に含まれていれば 0 以外
extern int InClassDic(WORD code);

// ========================== 隠し API ===============================
#if 0

#include "clasify3.h"

// long 型 CityBlock 距離
extern long lDfvCityBlockDistance(DFV *dicdfv, DFV *dfv);

// long 型 Euclid 距離
extern long lDfvEuclidDistance(DFV *dicdfv, DFV *dfv);

// int 型 CityBlock 距離
extern int nDfvCityBlockDistance(DFV *dicdfv, DFV *dfv);

// int 型 Euclid 距離
extern int nDfvEuclidDistance(DFV *dicdfv, DFV *dfv);

// 方向特徴を抽出
extern void DfData(PATTERN_W *ptnw, DFV *dfv);

// 方向特徴抽出(裏ストローク有)
extern void DfDataWithUra(PATTERN_W *ptnw, DFV *dfv);

// 方向特徴抽出(裏ストローク有、cosを二乗)
extern void SquaredDfDataWithUra(PATTERN_W *ptnw, DFV *dfv);

// 方向特徴抽出(裏ストローク有、cosを二乗)
extern void ThresholdDfDataWithUra(PATTERN_W *ptnw, DFV *dfv);

// 方向特徴抽出(8方向，裏スト有，cos^2)
extern void DfData8Direction(PATTERN_W *ptnw, DFV *dfv);

// 方向特徴抽出(8方向，裏スト有，cos)
extern void DfData8DirCos(PATTERN_W *ptnw, DFV *dfv);
#endif

// ====================== 特に使う必要なし ========================
// 斜辺長の表解放
extern void FreeObliqueSide(void);

// 斜辺長の表初期化
extern int InitObliqueSide(int max);

// 斜辺長求める
extern int GetLengthOfObliqueSide(int x, int y);

// バイトの2乗のテーブル初期化
extern int InitSquareByte(void);

// バイトの2乗のテーブル解放
extern void FreeSquareByte(void);

// バイトの2乗の値を返す
extern unsigned int SquareByte(int n);

// ========================= 正規化関連 =============================
// 線形正規化（大きい方に合わせる）
// 引数：inpt = 入力パターン, outpat = 出力パターンを受け取る構造体、
// 		outpatのdataメンバは十分なサイズのバッファを指していなければ
// 		ならない，size = 出力パターンサイズ, sx = 入力パターンの
// 		水平サイズを受け取る．NULL でも良い，sy = 垂直サイズを受け取る
//		NULL でも良い．
extern void LinearNormalize(
		PATTERN_W *inpat, PATTERN_W *outpat, int size, int *sx, int *sy);

// 線形正規化（両方向）
// 引数：inpt = 入力パターン, outpt = 出力パターンを受け取る構造体、
// 		outptのdataメンバは十分なサイズのバッファを指していなければ
// 		ならない，size = 出力パターンサイズ
extern void LinearNormalize2(
		PATTERN_W *inpt, PATTERN_W *outpt, int size);

// パターンのサイズを得る
extern int getpatsize(PATTERN_W *pat);

// 非線形正規化
// 引数：inpt = 入力パターン, outpt = 出力パターンを受け取る構造体、
// 		outptのdataメンバは十分なサイズのバッファを指していなければ
// 		ならない，outsize = 出力パターンサイズ
// 戻り値：エラー != 0
extern int NonLinearNormalize(
		PATTERN_W *inpt, PATTERN_W *outpt, int outsize);

#ifdef __cplusplus
}
#endif

// *********************************************************
// 				==== 関数の型宣言終わり ====
// *********************************************************

#endif // __comclas_h__
