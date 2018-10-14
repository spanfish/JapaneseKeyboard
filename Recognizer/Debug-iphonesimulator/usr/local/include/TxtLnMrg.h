#ifndef _TXTLNMRG_H_
#define _TXTLNMRG_H_

#include "Def.h"
//#include "Classify.h"

class CTxtLnMrg
{
/*public:
	int m_nClassNum;
	int m_nFtrDim;
	short m_sCodeLen;
	char *m_codetable;*/

public:
	CTxtLnMrg(char* szDic);
	~CTxtLnMrg();
	float TxtLnMrg(dType *ftr, int nFtrDim);
	
/*private:
	CClassifier *m_pClassifr;
	int rankNum;
	int coarse;
	REAL coarThr;
	int quadr;
	int knum;*/
};

#endif /* _TXTLNMRG_H_ */