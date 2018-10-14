/*************************************************************************

 Header file for computional geometry
 Author: ZHOU XIANGDONG
 Updated: 2009.6

**************************************************************************/

#ifndef _CGBASE_H_
#define _CGBASE_H_

#if defined(WIN32)
#include <windows.h>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////
//Constants and marcos

#define MAX_CNUM 512  // curve number
#define MAX_VNUM 5000 // vertex number


/////////////////////////////////////////////////////////////////////////////////////////////////
//Structures

#if defined(WIN32)

#else
#include "CWinStruct.h"

#endif

//20130828 MOD By Pothos
//#ifndef _WINDEF_
#ifndef HandsInkRecognizer_CWinStruct_h
// 2-D point with short coordinate
typedef struct tagPOINTS{
	short x;
	short y;
} POINTS, *PPOINTS;

// 2-D point with int coordinate
typedef struct tagPOINT{
	long x;
	long y;
} POINT, *PPOINT;
#endif

// 2-D point with int coordinate
typedef struct tagPOINTI{
	int x;
	int y;
} POINTI, *PPOINTI;

// a 2-D point with float coordinate
typedef struct tagPOINT2D{
	float x;
	float y;
	void operator=(POINTS point){ // from POINTS to POINT2D
		x=point.x;
		y=point.y;
	}
	void operator=(POINT point){ // from POINT to POINT2D
		x=float(point.x);
		y=float(point.y);
	}
	void operator=(POINTI point){ // from POINTI to POINT2D
		x=float(point.x);
		y=float(point.y);
	}
	operator POINTS(){   // from POINT2D to POINTS, you can use:
		POINTS tp;       // POINT2D pf={3.14, 1.5};
		tp.x=short(x);   // POINTS ps=pf; // or ps=POINTS(pf);
		tp.y=short(y);
		return tp;
	}
	operator POINT(){   // from POINT2D to POINT
		POINT tp;       
		tp.x=(x);
		tp.y=(y);
		return tp;
	}
	operator POINTI(){   // from POINT2D to POINTI
		POINTI tp;       
		tp.x=int(x);  
		tp.y=int(y);
		return tp;
	}
} POINT2D, *PPOINT2D;

// rectangular bound with edge parallel to coordinate axes
typedef struct tagBOUND{
	float left;
	float right;
	float top;
	float bottom;
} BOUND, *PBOUND;

// vector
typedef struct tagVECTOR{
	float x;
	float y;
} VECTOR, *PVECOTOR;

// line: Ax+By+C=0
typedef struct tagLINE{ 
	float A;
	float B;
	float C;
} LINE, *PLINE;

// directed line segment
typedef struct tagSEGMENT{
	POINT2D ps; // starting point
	POINT2D pt; // terminal point
} SEGMENT, *PSEGMENT;

// circle
typedef struct tagCIRCLE{ 
	POINT2D o;
	float r;
} CIRCLE, *PCIRCLE;


class CPoint2D;
class CVector;
class CLine;
class CSegment;
class CCircle;
class CBound;
class CCurve;
class CCurveSet;
class CPolygon;
class CTriangle;
class CConvexHull;
class CPtSet;


/////////////////////////////////////////////////////////////////////////////////////////////////
// Global functions                                   

// y downward, x rightward coordinate to y upward, x rightward coordinate: x'=x, y'=-y
void YDownToYUp(POINT2D& point);
void YDownToYUp(int nPtNum, POINT2D ptSet[]);
void YDownToYUp(int nCurveNum, int arrVNum[], POINT2D vertex[]);
// y upward, x rightward coordinate coordinate to y downward, x rightward: x'=x, y'=-y
void YUpToYDown(POINT2D& point);
void YUpToYDown(int nPtNum, POINT2D ptSet[]);
void YUpToYDown(int nCurveNum, int arrVNum[], POINT2D vertex[]);

// Euclidian distance
float Distance(POINT2D p1, POINT2D p2);
// swap two points
void swap(POINT2D p1, POINT2D p2);
// sort a point set according to the distances to a reference point o
void sort(int nPtNum, POINT2D ptSet[], POINT2D o);

