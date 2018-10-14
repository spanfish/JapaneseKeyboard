/*************************************************************************

 Header file for text line grouping
 Author: ZHOU XIANGDONG
 Updated: 2009.6

**************************************************************************/

#ifndef _TXTLINESET_H_
#define _TXTLINESET_H_

#include "Stroke.h"
#include "TxtLnMrg.h"

#define SAMP_STEP_COEF  10
#define BLOCK_COEF 0.8
#define LINE_COEF 5
#define MAX_SEG_NUM 100

enum
{
	LINE_MERGE = 0x30,    // merge, label '0'
	LINE_NONMERGE = 0x31,  // nonmerge, label '1'
};

// stroke in text line
typedef struct tagLINE_STRK{
	BOUND bound;
	int pos; // position in m_vertex[]
	BYTE type; // text or non-text
} LINE_STRK, *PLINE_STRK;

// block
typedef struct tagLINE_BLOCK{
	int nStart; // start stroke index
	int nEnd; // end stroke index
	int nPtNum; // point number
	POINT2D *ptSet; // point set for regression
	BOUND bound; // bound
	BYTE type; // text or non-text
} LINE_BLOCK, *PLINE_BLOCK;

// candidate line
typedef struct tagTXT_LINE{
	int nBlockNum; // block number
	int *blockIdx; // block indice

	float sigma2; // regression error
	float sigma2av; // average regression error, sigma2/n
	VECTOR dir; // direction
	VECTOR nor; // normal
	POINT2D mean; // mean
	float lambda1; // maximum eigenvalue
	float lambda2; // minimum eigenvalue
	float width; // along direction width 
	float height; // along norm height
	float xmax; // maximum distance along line direction
	float ymax; // maximum distance along norm direction

	CPolygon bound; // line bound
} TXT_LINE, *PTXT_LINE;

// path node for line segmentation
typedef struct tagLINE_NODE {
	float D; // accumulated cost
	int t; // separation point
	int s; // segment number
	int i; // path index
	int dep; // depth
} LINE_NODE, *PLINE_NODE;

// line neighbor in temporal merge
typedef struct tagTMP_MRG_NB {
	int idx; // index, line or block
	BYTE type; // STRK_TEXT or STRK_NONTEXT
	float conf; // confidence
} TMP_MRG_NB, *PTMP_MRG_NB;

// hypotheses in temporal merge
typedef struct tagTMP_MRG_HYP {
	int nbnum; // neighbor number
	TMP_MRG_NB nbs[2]; // neighbors
} TMP_MRG_HYP, PTMP_MRG_HYP;


// class text line set
class CTxtLnSet
{
public:
	CTxtLnSet();
	CTxtLnSet(int nStrkNum, int vtNums[], POINT2D vertex[], char strkTypes[], CTxtLnMrg *pTxtLnMrg, char *szSR_FUN);	
	void operator=(const CTxtLnSet &txtLnSet);
	void GetStrkType(char strkTypes[]);
	void GetLnStrks(int nLnIdx, int &nStrkNum, int *strkIdx);
	void GetLnStrks(const TXT_LINE &line, int &nStrkNum, int *strkIdx);
	INT_PAIR GetLnStartEndStrkIdx(int nLnIdx);
	~CTxtLnSet();
	
public:
	void DelLnSetDat();
	void DatCpy(const CTxtLnSet &txtLnSet);
	void BlkCpy(LINE_BLOCK &block1, const LINE_BLOCK &block2);
	void LnCpy(TXT_LINE &line1, const TXT_LINE &line2);
	
	void Init(int nStrkNum, int vtNums[], POINT2D vertex[], char strkTypes[], CTxtLnMrg *pTxtLnMrg, char *szSR_FUN);
	float GetSampStep(int nStrkNum, int vtNums[], POINT2D vertex[]);
	float CharSize();
	void GetSkeleton();
	void InitLns();
	
	void PreSeg();
	void CreateBlk(int nStrkIdx);
	void CreateLn(int nBlockIdx);
	float TmpStrkBlkDist(const CStroke &stroke, const LINE_BLOCK &block) ;
	bool StrkBlkSp(const CStroke &stroke, const LINE_BLOCK &block);	
	void BlkRSPts(LINE_BLOCK &block);
	void LnFit(TXT_LINE &line);
	void LnRSPts(int &nPtNum, POINT2D ptSet[], const TXT_LINE &line);
	
	void TmpSeg();
	float CharSize(const TXT_LINE &line);
	void CreateLns(int blockIdx[], int nBlockNum, int blkSPs[]);
	void CreateLn(int blockIdx[], int ssp, int esp, TXT_LINE &line);
	void DelLn(TXT_LINE &line);
	void LnCount();

