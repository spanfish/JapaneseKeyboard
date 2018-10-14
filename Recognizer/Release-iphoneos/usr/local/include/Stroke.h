/*************************************************************************

 Header file for strokes
 Author: ZHOU XIANGDONG
 Updated: 2009.6

**************************************************************************/

#ifndef _STROKE_H_
#define _STROKE_H_

#include "CGBase.h"
#include "OnlineDef.h"

// for preprocessing and display
#define CX_RES 800
#define CY_RES 600
#define RESAMPLE_STEP 5

enum
{
	STRK_TEXT = 0x30,    // text, label '0'
	STRK_NONTEXT = 0x31,  // nontext, label '1'
	STRK_OTHERS = 0x32    // others, label '2'
};

class CStroke;
class CUniStrkFtr;
class CBiStrkFtr;

/////////////////////////////////////////////////////////////////////////////////////////////////
// global function
void PreProcessing(int nStrkNum, int vtNums[], POINT2D vertex[], POINT2D shift, 
				   float scale, float step);
void StrkDataCvr(int nStrkNum, int vtNums[], POINT2D vertex[], CStroke strokes[]);

/////////////////////////////////////////////////////////////////////////////////////////////////
// class CStroke
class CStroke: public CCurve
{

private:
	PT_STROKE_ADD_INFOS m_strkAddInfos;

public:
// constructors
    // construct with stroke additional information
	CStroke();
	CStroke(int initVNum, POINT2D initVertex[]);
	CStroke(int initVNum, POINT2D initVertex[], PT_STROKE_ADD_INFOS initStrkAddInfos);
	void operator=(const CStroke &initStroke);
	
	// featrues
	// Willems-IGS2005-Features for mode detection in natural online pen input
	// Willems-ICDAR05-Mode detection in on-line pen drawing and handwriting recognition
	float Compactness(float dParameter, float dArea) const;
	float Eccentricity(float dMajorAxis, float dMinorAxis) const;
	float PrincipalAxis(float dMajorAxis, float dMinorAxis) const;
	float Rectangularity(float dMajorAxis, float dMinorAxis, float dArea) const;

	CPoint2D Centroid() const;
	float MeanRadius(POINT2D centroid) const;
	float CircularVariance(POINT2D centroid, float dMeanRadius) const;
	float NormCentroidOffset(POINT2D centroid, POINT2D ptMajor1, POINT2D ptMajor2) const;

	float Closure() const;
	
	void GetAngles(int &nAngleNum, float angles[]) const;
	float Curvature(int nAngleNum, float angles[]) const;
	float Perpendicularity(int nAngleNum, float angles[]) const;
	float SgnPerpendicularity(int nAngleNum, float angles[]) const;
	float SgnCurvature() const;	
};

/////////////////////////////////////////////////////////////////////////////////////////////////
// class CUniStrkFtr
class CUniStrkFtr
{	
private:
	int m_nFtrDim;

public:
	CUniStrkFtr();
	int GetFtrDim() const;
	void GetFtr(int nStrkNum, CStroke strokes[], int index, dType ftr[]) const;

protected:	
	int NbStrkNum(int nStrkNum, CStroke strokes[], int index) const;

	void SetExtreme(float dMin, float dMax, float arrMin[], float arrMax[], int index) const;	
};

/////////////////////////////////////////////////////////////////////////////////////////////////
// class CBiStrkFtr
class CBiStrkFtr 
{
private:
	int m_nFtrDim;

public:
	CBiStrkFtr();
	int GetFtrDim() const;
	void GetFtr(int nStrkNum, CStroke strokes[], int index1, int index2, dType ftr[]) const;
	
private:
	float OffStrkLen(const CStroke &stroke1, const CStroke &stroke2) const;
	float MinDist(const CStroke &stroke1, const CStroke &stroke2) const;
	void MaxMinEndPtDist(const CStroke &stroke1, const CStroke &stroke2, float &dMaxDist, float &dMinDist) const;
	void DistDiff(const CStroke &stroke1, const CStroke &stroke2, float &dMaxDiff, float &dMinDiff) const;
	void NbStrks(int nStrkNum, CStroke strokes[], int index, int &nNbNum, int Nb[]) const;
	int ComNbStrkNum(int nStrkNum, CStroke strokes[], int index1, int index2) const;
								 	
	void SetExtreme(float dMin, float dMax, float arrMin[], float arrMax[], int index) const;
};

#endif /* _STROKE_H_ */