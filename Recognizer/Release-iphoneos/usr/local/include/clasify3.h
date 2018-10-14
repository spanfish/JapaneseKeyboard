/*=============================================================

			大分類ライブラリ システムヘッダファイル

by 本間 昭次
	1994.??.??	fujidata.h オンライン的手法
	1994.10. 4～classify.h オフライン的手法
	1994.11.15～ndata.h オンライン的手法
	1995. 1.13～choclas.h 二手法合体
	1995. 1.16	これまでのヘッダファイルを合体
	1995. 5.19	リスト構造の辞書を追加
	1995. 6.10	Ver 1.0 (comclas.h)
	1995.10.16	Ver 1.1 comclas.h から分離(classify.h)
	1995.10.16	Ver 1.11 辞書統一
	1996. 6. 4	Ver 1.12 方向特徴8方向に対応
	1996. 7. 7	Ver 1.13 いらない構造体などを削除
by Katsuhiko Akiyama
	1998/ 1		いろいろ直した

=============================================================
=============================================================================
履歴
07/07/30        DFVDATAのdvのサイズを大きくした．by朱
=============================================================================
*/

#ifndef __classify_h__

#define __classify_h__

#include "crlib.h"

//#define homma
//#define homma_err_check							// デバッグ用エラーチェック
#define bunkatsu4x4  							// 分割数 4x4 (defaultは 8x8)
#define non_binarized							// 2値化でない (defaultは2値化)
#define dfv8direction							// 8方向使う

// 距離の最大値(int)
#define NDISTANCE_MAX			0x7fff
// 距離の最大値(long)
#define LDISTANCE_MAX			0x7fffffffL

// マスの標準サイズ
#define BOX_SIZE				128
#define BOX_SIZE_CLSS			(DIVISION_NUM * (1 << LOG_DIV_SIZE))
// マスの標準サイズ(大分類)分割数8x8->128, 4x4->64
// 画数の最大値 - 1
#define ST_MAX					30

// 特徴点抽出時閾値
#define DefMaxArc				7

// スト長閾値のゆるめ
//#define LEN_LOOSENESS			8
#define LEN_LOOSENESS			50
// 変動回数閾値のゆるめ
//#define TURN_LOOSENESS			2
#define TURN_LOOSENESS			5
// 画数閾値のゆるめ
#define K_LOOSENESS				1
// スト長を学習するときの幅
#define STUDY_WIDTH				2

/*
----------------------------------------------------------------------------
LEN_STUDY_WIDTH は次のような式で使用される。
len_study_width = (len_max - len_min) >> LEN_STUDY_WIDTH; ......(1)
ここで、変数 len_study_width はストローク長を学習するときに持たせる幅である。
ストローク長の学習では、学習したい文字のストローク長よりも少し余裕を持たせて
学習する。
len_max と len_min は、辞書のストローク長の範囲である。
だから、上の式は、辞書のストローク長の範囲を LEN_STUDY_WIDTH = 3 だけ
右にシフトすること、つまり 8 で割ることを意味する。
まとめ
ストローク長の学習では、辞書のストローク長の範囲を 8 で割った幅だけ
余裕を持たせて学習する。
----------------------------------------------------------------------------
*/

/*
----------------------------------------------------------------------------
用語説明
セル...最小分割単位
小領域...セル四つからなる単位
----------------------------------------------------------------------------
*/

#ifdef dfv8direction
	// 8方向
	#define DIRECTION_NUM		8
#else
	// 4方向
	#define DIRECTION_NUM		4
#endif

// 分割数を変えたい場合、この辺を変更する
#ifndef bunkatsu4x4
	// 分割数 8×8 の場合
	#define DIVISION_NUM		8
#else
	// 分割数 4×4 の場合
	#define DIVISION_NUM		4
#endif

// セル幅のビット数
#define LOG_DIV_SIZE		4
// 前は、8x8のときはLOG_DIV_SIZEを3にしていた。
#define CELL_NUM			(DIVISION_NUM - 1)
// 小領域の数
#define CLSS_VCTR_DIM		(CELL_NUM * CELL_NUM)
// 方向特徴次元数
#define CLSS_DFDATA_DIM		(CLSS_VCTR_DIM * DIRECTION_NUM)
// 2値化したときのバイト数
#define CLSS_DF2_DIM		((CLSS_DFDATA_DIM + 7) >> 3)

// 方向特徴ベクトル次元数
#ifdef non_binarized
	#define CLSS_DFV_DIM		CLSS_DFDATA_DIM
#else
	// 次元数（2値化した場合）
	#define CLSS_DFV_DIM		CLSS_DF2_DIM
#endif

