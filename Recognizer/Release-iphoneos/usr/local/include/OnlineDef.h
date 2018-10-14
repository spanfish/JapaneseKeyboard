/* Online character recognition definitions */

#ifndef	_ONLINEDEF_H_	
#define	_ONLINEDEF_H_

#include "def.h"
#include "CGBase.h"

#define MAX_FTR_DIM 1024
#define MAX_ILLUSTR_LEN 512
#define MAX_ATTR_LEN 512
#define MAX_CODE_LEN 4

#define MAX_CHAR_STROKE_NUM 60
#define MAX_CHAR_POINT_NUM 10000

#define MAX_LINE_STROKE_NUM 1500
#define MAX_LINE_CHAR_NUM 150
#define MAX_LINE_POINT_NUM 20000

#define MAX_PAGE_NUM 200000
#define MAX_PAGE_LINE_NUM 500
#define MAX_PAGE_CHAR_NUM 2000
#define MAX_PAGE_STROKE_NUM 10000
#define MAX_PAGE_POINT_NUM 100000

#define MAX_SUP_CLASS_NUM 20

//----------------------------------------------------------------------------------------------------------------------------
//                                                  CPT file
//----------------------------------------------------------------------------------------------------------------------------

// *.CPT file header
typedef struct tagCPT_HEADER
{
	long lHdSize;  // size of header: 54+strlen(illustr)+1 (there is a '\0' at the end of illustr)
	char szCode[8]; // "CPT"
	char szIllustr[MAX_ILLUSTR_LEN];  // text of arbitrary length. "#......\0"
	char szCodeType[20]; // "ASCII", "GB", "SJIS" etc
	short sCodeLen; // 1, 2, 4, etc
	char szDataType[20]; // "short", "long" etc
} CPT_HEADER, *PCPT_HEADER; 

// character sample
typedef struct tagCPT_SAMP
{
	char label[MAX_CODE_LEN]; // label
	int nPtNum; // point number
	char szAttr[MAX_ATTR_LEN]; // attribute. "#......\0"
	POINTS *traj; // trajectory
} CPT_SAMP, *PCPT_SAMP;

//----------------------------------------------------------------------------------------------------------------------------
//                                                  SPT file
//----------------------------------------------------------------------------------------------------------------------------

// *.SPT file header
typedef struct tagSPT_HEADER
{
	long lHdSize;  //size of header: 54+strlen(illustr)+1 (there is a '\0' at the end of illustr)
	char szCode[8]; // "SPT"
	char szIllustr[MAX_ILLUSTR_LEN];  // text of arbitary length. "#......\0"
	char szCodeType[20]; // "ASCII", "GB", "SJIS" etc
	short sCodeLen; // 1, 2, 4, etc
	char szDataType[20]; // "short", "float" etc
} SPT_HEADER, *PSPT_HEADER; 

// stroke
typedef struct tagSPT_STROKE
{
	short sCharIdx;      // the character index in labels that the stroke belongs to
	int nPtNum; // point number
	POINTS *traj; // trajectory
} SPT_STROKE, *PSPT_STROKE;

// string sample
typedef struct tagSPT_SAMP
{
	BYTE bLnDir; // line direction
	BYTE bCharOrt; // character orientation
	int nCharNum;  // character number
	char szLabels[MAX_LINE_CHAR_NUM*MAX_CODE_LEN]; // labels
	int nStrkNum; // stroke number
	SPT_STROKE strokes[MAX_LINE_STROKE_NUM]; // strokes
} SPT_SAMP, *PSPT_SAMP;

// string sample
typedef struct tagSPT_SAMP_B
{
	BYTE bLnDir; // line direction
	BYTE bCharOrt; // character orientation
	int nCharNum;  // character number
	char *szLabels; // labels
	int nStrkNum; // stroke number
	SPT_STROKE *strokes; // strokes
} SPT_SAMP_B, *PSPT_SAMP_B;

// line direction
enum
{
	LN_DIR_LEFT_RIGHT, // left-right
	LN_DIR_TOP_DOWN  // top-down
};