// total least squares (TLS) line fitting
float TLSLineFit(int nPtNum, POINT2D ptSet[], VECTOR &dir, VECTOR &nor, POINT2D &mean, float &lambda1, float&lambda2);
// boundary points of a given parallel line family with normal nor
void BndPoints(int nPtNum, POINT2D ptSet[], VECTOR nor, int &idxp, int &idxn, float &dist);
// regression bound
CPolygon RSBound(int nPtNum, POINT2D ptSet[], VECTOR nor, float &width, float &height);



/////////////////////////////////////////////////////////////////////////////////////////////////
// Classes

/////////////////////////////////////////////////////////////////////////////
// CPoint2D - A 2-D point, similar to POINT2D structure.
class CPoint2D : public tagPOINT2D {
public:
// Constructors
	// create an uninitialized point
	CPoint2D();
	// create from two short integers
	CPoint2D(short initX, short initY);
	// create from two integers
	CPoint2D(int initX, int initY);
	// create from two float numbers
	CPoint2D(float initX, float initY);
	// create from two double numbers
	CPoint2D(double initX, double initY);
	// copy constructor: create from another point
	CPoint2D(POINT2D initPt);
	void operator=(POINT2D initPt);
	CPoint2D(POINTS initPt);
	void operator=(POINTS initPt);
	CPoint2D(POINT initPt);
	void operator=(POINT initPt);
	CPoint2D(POINTI initPt);
	void operator=(POINTI initPt);
	
// Operations
	bool operator==(POINT2D point) const;
	bool operator!=(POINT2D point) const;
	void operator+=(POINT2D point);
	void operator-=(POINT2D point);

// Operators returning CPoint2D values
	CPoint2D operator+(POINT2D point) const;
	CPoint2D operator-(POINT2D point) const;
	CPoint2D operator+(VECTOR vec) const;
	CPoint2D operator-() const;
	CPoint2D operator*(float scalar) const;
	CPoint2D operator/(float scalar) const;

// Functions
	CPoint2D Rotate(POINT2D o, float alpha) const;
	float DistTo(POINT2D point) const;
	float DistTo(LINE line) const;
	float DistTo(LINE line, POINT2D &point) const;
	float SgnDistTo(LINE line) const;
	float DistTo(SEGMENT seg) const; 
	float DistTo(SEGMENT seg, POINT2D& point) const;
	float DistTo(const CCurve &curve) const;
	float DistTo(const CCurve &curve, POINT2D &point) const;
	CPoint2D Projection(LINE line) const;
	float ProjRatio(SEGMENT seg) const;
	bool InRegion(CIRCLE circle) const;
	bool InRegion(BOUND bound) const;
	bool InRegion(const CPolygon &polygon) const;
	bool RelationTo(LINE line) const;
	bool RelationTo(SEGMENT seg) const;
	CPoint2D PointInDir(float dist, VECTOR dir) const;
};


/////////////////////////////////////////////////////////////////////////////
// CVector - A 2-D vector, similar to VECTOR structure.
class CVector: public tagVECTOR {
public:
// Constructors
	// construct an uninitialized vector
	CVector();
	// construct from two points
	CVector(POINT2D initPtTail, POINT2D initPtHead);
	// construct from directed line segment
	CVector(CSegment seg);
	// copy constructor: create from another vector
	CVector(VECTOR initVec);
	void operator=(VECTOR initVec);
	// radius vector (position vector): create from a point
	CVector(POINT2D initPt);

// Operations
	bool operator==(VECTOR vec) const;
	bool operator!=(VECTOR vec) const;
	void operator+=(VECTOR vec);
	void operator-=(VECTOR vec);

// Operators returning CVector values
	CVector operator+(VECTOR vec) const;
	CVector operator-(VECTOR vec) const;
	CVector operator-() const;

// Operators returning CPoint values
	CPoint2D operator+(POINT2D point) const;
	CPoint2D operator-(POINT2D point) const;

// Functions
	float operator^(VECTOR vec) const;
	float operator*(VECTOR vec) const;
	CVector operator*(float scalar) const;
	CVector operator/(float scalar) const;
	float Norm() const;
	float Argument() const;
	CVector OrthoVec() const;
	CVector Unit() const;
	CVector Projection(VECTOR vec) const;
	float DistTo(VECTOR vec) const;
	float AngleTo(VECTOR vec) const;	
};


