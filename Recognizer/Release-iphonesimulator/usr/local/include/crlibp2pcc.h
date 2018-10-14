// Crlibp2pに大分類を加えてみよう！バージョン

#ifndef __CRLIBP2PCC_H__

#define __CRLIBP2PCC_H__

#define USE_CC//大分類使用時は定義せよ

#ifdef USE_CC

//#include "ctclass.h"//ak.大分類用に追加
#include "comclas3.h"//ak.大分類用に追加
#include "crlibex.h"
#endif

#ifdef __BORLANDC__
#define EXPVAR __pascal

#else
#define EXPVAR

#endif
//20150323ADD
#define __stdcall

//字種識別用
#define RK_Hiragana 1
#define RK_Katakana 2
#define RK_Alphabet 4
#define RK_Jis1Kanji 8
#define RK_Jis2Kanji 16
#define RK_Numeric 32	//ak@数字
#define RK_Symbol 64	//ak@記号
#define RK_Greek 128
#define RK_Punctuation 256	//ak@句読点

#define RK_AllCategory (RK_Hiragana \
			| RK_Katakana \
			| RK_Alphabet \
			| RK_Jis1Kanji \
			| RK_Jis2Kanji \
			| RK_Numeric \
			| RK_Symbol \
			| RK_Greek \
			| RK_Punctuation \
			)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef USE_CC
/*参考までに from ComClass3.h
typedef struct{
	SHORT *linktbl;
	SHORT *hashtbl;
} CANDTBL;		*/

//大分類用構造体
typedef struct{
	WORD *code;
	int count;
	CANDTBL ct;
	int rank;
	int mflag;
} CCINFO;
#endif //#ifdef USE_CC

//静的な宣言を外部に公開する場合は以下の様に行う
//extern __declspec(dllexport) int EXPVAR VAR;

/////////////////////////認識基本関数群//////////////////////////////

//認識システムの初期化
int __stdcall D_OpenOnCrRecSystem(const char dic_file[]);
//ファイルのクローズ
void __stdcall D_CloseOnCrRecSystem();
//文字認識実行
int __stdcall D_OnCrRecognize(
											PATTERN_W *in, CR_RESULT res[], int res_count);
//大分類実行
int __stdcall D_CoarseClassify(PATTERN_W *pat, WORD *cands, long *dist, int num);
//文字パタンが入力された際の矩形をシステムに教える
void __stdcall D_SetGuideBoxRect(PAT_POS *pos);

#ifdef USE_CC
//大分類を使用する場合に利用する伸縮マッチングを設定
int __stdcall D_SetMatchMode_CC(int m_alg);
#endif
//大分類を使用しない場合に利用する伸縮マッチングを設定
int __stdcall D_SetMatchMode_NCC(int m_alg);
//伸縮マッチングを設定
int __stdcall D_SetMatchMode(int m_alg);

//文字コードを持たないパタンを認識対象にする(外す)関数(flag == 1で対象，== 0で対象外)
void __stdcall D_SetSupportNonCodePat(int flag);
//文字コードを持たないパタンが認識対象にあるかを調べる(==1 で対象，== 0で対象外)
int __stdcall D_IsSupportNonCodePat();
/////////////////////認識フィルタ系関数群//////////////////////////

//フィルタ関数をセットする(新しい版)
void __stdcall D_SetCRPassFilter_CrecStat(
									int (*proc)(unsigned code, void *param), void *param);
//現在設定されているフィルタ関数を取得する
void __stdcall D_GetCRPassFilter(CRFILTER *crflt);
//正解候補フィルタ用のカテゴリクラスを選択する
void __stdcall D_SetFiltCodeClass(int filter);
//文字コード範囲で指定するフィルタ関数のセット
void __stdcall D_SetFiltCodeRange();
//文字コード範囲で指定するフィルタ関数への範囲の追加
int __stdcall D_AddFilterCodeRange(unsigned start, unsigned end);
//文字コード範囲で指定するフィルタ関数にコードを１つだけ追加
int __stdcall D_AddFilterCodeRangeSingle(unsigned code);
//文字コード範囲で指定するフィルタ関数にセットした範囲のクリア
void __stdcall D_ClearFilerCodeRange();
//文字コード範囲リストの長さを取得
int __stdcall D_GetFilterCodeRangeListNum();
//長さを指定して文字コード範囲リストを取得
int __stdcall D_GetFilterCodeRangeList(
											unsigned start[], unsigned end[], int num);
//フルオートで文字コード範囲フィルタを取得
int __stdcall D_GetFilterCodeRangeListEX(unsigned **start, unsigned **end);
//D_GetFilterCoderangeListEX()で確保したメモリ領域を開放
void __stdcall D_FreeFilterCodeRangeListEX(unsigned **start, unsigned **end);

//字種フィルタをクリア
void __stdcall D_ClearCodeFilter();

///////////////////////大分類系関数/////////////////////////////

#ifdef USE_CC
//大分類初期化
int __stdcall D_OpenCoarseClassification(const char dic_file[]);
//大分類終了
void __stdcall D_CloseCoarseClassification();
//大分類候補数変更
int __stdcall D_ChangeCandNumCC(unsigned cand_num);
#endif //#ifdef USE_CC

///////////////////////雑用系関数/////////////////////////////

//2byte文字判定関数
int __stdcall D_IsLeadByte(unsigned char c);
//内部コードをSJISコードに変換
void __stdcall D_Jctos(unsigned code, char s[]);
//SJISコード(文字列型)をWORD型に変換
unsigned __stdcall D_MakeCrlibCode(const char s[], unsigned *c);
//SJISコード(文字列型)をWORD型に変換(CString->c_str():unsigned char?対応)
unsigned __stdcall  D_MakeCrlibCodeUS(unsigned char c1, unsigned char c2);

#ifdef __cplusplus
	};
#endif

#endif //#ifndef __CRLIBP2PCC_H__
