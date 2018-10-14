/*
=============================================================================
�v���W�F�N�g��  Sorter
�t�@�C����      Sorter.h
�N���X��        Sorter
���            sort
�S����          ��ɗ�
=============================================================================
����
10/11/25        �쐬
=============================================================================
*/

#ifndef SorterH
#define SorterH

#include <stdio.h>

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
struct SortNode
{
	int id;
	double v;
	SortNode *left;
	SortNode *right;
	SortNode *par;
	
	SortNode()
	{
		left = NULL;
		right = NULL;
		par = NULL;
	}
};
//---------------------------------------------------------------------------
struct HashNode
{
	int id;
	HashNode *next;
	
	HashNode()
	{
		next = NULL;
	}
};
//---------------------------------------------------------------------------
class Sorter
{
	private:

		SortNode *node;
		int rankNum;

    public:

		SortNode *Root, *Left, *Right;

		void ResetSortNode(int count);
		void ClearSortNode();
		void InsertNode(double dist, int k, int &count);
		void SetScore(SortNode *node, double *dmin, int *index, int &i);
		void SetIndex(SortNode *node, int *index, int &i);
		void PrintNode(SortNode *node);

		int FastSortHash(short *index, int *score, int preCount, int count);
		int FastSortHashNode(short *index, int *score, int preCount, int count);
		int FastSortHash(short *index, double *score, int preCount, int count);
		int FastSortHashNode(short *index, double *score, int preCount, int count);
	
		Sorter();
		~Sorter();
};
//---------------------------------------------------------------------------
#endif