/////////////////////////////////////////////////////////////////////////////
// CLine - A 2-D line, similar to LINE structure.
class CLine: public tagLINE {
public:	
// Constructors
	// construct an uninitialized line
	CLine();
	// construct from A, B, C
	CLine(float initA, float initB, float initC);
	// construct from two points
	CLine(POINT2D initPt1, POINT2D initPt2);
	// construct from a line segment
	CLine(SEGMENT initSeg);
	// construct from norm and a given point
	CLine(VECTOR norm, POINT2D point);
	// copy constructor: create from another line
	CLine(LINE initLine);
	void operator=(LINE initLine);

// Functions
	CVector Normal() const;
	CVector Direction() const;
	int RelationTo(LINE line, POINT2D& point) const;
	int RelationTo( CIRCLE circle, POINT2D& point1, POINT2D& point2 ) const;
	float AngleTo(LINE line) const;
	CLine Perpendicular(POINT2D point) const;
	CLine Perpendicular(POINT2D point, POINT2D& foot) const;
	CLine Parallel(POINT2D point) const;
};


/////////////////////////////////////////////////////////////////////////////
// CSegment - A 2-D line segment, similar to SEGMENT structure.
class CSegment: public tagSEGMENT {
public:	
// Constructors
	// construct an uninitialized segment
	CSegment();
	// construct from two points
	CSegment(POINT2D initPtS, POINT2D initPtT);
	// copy constructor: create from another segment
	CSegment(SEGMENT initSeg);
	void operator=(SEGMENT initSeg);

// operations
	CSegment operator-() const;

// Functions
	float Length() const;
	CPoint2D DivPoint(float ratio) const;
	CPoint2D Midpoint() const;
	CPoint2D SynDivPoint(float ratio) const;
	CLine Bisector() const;
	CPolygon Parallelogram(float len, VECTOR dir, int flag) const;
	CSegment Projection(LINE line) const;
	float DistTo(SEGMENT seg) const;
	float DistTo(SEGMENT seg, POINT2D &point1, POINT2D &point2) const;
	float DistTo(const CPolygon &polygon) const;
	bool Same(SEGMENT seg) const;
	bool RelationTo(SEGMENT seg) const;
	bool RelationTo(SEGMENT seg, POINT2D &point) const;
	int RelationTo(SEGMENT seg, VECTOR dir) const;
	bool RelationTo(const CCurve &curve) const;
	int RelationTo( CIRCLE circle, POINT2D &point1, POINT2D &point2 ) const;
	int InRegion(BOUND bound) const;
	int InRegion(const CPolygon& polygon) const;
};


/////////////////////////////////////////////////////////////////////////////
// CCircle - A circle, similar to CIRCLE structure.
class CCircle: public tagCIRCLE {
public:	
// Constructors
	// construct an uninitialized circle
	CCircle();
	// construct from center and radius
	CCircle(POINT2D initO, float initR);
	// construct from a segment (diameter)
	CCircle(SEGMENT initSeg);
	// construct from three points (not collineation)
	CCircle(POINT2D initPt1, POINT2D initPt2, POINT2D initPt3);
	// copy constructor: create from another circle
	CCircle(CIRCLE initCir);
	void operator=(CIRCLE initCir);
	
// Functions
};