	// for comparison experiment with TmpSeg()
	void TmpSeg_Cmp();
	bool LnSeg(TXT_LINE &line, int &sp);
	void LnChk();

	void Get2Best(float weights[], float ftr1[], float &score1, float ftr2[], float &score2);
	float GetPathScore(float weights[], float ftr[], char szType[]);
	float LDF(float weights[], float ftr[], int nFtrDim);
	float LR(float weights[], float ftr[], int nFtrDim);
	bool GetTruSPs(int strkSPs[]);	
	void GetRvlSPs(int nBlockNum, float ***UnFtrMtx, int nUnFtrDim, float ****BiFtrMtx, int nBiFtrDim, float weights[], int blkSPs[], int &nLnNum, float dCharSize, char *szType);
	float MaxInLnDist(const TXT_LINE &line);
	void GetBlkProjs(const TXT_LINE &line, SEGMENT projs[]);
	CPoint2D GetRfPt(VECTOR dir, SEGMENT projs[], int num);
	void SortProjs(SEGMENT projs[], int num, POINT2D o);
	void MrgProjs(SEGMENT projs[], int &num);
	bool MrgProjs(SEGMENT &proj1, SEGMENT proj2);
	float MaxOffStrkProj(const TXT_LINE &line);
	void GetOffStrkProjs(const TXT_LINE &line, SEGMENT projs[]);
	float GetComArea(const TXT_LINE &line1, const TXT_LINE &line2);
	CVector GetTruDir(const TXT_LINE &line);
	void CstLatLns(int blockIdx[], int nBlockNum, int nSegNum, TXT_LINE lat[]);
	void DelLatLns(int nBlockNum, int nSegNum, TXT_LINE lat[]);
	void CstUnMtx(int nBlockNum, int nSegNum, TXT_LINE lat[], float **UnMtx, float dCharSize,const char *szType);
	void CstBiMtx(int nBlockNum, int nSegNum, TXT_LINE lat[], float ***BiMtx, float dCharSize,const char *szType);
	void CstU(int nBlockNum, int nSegNum, float **U, float ***UnFtrMtx, int nUnFtrDim, float *weights);
	void CstV(int nBlockNum, int nSegNum, float ***V, float ****BiFtrMtx, int nBiFtrDim, float *weights);
	bool Plausible(const TXT_LINE &line, float dCharSize);
	void CstFtrMtx(int nBlockNum, int nSegNum, TXT_LINE lat[],  float ***UnFtrMtx, int &nUnFtrDim, float ****BiFtrMtx, int &nBiFtrDim, float dCharSize, char *szType);
	void GetPathFtr(int blkSPs[], int dep, float ftr[], float ***UnFtrMtx, int nUnFtrDim, float ****BiFtrMtx, int nBiFtrDim, char *szType);
	float UnSumFtr(int blkSPs[], int dep, float **UnMtx);
	float UnMinFtr(int blkSPs[], int dep, float **UnMtx);
	float BiSumFtr(int blkSPs[], int dep, float ***BiMtx);
	float BiMinFtr(int blkSPs[], int dep, float ***BiMtx);
	void GetPathFtr(const TXT_LINE &line, float ftr[], float dCharSize, char szType[]);
	void GetPathFtr(const TXT_LINE &line1, const TXT_LINE &line2, float ftr[], float dCharSize, char szType[]);
	float GetMrgConf(const TXT_LINE &line1, const TXT_LINE &line2, float weights[], int nFtrDim, char szType[]);
	void LnSeg(int nBlockNum, float ***UnFtrMtx, int nUnFtrDim, float ****BiFtrMtx, int nBiFtrDim, float weights[], int blkSPs1[], int blkSPs2[], float dCharSize, char *szType);
	void DP_TS_SP(int T, int S, int BN, float **U, float ***V, int *rst1, int *rst2);
	void BS_TS_SP(int T, int S, int BN, float *weights, float ***UnFtrMtx, int nUnFtrDim, float ****BiFtrMtx, int nBiFtrDim, int *rst1, int *rst2, char *szType);
	void InsertPath(float *Mtx_D, int *Mtx_t, int *Mtx_s, int *Mtx_i, int *Mtx_dep, int &num, int BN, const LINE_NODE &path); 
	void CopyPath(float *Mtx_D, int *Mtx_t, int *Mtx_s, int *Mtx_i, int *Mtx_dep, int pos, const LINE_NODE &path); 
	void MovePath(float *Mtx_D, int *Mtx_t, int *Mtx_s, int *Mtx_i, int *Mtx_dep, int pos, int num, int BN); 
	void BackTrack(int t, int i, int **PRE_i, int **CUR_s, int **DEP, int *rst, int &dep);
	