// character orientation
enum
{
	CHAR_ORT_ORTHOGONAL, // orthogonal
	CHAR_ORT_PARALLEL    // parallel
};

//----------------------------------------------------------------------------------------------------------------------------
//                             SIF file (for performance evaluation in string recognition)
//----------------------------------------------------------------------------------------------------------------------------

// SIF file header
typedef struct tagSIF_HEADER
{
	long lHdSize;  //size of header: 12+strlen(illustr)+1 (there is a '\0' at the end of illustr)
	char szCode[8]; // "SIF" 
	char szIllustr[MAX_ILLUSTR_LEN];  // text of arbitrary length. "#......\0" 
	char szCodeType[20]; // "ASCII", "GB", "SJIS" etc
	short sCodeLen; // 1, 2, 4, etc
	char szDataType[20]; // "short", "float" etc
} SIF_HEADER, *PSIF_HEADER;

// character
typedef struct tagSIF_CHAR
{
	char label[MAX_CODE_LEN]; // label
	int nStrkNum; // stroke number
	int strkIdx[MAX_CHAR_STROKE_NUM]; // stroke indice
} SIF_CHAR, *PSIF_CHAR;

// string
typedef struct tagSIF_STR
{
	int nCharNum; // character number
	SIF_CHAR chars[MAX_LINE_CHAR_NUM]; // characters
} SIF_STR, *PSIF_STR;

//----------------------------------------------------------------------------------------------------------------------------
//                                                  PT file
//----------------------------------------------------------------------------------------------------------------------------

// *.PT file header
typedef struct tagPT_HEADER
{
	long lHdSize;  // size of header: 58+strlen(illustr)+1 (there is a '\0' at the end of illustr)
	char szCode[8]; // "PT"
	char szIllustr[MAX_ILLUSTR_LEN];  // text of arbitrary length. "#......\0"
	char szCodeType[20]; // "ASCII", "GB", "SJIS" etc
	short sCodeLen; // 1, 2, 4, etc
	char szDataType[20]; // "short", "long" etc
} PT_HEADER, *PPT_HEADER; 

// stroke additional informations
typedef struct tagPT_STROKE_ADD_INFOS
{ 
	unsigned short wPenoffTime; // off-stroke time [msec]
	unsigned short wPenonTime;  // on-stroke time [msec]
	unsigned short wCharIdx;      // the character index in labels that the stroke belongs to
	unsigned char byProperty;  // property
	unsigned char byType;      // stroke type
} PT_STROKE_ADD_INFOS, *PPT_STROKE_ADD_INFOS;

// stroke
typedef struct tagPT_STROKE
{
	PT_STROKE_ADD_INFOS addInf; // stroke additional information
	int nPtNum; // point number
	POINTS *traj; // trajectory
} PT_STROKE, *PPT_STROKE;

// page
typedef struct tagPT_PAGE
{
	int nCharNum;  // character number
	char szLabels[MAX_PAGE_CHAR_NUM*MAX_CODE_LEN]; // labels
	int nStrkNum; // stroke number
	PT_STROKE strokes[MAX_PAGE_STROKE_NUM];
} PT_PAGE, *PPT_PAGE;

// stroke property
enum
{
	SP_Default        = 0x00, /* デフォルト       */
	SP_UnreliableTime = 0x01, /* 時間信憑性なし   */
	SP_Invalidated    = 0x02  /* 消去線で消された */
};

// stroke type
enum
{
	SK_Text,       /* 文字を構成する（デフォルト） */
	SK_Formula,    /* 数式を構成する */
	SK_Figure,     /* 図を構成する   */
	SK_RuledLine,  /* 罫線を構成する */
	SK_EditingMark /* 編集記号である */
};

//----------------------------------------------------------------------------------------------------------------------------
//                                                  MPF file
//----------------------------------------------------------------------------------------------------------------------------