/////////////////////////////////////////////////////////////////////////////
// CBound - A bound, similar to BOUND structure.
class CBound: public tagBOUND {
public:	
// Constructors
	// construct an uninitialized bound
	CBound();
	// construct from four edge coordinates
	CBound(float initLeft, float initRight, float initTop, float initBottom);
	// construct from two points
	CBound(POINT2D initPt1, POINT2D initPt2);
	// construct from a line segment (diagonal)
	CBound(SEGMENT initSeg);
	// copy constructor: create from another bound
	CBound(BOUND initBound);
	void operator=(BOUND initBound);

// Functions
	float Width() const;
	float Height() const;
	float LongSide() const;
	float ShortSide() const;
	float Diagonal() const;
	CPoint2D Center() const;
	bool RelationTo(BOUND bound) const;
	CBound Merge(BOUND bound) const;
};


/////////////////////////////////////////////////////////////////////////////
// CCurve - 2-D curve
class CCurve {
public:		
// Constructors
    // construct an uninitialized curve for derived class (derived 
    // class need a default construct function of base class)
    CCurve();
	// construct from points number and vertices
	CCurve(int initVNum, POINT2D initVertex[]);
	// construct from a polygon
	CCurve(const CPolygon &polygon);
	// copy constructor: create from another polygonal line
	CCurve(const CCurve& initCurve);
	void operator=(const CCurve& initCurve);

// Destructor
	~CCurve();

// Operations
	int GetVertexNum() const;
	CPoint2D GetVertex(int nIndex) const;
	void GetData(POINT2D vertex[]) const;
	void SetVertex(int nIndex, POINT2D point);
	
// Functions
	float Length() const;
	CBound Bound() const;
	float DistTo(const CCurve &curve) const;
	float DistTo(const CCurve &curve, POINT2D &point1, POINT2D &point2) const;
	bool RelationTo(const CCurve &curve) const;
	bool RelationTo(const CCurve &curve, POINT2D ptSet[], int segIdx1[], int segIdx2[], int &nPtNum) const;
	CCurveSet Cut(POINT2D ptSet[], int segIdx[], int &nPtNum) const;
	int InRegion(BOUND bound) const;
	int InRegion(const CPolygon &polygon) const;
	int InRegion(const CPolygon &polygon, float &len) const;
	
	// convex hull
	CConvexHull ConvexHull() const;

	// the following operations will change class member variable
	void Smooth();
	void Resample(float step);

protected:
	int m_nVNum;
	POINT2D* m_vertex;
};

/////////////////////////////////////////////////////////////////////////////
// CCurveSet - curve set
class CCurveSet {
protected:
	int m_nCurveNum;
	int *m_vtNums;
	POINT2D *m_vertex;
	int m_nPtNum;

public:
    // constructors
	CCurveSet();
	CCurveSet(int initCurveNum, int initVtNums[], POINT2D initVertex[]);
	CCurveSet(const CCurve &curve);
	CCurveSet(const CCurveSet &initCurveSet);
	void operator=(const CCurveSet &initCurveSet);

	// destructor
	~CCurveSet();

	// operations
	int GetCurveNum() const;
	int GetPtNum() const;
	void GetData(POINT2D vertex[]) const;
	CPtSet GetData() const;
	void GetData(int vtNums[], POINT2D vertex[]) const;
	CCurve GetCurve(int nIndex) const;
	CCurveSet GetSubSet(int index[], int nCurveNum) const;

	CCurve MinLenCur() const;
	CBound Bound() const;
	float Length() const; 
	CConvexHull ConvexHull() const;
	
	void RelationTo(const CCurve &curve, int index1[], int &num1, int index2[], int &num2) const;

	void Scale(float scale);
	void Shift(POINT2D shift);
	void LeftTopShift();
	void Rotate(POINT2D o, float alpha);
	void Normalize(float dim);
	void Smooth();
	void Resample(float step);
};

