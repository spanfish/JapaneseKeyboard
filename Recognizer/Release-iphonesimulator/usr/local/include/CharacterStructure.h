/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      CharacterStructure.cpp
�N���X��        CharacterStructure
���            ���`����N���X
�S����          �� �ɗ�

=============================================================================
����
05/05/30        ���`���쐬
05/05/30        �S���҂�D�c�����ɕύX
05/06/09        CharacterStructure�Ǘ��̃\�[�X���쐬
07/07/30		�����\���X�R�A�ɏd�݂�ǉ�
07/11/20        �ʒu���̊m���̌v�Z��ǉ�
07/11/26        CHARACTER_STRUCTURE_DICT�CCHARACTER_STRUCTURE_DICT_NEW�̒�`��
				�w�b�_�Ɉړ�(���̃\�[�X����Q�Ƃ���)by�D�c
07/12/16		����������CHARACTER_STRUCTURE_DICT_NEW�̃p�X��n���悤�ɕύX
=============================================================================
*/
//---------------------------------------------------------------------------
#ifndef CharacterStructureH
#define CharacterStructureH

//#include "InkDocument.h"
#include "InkPage.h"
//#include "CrLibXp.h"
#include "Crlibp2pcc.h"

#define INDEX_NUMBER 8883
#define MAX_CHARCTER_NUM 8238

#define CHARACTER_STRUCTURE_DICT "ja_JP_w_characterStructure.res"
#define CHARACTER_STRUCTURE_DICT_NEW "ja_JP_w_characterPosition.res"
//---------------------------------------------------------------------------
class CharacterStructureException
{
    private:

        // ��O�𔭐������s��
        int line;
        // ��O�𔭐������t�@�C����
        char * fileName;

    public:

        CharacterStructureException(int line, char *fileName)
        {
            this->line = line;
            this->fileName = fileName;
        }
        ~CharacterStructureException() throw(){ }
};
//---------------------------------------------------------------------------
enum SizeType{
	SmallCharacter 	 = 0,
	MiddleCharacter  = 1,
	BigCharacter     = 2
};
//---------------------------------------------------------------------------
enum PositionType{
	LowCharacter 	 = 0,
	NormalCharacter  = 1,
	HighCharacter    = 2
};
//---------------------------------------------------------------------------
class CharacterStructure
{
    private:

        char divisionNumber;
        unsigned char *patternInnerGaps[INDEX_NUMBER];
        int *patternSize[INDEX_NUMBER];
        int threshold;
        int powerThreshold;
        int lastThreshold;
        int PBW;
        int PBH;
		char *image;

		short index2DicIndex[MAX_CHARCTER_NUM];
		int categoryNum;
		int dim;
		double *vector;
		float *mean;
		double *eigv;

		void Initialize(const char *CharacterStructureDict,const char *CharacterStructureDictNew);
		void getInnerGap(RECT *strokeBound, int count, int *innerGap, PAT_POS boundingBox);
        void setInnerGap(int length, int size, char innerGapType, int psition, int *innerGap);
        void setStrokeBound(InkStroke *inkStroke, int count, RECT *strokeBound);
		bool isSpaceLeftTop(RECT &rect, int &bx, int &by);
		bool isSpaceLeftBottom(RECT &rect, int &bx, int &by);
		bool isSpaceRightTop(RECT &rect, int &bx, int &by);
		bool isSpaceRightBottom(RECT &rect, int &bx, int &by);
    	unsigned short coindex(unsigned char *s);
		double getPositionProbability(float *feature, unsigned short characterCode);

    public:
    
		bool IsEmpty;
        void GetProbability(InkStroke *inkStroke, int count,
			int averageSize, PAT_POS boundingBox,  int centerHigh,
			unsigned short *characterCode,
            double *characterScore, int candidateNumber = 10);
        bool PruneNode(InkStroke *inkStroke, int count, int averageSize);
		bool GetPosition(unsigned short code, float f[2]);
		bool GetSize(unsigned short code, double &w, double &h);
		PositionType GetPositionType(unsigned short code);
		SizeType GetSizeType(unsigned short code);

        CharacterStructure();
		CharacterStructure(char *CharacterStructureDict, char *CharacterStructureDictNew);
        ~CharacterStructure();
};
#endif
