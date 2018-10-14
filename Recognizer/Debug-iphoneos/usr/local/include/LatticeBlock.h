/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      LatticeBlock.h
�N���X��        LatticeBlock
���            Lattice�f�[�^�N���X
�S����          ��ɗ�

  =============================================================================
  ����
  05/09/26        LatticeDocument.h���番��
  08/06/08  �@�@  �S���҂͐D�c�����֕ύX
  =============================================================================
*/

#ifndef LatticeBlockH
#define LatticeBlockH

#include <stdio.h>
#include "LatticeNode.h"
#include "ArrayList.h"
#include "InkStroke.h"
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
class SegmentPosition
{
public:
	int Start;
	int End;
	bool Changed;
	
	//15 WANG
	SegmentStatus Status;
	SegmentStatus pSegment;
	SegmentPosition(int start, int end)
	{
		Start = start;
		End   = end;
		pSegment = COMBINE;
		Status = NEW_LINE;
	}
	SegmentPosition(int start, int end, SegmentStatus p, SegmentStatus s)
	{
		Start = start;
		End   = end;
		pSegment = p;
		Status = s;
	}
};
//---------------------------------------------------------------------------
class LatticeBlock 
{
public:
	//16 Wang
	//LatticeNode    **Node;          // *Data���ϒ��񎟌��z���
	ArrayList<LatticeNode *> Node;
	//LatticeNode    *Data;           // �������̃f�[�^
	ArrayList<LatticeNode> Data;	// Wang
	//int            dLength;         // Data�̐�
	//int            nLength;         // �߂̐�
	//int            *nCount;         // �e�߂̃m�[�h�̐�
	ArrayList<int> nCount;
	
	void Create(SegmentPosition *segment, int nLength, ArrayList<InkStroke> &stroke);
	void Modify(SegmentPosition *segment, int nLength, int pLength, ArrayList<InkStroke> &stroke);
	LatticeBlock Split(SegmentPosition *segment, int first_length, bool remain, ArrayList<InkStroke> &stroke);
	LatticeBlock         &operator=(const LatticeBlock &latticeBlock);

	// ���o�͊֐�
        istream&    Read(istream &in);
        ostream&    Write(ostream &out);
	
        friend ostream  &operator<<(ostream &stream, LatticeBlock &latticeBlock);

	LatticeBlock(const LatticeBlock &latticeBlock);
	LatticeBlock();
	~LatticeBlock();
};
//---------------------------------------------------------------------------
#endif