/////////////////////////////////////////////////////////////////////////////
// CPolygon - 2-D polygon
class CPolygon {
public:	
// Constructors
	// construct an uninitialized polygon for derived class (derived 
	// class need a default construct function of base class)
	CPolygon();
	// construct from points number and vertices
	CPolygon(int initVNum, POINT2D initVertex[]);
	// construct from a bound
	CPolygon(BOUND initBound);
	// construct from a curve
	CPolygon(const CCurve& initCurve);
	// copy constructor: create from another polygon
	CPolygon(const CPolygon& initPolygon);
	void operator=(const CPolygon& initPolygon);
	// construct from a convex hull
	CPolygon(const CConvexHull &initConvexHull);

// Destructor
	~CPolygon();

//Operations
	int GetVertexNum() const;
	CPoint2D GetVertex(int nIndex) const;
	void GetData(POINT2D vertex[]) const;
	void GetDataEx(POINT2D vertex[]) const;
	void SetVertex(int nIndex, POINT2D point);
	bool Degrade() const;

// Functions
	float Perimeter() const;
	float Area() const;
	CBound Bound() const;
	float DistTo(const CPolygon &polygon) const;
	bool RelationTo(const CPolygon &polygon, CPolygon &common) const;
	int InRegion(const CPolygon& polygon) const;

    // convex hull
	CConvexHull ConvexHull() const;

	void Rotate(POINT2D o, float alpha);

protected:
	int m_nVNum;
	POINT2D* m_vertex;
};


/////////////////////////////////////////////////////////////////////////////
// CTriangle - based on CPolygon.
class CTriangle: public CPolygon {
public:	
// Constructors
	// construct from three points
	CTriangle(POINT2D initPt1, POINT2D initPt2, POINT2D initPt3);

// Functions
};

/////////////////////////////////////////////////////////////////////////////
// Convex hull
class CConvexHull {
public:
// Constructor
	CConvexHull();
	// construct from point set
	CConvexHull(int nPtNum0, POINT2D ptSet0[]);
	// construct from a curve
	CConvexHull(const CCurve &curve);
	// construct from curve set
	CConvexHull(const CCurveSet &curveSet);
	// construct from a polygon
	CConvexHull(const CPolygon &polygon);
	// copy constructor
	CConvexHull(const CConvexHull& initHull);
	void operator=(const CConvexHull& initHull);

// destructor
	~CConvexHull();

//Operations
	int GetVertexNum() const;
	CPoint2D GetVertex(int nIndex) const;
	void GetData(POINT2D vertex[]) const;
	CPtSet GetData() const;

// Functions
	float Perimeter() const;
	float Area() const;
	CBound Bound() const;
	float MajorAxis(POINT2D &ptMaj1, POINT2D &ptMaj2) const; 
	float MinorAxis(POINT2D ptMaj1, POINT2D ptMaj2) const; 
	float MinorAxis() const;
	float Compactness(float dParameter, float dArea) const;
	float Eccentricity(float dMajorAxis, float dMinorAxis) const;
	float PrincipalAxis(float dMajorAxis, float dMinorAxis) const;
	float Rectangularity(float dMajorAxis, float dMinorAxis, float dArea) const;
	CPoint2D Centroid() const;
	float MeanRadius(POINT2D centroid) const;
	float CircularVariance(POINT2D centroid, float dMeanRadius) const;
	float NormCentroidOffset(POINT2D centroid, POINT2D ptMajor1, POINT2D ptMajor2) const;

	float DistTo(const CConvexHull &hull) const;

private:
	void GetConvexHull(int nPtNum, POINT2D ptSet[], int &nVNum, POINT2D convex[]);

private:
	int m_nVNum;
	POINT2D *m_vertex;
};

/////////////////////////////////////////////////////////////////////////////
// Convex hull
class CPtSet{
public:
	CPtSet();
	CPtSet(int nPtNum, POINT2D ptSet[]);
	CPtSet(const CPtSet& initPtSet);
	void operator=(const CPtSet& initPtSet);
	~CPtSet();

	int GetPtNum() const;
	void GetData(POINT2D ptSet[]) const;

	void DelIdPts();
	void Delete(int idx);
	void Sort();

	CPoint2D Centroid() const;
	float Divergence(LINE line) const;

private:
	int m_nPtNum;
	POINT2D *m_ptSet;
};

#endif /*_CGBASE_H_*/