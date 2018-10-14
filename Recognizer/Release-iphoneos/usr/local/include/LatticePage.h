/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      LatticePage.h
�N���X��        LatticePage
���            Lattice�f�[�^�N���X
�S����          ��ɗ�

=============================================================================
����
05/09/26        LatticeDocument.h���番��
                CreateLink�֐���LatticeManager�N���X����ړ�
05/09/28        Create�֐�,SetPosition���֐���LatticeManager�N���X����ړ�                
07/11/26		HasBounds�֐���ǉ�
08/06/08  �@�@  �S���҂͐D�c�����֕ύX
=============================================================================
*/

#ifndef LatticePageH
#define LatticePageH
#include "InkManager.h"
#include "LatticeBlock.h"
#include "TUATList.h"

#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
class LatticePage{
	private:
		void setBlock(LatticeBlock &prevBlock, LatticeBlock &block
			, SegmentStatus presentSegment, SegmentStatus nextSegment);
		void setBlockLink(LatticeBlock *pBlock, LatticeBlock *block);

		bool hasBounds;
	public:
		TUATList<LatticeBlock> Block;  // �u���b�N
		//double	TrueProbability[7];
		//int TrueCharterNum;
		//PAT_POS Rect[200];
		//unsigned short Code[200];

		bool HasBounds();

		void Create(InkPage *inkPage);
		void SetPosition(InkPage *inkPage);
		void CreateLink();

		istream&    Read(istream &in);
		ostream&    Write(ostream &out);

		friend ostream  &operator<<(ostream &stream, LatticePage &latticePage);
		LatticePage     &operator=(const LatticePage &latticePage);

        LatticePage(const LatticePage &latticePage);
        LatticePage();
        ~LatticePage();

	// Wang 2011-6-27
	int SearchPosition;
};
#endif
