/*************************************************************************
 Header file for algorithms
 Author: ZHOU XIANGDONG
 Updated: 2009.6
**************************************************************************/

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <errno.h>

// int pair
typedef struct tagINT_PAIR
{
	int i1;
	int i2;
} INT_PAIR, *PINT_PAIR;

//-----------------------------------------------------------------------------------------------------------------------------

void Insert(int &size, int *set, int e);
void Insert(int &size1, int *set1, int size2, int *set2);
bool InSet(int size, int *set, int e);
bool InOrdSet(int size, int *set, int e);
int PosInOrdSet(int size, double *set, double e);
int PosInOrdSet(int size, float *set, float e);
int PosInOrdSet(int size, int *set, int e);
void InsertOrd(int &size, double *set, double e);
void InsertOrd(int &size, double *set, double e, int BN);
void Sort(int size, int *set);
void Sort(int size, float *set);
int PosInsert(int &size, int *set, int e);
int PosInSet(int size, int *set, int e);
int MaxPos(int size, float *set);
int MinPos(int size, float *set);
float Max(int size, float *set);
float Min(int size, float *set);
int Max(int size, int *set);
int Min(int size, int *set);
void MaxMin(int size, int *set, int &maxv, int &minv);
bool EqOrdSet(int size1, int *set1, int size2, int *set2);
int OrdSetRelation(int size1, int *set1, int size2, int *set2);
void Swap(int &a, int &b);
bool Delete(int &size, int *set, int e);

void InsertPair(int &size, INT_PAIR *set, INT_PAIR pair);
bool EqPair(INT_PAIR pair1, INT_PAIR pair2);
void SwapPair(INT_PAIR &pair1, INT_PAIR &pair2);
void SortPair(int size, INT_PAIR *set, int flag);
bool RmvPair(int &size, INT_PAIR *set, int idx);

void SortTable( char *codetable, int nClassNum, short sCodeLen );
bool InTable( char *label, char *codetable, int nClassNum, short sCodeLen );
int PosInTable( char *label, char *codetable, int nClassNum, short sCodeLen );
void InsertTable( char *label, char *codetable, int &nClassNum, short sCodeLen );

bool ListFiles(char *dir, char **listfile, int &num, char *ext, bool full);
//void FileOpenCheck(errno_t err, char *szType);
void ErrExit(char *szErr);

int CombNum(int n, int m);
void GetCombs(int n, int m, int *combs, int &cn);
bool Change(int n, int m, int *a);
float GraphCut(float **mat, int N);
float GraphCut(float **mat, int N, int *index, int m);

int Random(int n);

#endif /* _UTILITY_H_ */
