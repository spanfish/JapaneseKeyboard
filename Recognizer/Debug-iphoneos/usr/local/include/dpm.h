#ifndef __DPM_H__

#define __DPM_H__

#include "crlib.h"

typedef struct{
	LONG score;
	SHORT _tmp_score;
	SHORT dir;
	SHORT np_num;
	SHORT overlen;
	SHORT _length;
	SHORT dic_stroke;
} MDTBL;

typedef struct{
	int min_score;
	int rej_start;
	int maxoverlen;
} DPM_PARAM;

#ifdef __cplusplus
extern "C"{
#endif

void setdpmparam(DPM_PARAM *dp);
void getdpmparam(DPM_PARAM *dp);
int mkmdtbl(MDTBL *mdt, PATTERN_B *dic, int start_dic, PATTERN_B *in);
void mdttonpt(NP_TABLE *npt, MDTBL *mdt, int dic_num, int in_num);
int dpmatching(NP_TABLE *npt, PATTERN_B *dic, PATTERN_B *in);
int ruijido(NP_TABLE *npt, PATTERN_B *dic, PATTERN_B *in);
int dpmcr(CP_DIC *dic, PATTERN_W *id, CR_RESULT *res, int res_num);

//#ifdef __clpusplus
#ifdef __cplusplus
}
#endif

#endif