// 重みの枠の幅のビット数
#define LOG_WEIGHT_SIZE		(LOG_DIV_SIZE - WEIGHT_GRAD_BIT)
// 重みの段階数のビット幅
#define WEIGHT_GRAD_BIT		2
// 重みの段階数
#define WEIGHT_NUM			(1 << WEIGHT_GRAD_BIT)
// 重みのマスク
#define WEIGHT_MASK			(WEIGHT_NUM - 1)

// 続け字に対応した距離のウェイト
#define DISTANCE_WEIGHT		1
// 2値化閾値(新規辞書作成の場合)
#define NICHITHRESHOLD		49

// 2の平方根
#define ROOT2				1.41421356
// 2の平方根の2分の1
#define ROOT2SEC			(ROOT2 / 2)
// 2の平方根/2*(2^(GETA_UP=7)))
#define ROOT2x64			90
// cos を整数にするために下駄をはかせる
#define GETA_UP				7

// 下駄についての注意
// 分割数が 4x4 の場合、各数値が大きくなってしまうので、
// はかせた下駄より一つ余分に下駄をはずす。
#define GETA_DOWN			(GETA_UP + 1)

#define FEATURE			8		// 特徴点

// 大分類学習で、何を学習したかのフラグ
#define STUDY_ERR		-1		// エラー
#define STUDY_K_MAX		1		// 画数の最大値
#define STUDY_YLEN_MIN	2		// Y方向のスト長の最小値
#define STUDY_OTHER		4		// その他のオンライン特徴
#define STUDY_DFV		8		// 方向特徴ベクトル
#define STUDY_NEW		\
		(16 | STUDY_K_MAX | STUDY_YLEN_MIN | STUDY_OTHER | STUDY_DFV)
								// 新規文字学習

#define STUDY_ON				1
#define STUDY_OFF				0

// 裏ストロークの扱い
#define SW_NOBACK	1
#define SW_BACK		2
// 方向特徴抽出方法
#define SW_COS		1
#define SW_SQRCOS	2
#define SW_THRESH	3
// 距離計算方法
#define SW_EUCLID		1
#define SW_CITYBLOCK	2
// 距離計算でint,long選択
#define SW_INT		1
#define SW_LONG		2

typedef union{		// 日本語文字型（char の日本語版）
	WORD w;								/* 2 バイト（1 ワード） */
	struct{
		BYTE low;						/* 下位バイト */
		BYTE high;						/* 上位バイト */
	} b;
} jchar;

typedef struct {	// 候補
	long distance;
	jchar jiscode;
	WORD dummy;
} CANDIDATE;

// 候補文字列とその得点
typedef struct {
	CANDIDATE *candidate;
	// 候補数
	int num;
} DFVCAND;

typedef struct {	// 入力パタンのストロークに関する情報
	int stnum;					// 画数
	int xlen;					// X 方向ストローク長(city block 距離)
	int ylen;					// Y 方向ストローク長
	int xturn;					// X 方向増減回数
	int yturn;					// Y 方向増減回数
} STDATA;

// 8方向	0:右, 1:右上, 2:上, 3:左上, 4:左, 5:左下, 6:下, 7:右下
// 4方向	0:垂直, 1:右上がり, 2:水平, 3:右下がり
typedef struct{
	unsigned int direct[DIRECTION_NUM];
} DIRECT;

// 8方向の場合は，4方向から動的に割り当てる．
// 8方向	0:右, 1:右上, 2:上, 3:左上, 4:左, 5:左下, 6:下, 7:右下
typedef struct{
	unsigned int amount[4];
	int d[4];
} DIRECT8;

// ベクトルを方向ごとか配列で表わす
typedef union{
	unsigned v[CLSS_DFDATA_DIM];
	DIRECT dv[CLSS_VCTR_DIM + 10];
} DFVDATA;

// 方向特徴ベクトル
typedef struct{
	BYTE v[CLSS_DFV_DIM];
} DFV;

// ストローク情報と方向成分を合わせた構造体
typedef struct {
	STDATA stdata;
	DFV dfv;
} UDATA;

// ============================= 辞書構造 ============================
// 辞書の画数、スト長、方向変動回数の部分
typedef struct{
	// 画数
	BYTE k_max;
	// ストローク長
	BYTE xlen_max;
	BYTE xlen_min;
	BYTE ylen_max;
	BYTE ylen_min;
	// 変動回数
	BYTE xturn_max;
	BYTE xturn_min;
	BYTE yturn_max;
	BYTE yturn_min;
} ONLINE_CC_DIC;

// 辞書の方向特徴部
typedef struct{
	DFV dfv;
} OFFLINE_CC_DIC;

typedef struct tagUNION_CC_DIC{
	// オフライン特徴
	OFFLINE_CC_DIC *offcd;
	// オンライン特徴
	ONLINE_CC_DIC oncd;
	// リンク
	struct tagUNION_CC_DIC *previous, *next;
	// 文字コード
	jchar jiscode;
	// オフライン特徴の数
	BYTE offcd_num;
} UNION_CC_DIC;

#endif