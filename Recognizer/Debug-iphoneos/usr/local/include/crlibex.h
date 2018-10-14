/*
============================================================================

				crlib extension library header file

													Copyrighted by K.A

============================================================================
*/

#ifndef __CRLIBEX_H__

#define __CRLIBEX_H__

#include "crlib.h"

// 特徴点属性
#define CA_DivideChar			1
#define CA_ReverseOrder			2
#define CA_KeepRatio			4
#define CA_ComparePos			8
#define CA_SmallChar			0x80

// パターン属性
#define CPA_LearnedPattern		0x40

// 認識モード
enum{ CR_WithCodeCategory = 0, CR_AllCategory, CR_UseFilter };

// 辞書カテゴリテーブルサイズ
enum{ CR_MaxCategoryTableSize = 15000 };

// 認識候補フィルタ返り値
enum{
	CR_UseLtm = 1, CR_Reject = 0, CR_UseLtmAndDpm = -1, CR_UseDpm = -2
};

// 構造体定義
typedef struct{
	PATTERN_B *pat;
	SHORT count;
} PATDIC;

struct tagCATEGORY;

typedef struct{
	int ctg_no;
	int x, y;
	int sx, sy;
} SUBCTG;

typedef struct{
	unsigned code;
	unsigned status;
	int sx, sy;
	SUBCTG subctg[2];
} CTGINFO;

typedef struct{
	PAT_POS pos;
	int ctg_no, pat_size;
	PATTERN_B inpd;
PATTERN_B inpd2;
PAT_POS pp;
	void *tmp_dic_data;
	void *npt_pair;
	void *table;
	void *reslink;
	CR_RESULT *res_buf;
	int res_count;
} CRSTATE;

typedef struct{
	int (*proc)(unsigned code, void *param);
	void *param;
} CRFILTER;

struct tagCATEGORY;

// 分割情報
typedef struct{
	struct tagCATEGORY *part;
	BYTE pos, size;
} DIVINFO;

// カテゴリ情報
typedef struct tagCATEGORY{
	SHORT ctg_no;
	WORD code;
	BYTE status, size;
	DIVINFO div[2];
	PATDIC patdic;
} CATEGORY;

typedef struct{
	CATEGORY **ctg;
	int count;
	int maxctgtblsize;
	int maxpointcount;
} CRDIC;

typedef struct{
	int ctg_no;
	int pt_no;
	int pt_count;
} CRLEARNINFO;

typedef struct{
	int div_min_score;
} CRLEARNCFG;

#ifdef __cplusplus
extern "C" {
#endif

void GetCRLearnConfig(CRLEARNCFG *lc);
void SetCRLearnConfig(CRLEARNCFG *lc);
extern CRDIC _crdic;
// 入力パターン pat を ctg_no に学習
int LearnCRDictionary(PATTERN_W *pat, int ctg_no, CRLEARNINFO *li);
// 学習すべき部分の情報を取得
int GetCRLearnPart(PATTERN_W *pat, int ctg_no, CRLEARNINFO *li);
// 部分パターンを登録する
int RegistCRLearnPart(PATTERN_W *pat, CRLEARNINFO *li);

// 任意の辞書パターンとの類似度を得る
int GetPatternScore(PATTERN_W *pat, int ctg_no);

// 認識システムを使用できるようにする
int OpenCRSystem(const char dic_file[]);
// 認識システムを開放する
void CloseCRSystem(void);

// 認識を行う
int RecognizeCP(PATTERN_W *in, CR_RESULT res[], int res_count);
// バックグラウンド認識の初期化関数
int InitBGRecognize(CRSTATE *crs,
		PATTERN_W *pat, CR_RESULT *res_buf, int res_count);
// バックグラウンド認識 (続きがあれば 0 以外)
int BGRecognizeCP(CRSTATE *crs, int match_count);

int RecognizeCPNew(PATTERN_W *id, int *score);
void BGRecognizeCPNew(CRSTATE *crs, int *score);
void SetFirstCandidate(short *candidate, int count);

// バックグラウンド認識の終了関数
void CloseBGRecognize(CRSTATE *crs);
// マッチングの途中結果を再利用して認識を行う。現在使用不可
//int RecognizeCP2(PATTERN_W *in, CR_RESULT res[], int res_count);
// トライ辞書を用いた認識を行う。現在使用不可
// int TriRecognizeCP(PATTERN_W *in, CR_RESULT res[], int res_count);

// シフト JIS コードに対応するカテゴリ番号を得る
int GetCategoryNo(unsigned code, int start_ctg_no);

// カテゴリの非分割パターンを得る
int GetCategoryPattern(PATTERN_B *pat, int ctg_no, int pat_no);
// カテゴリの非分割パターンを設定する
int SetCategoryPattern(PATTERN_B *pat, int ctg_no, int pat_no);
// カテゴリの非分割パターンを追加する
int AddCategoryPattern(PATTERN_B *pat, int ctg_no, int pat_no);
// カテゴリの非分割パターンを削除する
int DeleteCategoryPattern(int ctg_no, int pat_no);
// カテゴリの非分割パターン数を得る
int GetCategoryPatternCount(int ctg_no);

// カテゴリのパターンを得る
int GetCharacterPatterns(PATDIC *pd, int ctg_no, int is_all);
// カテゴリのパターン数を得る
int GetCharacterPatternCount(int ctg_no);

// PATTERN_B 型のメンバ配列を開放する
void FreePatternB(PATTERN_B *pat);
// パターン配列を開放する
void FreePatDic(PATDIC *pd);

// ctg1 が ctg2 を構造に含むかどうか判定する
int IsIncludedCategory(int ctg1, int ctg2);
// カテゴリ情報を得る
int GetCategoryInfo(CTGINFO *ctg, int ctg_no);
// カテゴリ情報をセットする
int SetCategoryInfo(CTGINFO *ctg, int ctg_no);
// 辞書カテゴリテーブルのサイズを得る
int GetCategoryCount(void);
// 辞書カテゴリテーブルのサイズを設定する
int SetCategoryCount(int count);

// 辞書カテゴリを追加する
int AddCategories(int ctg_no, int count);
// 辞書カテゴリを削除する
int DeleteCategories(int ctg_no, int count);

// 辞書をセーブする
int SaveCRDictionary(const char fn[]);

// 認識モードを得る
int GetCRMode(void);
// 認識モードを設定する
void SetCRMode(int mode);

// 認識候補フィルタを設定する
void SetCRPassFilter(int (*proc)(unsigned code, void *param), void *param);
// 認識候補フィルタの設定を取得する
void GetCRPassFilter(CRFILTER *crflt);
// 加点フィルタを設定する
void SetCRBonusFilter(int (*proc)(unsigned code, void *param), void *param);
// 加点フィルタの設定を取得する
void GetCRBonusFilter(CRFILTER *crflt);

// 小文字の大きさの上限を設定する
void SetSmallCharSize(int size);
// 文字枠矩形を設定する
void SetGuideBoxRect(PAT_POS *pos);

// 認識辞書ロード
int LoadCRDictionary(const char fn[], CRDIC *dic);
// 認識辞書セット
void SetCRDictionary(CRDIC *dic, CRDIC *pre_dic);
// 現在の辞書を得る
void GetCRDictionary(CRDIC *dic);
// 辞書を開放する
void FreeCRDictionary(CRDIC *dic);

int setDic();
CRDIC getDic();
/*int MakePattern(CATEGORY *kj,
				PATDIC *patdic, int x, int y, int sx, int sy, int allflag);*/
#ifdef __cplusplus
}
#endif

#endif