	void TmpMrg();
    void TmpMrg(int nTruLnNum, int *truStrkNums, int **truth, int &nFtrNum, dType *ftr, BYTE *labels);
	void GetLnNbs(int nLnIdx, TMP_MRG_HYP &hyp);
	int GetMaxConfNb(int nLnIdx, const TMP_MRG_HYP &hyp);
	int GetTruIdx(int nStrkNum, int *strkIdx, int nTruLnNum, int *truStrkNums, int **truth);
	int GetTruIdx(int idx, int nTruLnNum, int *truStrkNums, int **truth);
	void LnSort(char *szType);
	void CreateLn(const TXT_LINE &line1, const TXT_LINE &line2, TXT_LINE &line);
	void CreateLn(int nBlkIdx, TXT_LINE &line);
	float MaxLnStrkLen(const TXT_LINE &line);
	int LnStrkNum(const TXT_LINE &line);
	float InsecRto(CStroke strk1, CStroke strk2);
	float InsecRto(LINE_BLOCK &blk);
	void GetTmpLn2Ftr(int nLnIdx1, int nLnIdx2, dType ftr[]);
	void GetTmpLn2Ftr(const TXT_LINE &line1, const TXT_LINE &line2, dType ftr[]);
	void GetTmpLnBlkFtr(int nLnIdx, int nBlkIdx, dType ftr[]);
	void SetExtr(double dMin, double dMax, double mins[], double maxs[], int index);
	float TmpLn2Dist(const TXT_LINE &line1, const TXT_LINE &line2);
	float TmpLn2Dist(int nLnIdx1, int nLnIdx2);
	void GetLnEndSeg(const TXT_LINE &line, CSegment &head, CSegment &tail);
	float GetMrgConf(int nLnIdx, int idx, char *szType);
	bool Ln2Proc(int nLnIdx1, int nLnIdx2, int *truLnIdx, dType *ftr, BYTE *label);
	bool LnBlkProc(int nLnIdx, int nBlkIdx, int *truLnIdx, int *truBlkIdx, dType *ftr, BYTE *label);
	int LnIdx(int nBlkIdx);
	void Ln2Mrg(int nLnIdx1, int nLnIdx2);
	void LnBlkMrg(int nLnIdx, int nBlkIdx);
	void LnBlkRmv(int nLnIdx, int nBlkIdx);
	void PostProc();
	
	void SptMrg();
    void SptMrg(char *szType);
	void GetLnNbs(float **nbmat, int lidx, int *nbs, int &num, char *szType);
	int GetMaxConfNb(int nLnIdx, int *nbs, int num);
	void UpdtNbMat(float **nbmat, int lidx1, int lidx2, char *szType);
	void UpdtNbMat(float **nbmat, int lidx);
	float SptLn2Dist(const TXT_LINE &line1, const TXT_LINE &line2);
	float SptLn2Dist(const TXT_LINE &line1, const TXT_LINE &line2, SEGMENT &seg1, SEGMENT &seg2, int &flag1, int &flag2);
	bool Ln2Sp(const TXT_LINE &line1, const TXT_LINE &line2, char szType[]);
	int BlkIdx(const TXT_LINE &line, SEGMENT seg);
	float ComAreaRto(const TXT_LINE &line1, const TXT_LINE &line2);
	float ComAreaRto(const TXT_LINE &line, const LINE_BLOCK &block);
	
public:	
	int m_nLnNum; // text line number
	TXT_LINE *m_lines; // text lines

public:
	// for text line 
	float m_dCharSize; // character size
	int m_nBlkNum; // block number
	LINE_BLOCK *m_blocks; // blocks

	int m_nStrkNum;
	int *m_vtNums;
	POINT2D *m_vertex;
	int m_nPtNum;
	LINE_STRK *m_strokes;
	
	CStroke m_lntStrokes[1024]; // long non text strokes
	int m_nLNT; // long non text strokes number
	POINT2D m_crPts[2048]; // critical points (long non-text intersection points and corners)
	int m_nCrPtNum;

	// for DP training
	int m_nTruLnNum; // truth line number
	int m_truSPs[MAX_PAGE_LINE_NUM]; // truth line separation points in blocks

	// for DP test and spatial merge
	enum { m_nFtrDim_DP=4, m_nFtrDim_BS=6, m_nFtrDim_SPT=4 };
	float m_ws_DP[256]; // weights for DP
	float m_ws_BS_LDF[256]; // weights for beam search with linear discriminant function
	float m_ws_BS_LR[256]; // weights for beam search with logistic function
	float m_ws_SPT[256]; // spatial contain, the dimensionality is m_nUnFtrDim_DP

	// for temporal merging
	enum { m_nFtrDim_TMrg=21 };
	CTxtLnMrg *m_pTxtLnMrg;

	// search strategy and discriminant function
	char m_szSR_FUN[256];
};

#endif /* _TXTLNSET_H_ */