// *.MPF file header
typedef struct tagMPF_HEADER
{
	long lHdSize;  //size of header: 62+strlen(illustr)+1 (there is a '\0' at the end of illustr)
	char szCode[8]; // "MPF"
	char szIllustr[MAX_ILLUSTR_LEN];  // text of arbitary length. "#......\0"
	char szCodeType[20]; // "ASCII", "GB", "SJIS" etc
	short sCodeLen; // 1, 2, 4, etc
	char szDataType[20]; // "short", "long" etc
	long lSampNum; // sample number
	long lDim; // dimensionality
} MPF_HEADER, *PMPF_HEADER; 

//----------------------------------------------------------------------------------------------------------------------------
//                                                    LIF file
//----------------------------------------------------------------------------------------------------------------------------

// LIF file header
typedef struct tagLIF_HEADER
{
	long lHdSize;  //size of header: 12+strlen(illustr)+1 (there is a '\0' at the end of illustr)
	char szCode[8]; // "LIF" 
	char szIllustr[MAX_ILLUSTR_LEN];  // text of arbitary length. "#......\0" ("#TRUTH" or "#RESULT")
} LIF_HEADER, *PLIF_HEADER;

// character
typedef struct tagLIF_CHAR
{
	int nStrkNum; // stroke number
	int strkIdx[MAX_CHAR_STROKE_NUM]; // stroke indice
} LIF_CHAR, *PLIF_CHAR;

// truth line
typedef struct tagLIF_TRUTH_LINE
{
	int nStrkNum; // stroke number
	int strkIdx[MAX_LINE_STROKE_NUM]; // stroke indice
	int nCharNum; // character number
	int charIdx[MAX_LINE_CHAR_NUM]; // character indice 
	LIF_CHAR chars[MAX_LINE_CHAR_NUM]; // characters
} LIF_TRUTH_LINE, *PLIF_TRUTH_LINE;

// truth page
typedef struct tagLIF_TRUTH_PAGE
{
	int nLnNum; // line number
	LIF_TRUTH_LINE lines[MAX_PAGE_LINE_NUM]; // lines
} LIF_TRUTH_PAGE, *PLIF_TRUTH_PAGE;

// result line
typedef struct tagLIF_RESULT_LINE
{
	int nStrkNum; // stroke number
	int strkIdx[MAX_LINE_STROKE_NUM]; // stroke indice
} LIF_RESULT_LINE, *PLIF_RESULT_LINE;

// result page
typedef struct tagLIF_RESULT_PAGE
{
	int nLnNum; // line number
	LIF_RESULT_LINE lines[MAX_PAGE_LINE_NUM]; // lines
} LIF_RESULT_PAGE, *PLIF_RESULT_PAGE;

//----------------------------------------------------------------------------------------------------------------------------
//                                                    LNS file
//----------------------------------------------------------------------------------------------------------------------------

// DP file header
typedef struct tagDP_HEADER
{
	long lHdSize;  //size of header: 12+strlen(illustr)+1 (there is a '\0' at the end of illustr)
	char szCode[8]; // "LIF" 
	char szIllustr[MAX_ILLUSTR_LEN];  // text of arbitary length. 
} DP_HEADER, *PDP_HEADER;

// sample
typedef struct tagDP_SAMP
{
	int nStrkNum; // stroke number
	int ptNums[MAX_PAGE_STROKE_NUM]; // point number of each text line
	POINTS traj[MAX_PAGE_POINT_NUM]; // trajectory 
	int nLnNum; // text line number
	int sidx[MAX_PAGE_LINE_NUM]; // start stroke index of each text line
	double dCharSize; // character size
} DP_SAMP, *PDP_SAMP;

//----------------------------------------------------------------------------------------------------------------------------
//                                                    COD file
//----------------------------------------------------------------------------------------------------------------------------

// super class
typedef struct tagSUP_CLS
{
	int nClassNum; // class number of the super class
	char *labels; // labels
} SUP_CLS, *PSUP_CLS;

// code file data
typedef struct tagCOD_DAT
{
	short sCodeLen; // code length
	int nClassNum; // super class number
	SUP_CLS supCls[MAX_SUP_CLASS_NUM];
} COD_DAT, *PCOD_DAT;


#endif /* _ONLINEDEF_H_ */

