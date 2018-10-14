/*************************************************************************

 Header file for text line grouping
 Author: ZHOU XIANGDONG
 Updated: 2009.6

**************************************************************************/

//---------------------------------------------------------------------------
#ifndef DetectLineH
#define DetectLineH

#include "InkStroke.h"
#include "CGBase.h"
#include "Utility.h"

//---------------------------------------------------------------------------
class DetectLine {
public:
	DetectLine();
	~DetectLine();
	void Execute(InkStroke *inkStroke, int count);

private:
	void Allocate(InkStroke *inkStroke, int count);
	void DataConversion(InkStroke *inkStroke, int count);
	void Release();
	void TemporalSegmentation(INT_PAIR *sidx, CPolygon *bounds, int &nLnNum, char *strkTypes);

public:
	void Execute(InkStroke *inkStroke, int count, INT_PAIR *sidx, CPolygon *bounds, int &nLnNum, char *strkTypes);

private:
	int m_nStrkNum;
	int *m_vtNums;
	POINT2D *m_vertex;
	int m_nPtNum;

	float m_scale;
	int m_cxInRes;
	int m_cyInRes;
};
//---------------------------------------------------------------------------
#endif
