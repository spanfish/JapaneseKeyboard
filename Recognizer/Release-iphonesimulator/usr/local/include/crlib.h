/*
=================================================================

		Online character recognition library header file

											Katsuhiko Akiyama

=================================================================
*/

#ifndef __CRLIB_H__

#define __CRLIB_H__

#include "btype.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* 高速化のための COS テーブル使用スイッチ */
#define USE_COS_TABLE

/*　属性ビットの定義　*/
#define PA_Cross			1		/*　クロスストローク　*/
#define PA_Start			2		/*　ストロークの始点　*/
#define PA_End				4		/*　ストロークの終点　*/
#define PA_CrossParam		8		/*　cross param　*/
#define GetCrossOfs(ATR)	(((ATR) >> 3) & 3)
#define PA_Unlink			0x20	/*　非連結　*/
#define PA_Omissible		0x40	/*　省略可能点　*/
#define PA_Unstable			0x80	/*　方向不安定ストローク　*/

enum{
	CR_NoMatter = 0, CR_NoMemory, CR_NoPoint, CR_FileError,
	CR_NoHeader, CR_ParamError
};

#define CR_MaxScoreBit		10
#define CR_MaxScore			(1 << CR_MaxScoreBit)
#define CR_NormSizeBit		7
#define CR_NormSize			(1 << CR_NormSizeBit)

enum{
	CR_StrokeIndepend = 0, CR_StrokeDepend
};

typedef struct{
	BYTE x, y, l, attr;
#ifdef USE_COS_TABLE
	SHORT dir, dummy;
#endif
} POINT_B;

typedef struct{
	int maxx, maxy, minx, miny;
} PAT_POS;

typedef struct{
	POINT_B *data;
	PAT_POS pos;
	WORD code;
	SHORT num, len, stroke;
} PATTERN_B;

typedef struct{
	int cat;
	PATTERN_B *tbl;
} CP_DIC;

typedef struct{
	SHORT x, y;
	BYTE attr;
} POINT_W;

typedef struct{
	POINT_W *data;
	int num;
} PATTERN_W;

/*　Ｎｏｄｅ　Ｐａｉｒ　型　*/
typedef struct{
	int dic, in;
	int attr, score;
} NODE_PAIR;

/*　Ｎｏｄｅ　Ｐａｉｒ　Ｔａｂｌｅ　型　*/
/*　NODE_PAIR 型の配列とその数が格納される　*/
typedef struct{
	int num;
	NODE_PAIR *pair;
} NP_TABLE;

/*　候補型　*/
/*　認識候補文字コードとその評価値が格納される　*/
typedef struct{
	int pat_no, score;
	unsigned code;
} CR_RESULT;

typedef struct{
	int minarc, minsc, crmode, rejstart;
	int overlen, lastover, minedge;
} CR_INFO;

typedef struct{
	int ssp_dic, ssp_dic_save;
	int ssp_in, ssp_in_save;
	int mdr, prev_maxmd, nmaxmdr, maxmdr, sc;
	int stop_in_count, over_ldic;
	int stop_dic_count, over_lin;
	int len, lenr;
	int ignore_flag;
	NODE_PAIR pair;
	NP_TABLE npt;
	PATTERN_B dic, in;
} MATCH_INFO;

#ifdef __cplusplus
extern "C" {
#endif

CP_DIC *createcpdic(int maxcat);
void releasecpdic(CP_DIC *dic);
int loadcpdic(CP_DIC *dic, const char *fname);
int savecpdic(CP_DIC *dic, const char *fname);
int getcpdiccat(const char *fname);
void initcpdic(CP_DIC *dic);
int maxcpdicpt(CP_DIC *dic);
void setcpdicpat(CP_DIC *dic, PATTERN_B *ipd, int num);
void getcpdicpat(CP_DIC *dic, PATTERN_B *ipd, int num);

int mdcal(POINT_B  *dic, POINT_B  *in, int dic_p, int in_p);
int mdcalus(POINT_B  *dic, POINT_B  *in, int dic_p, int in_p);
int ltmatching(NP_TABLE *pl, PATTERN_B *dic, PATTERN_B *in);
int hyouka(NP_TABLE *npl, PATTERN_B *dic, PATTERN_B *in);
int evaluate(NP_TABLE *pl, PATTERN_B *dic, PATTERN_B *in);
int recognize(CP_DIC *dic, PATTERN_W *id, CR_RESULT *res, int res_num);

void setfeature(PATTERN_B *pd);
void getpatpos(PAT_POS *pos, PATTERN_W *pd);
void normalize(PAT_POS *pos, PATTERN_W *in, PATTERN_W *out);
void setchptattr(PATTERN_W *in);
int createpat(PAT_POS *pos, PATTERN_W *id, PATTERN_B *out);
void releasepat(PATTERN_B *pd);

void setcrinfo(CR_INFO *crinfo);
void getcrinfo(CR_INFO *crinfo);

int settekitoflag(int flag);
int gettekitoflag(void);

void initpartmatch(
		MATCH_INFO *mi, NP_TABLE *pl, PATTERN_B *dic, PATTERN_B *in);
int partmatching(MATCH_INFO *match_info, int stop_no);

int initcrlib(void);
void closecrlib(void);

#ifdef USE_COS_TABLE
int initcostable(void);
int initdirtable(void);
void closecostable(void);
void closedirtable(void);
SHORT getdirection(int dx, int dy);
#endif

#ifdef	__cplusplus
}
#endif

#endif