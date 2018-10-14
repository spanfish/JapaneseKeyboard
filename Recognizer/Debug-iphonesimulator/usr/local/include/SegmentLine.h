/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      SegmentLine.h
�N���X��        SegmentLine
���            �菑����������s�P�ʂɕ�������N���X
�S����          ���� ���P

=============================================================================
����
05/05/08        ���`���쐬
05/05/11        �S���҂�D�c���珬���ɕύX
05/05/26        ��ʂ�̋@�\�������A�����������ω��_�Ȃ�
05/06/24		�����C��
05/06/24b		�o�b�t�@�I�[�o�[���C��
05/06/26		�o�b�t�@�I�[�o�[���C��
05/06/26b		���[�v�I�������̏������قȂ��Ă����̂ŏC��
05/09/23    	�X�g���[�N����0���Ɨ�����o�O���C�� by �D�c
05/11/05        ���σT�C�Y�̌v�Z�ŃX�g���[�N�T�C�Y�̌v�Z���@��ύX
 �@�@�@�@�@�@�@ �s�����������@��ύX by ��
				�S���҂����������ɕύX
07/05/02		���������N���X�̎����t�@�C�������w�肷��R���X�g���N�^��ǉ� by �D�c
07/11/27		Execute�֐��ɘg�L��F���̏ꍇ�̏�����ǉ� by �D�c
=============================================================================
*/

//---------------------------------------------------------------------------
#include "InkPage.h"
#include "SegmentCharacter.h"
#include "DetectLine.h"

#if defined(WIN32)
#else
typedef long LONG;
typedef short SHORT;
#endif

#ifndef SegmentLineH
#define SegmentLineH
//---------------------------------------------------------------------------
class SegmentLine
{
    protected:

    private:
        LONG charAveSize;
		DetectLine *detectLine;

        long GetAverageSize(InkStroke *inkStroke, int inkStrCount);
        long SetRetDetect(InkStroke *inkStroke, int inkStrCount, long aveSize);
        long SetCharacterOrientation(InkStroke *inkStroke, int inkStrCount, long aveSize);

        long EstimationCharacterOrientation(InkStroke *inkStroke, int inkStrCount, long aveSize);
        long RottationStroke(InkStroke *inkStroke, int inkStrCount, long aveSize, long Angle);
        long SetLineDirection(InkStroke *inkStroke, int inkStrCount, long aveSize);
	long SetRetDetect_Former(InkStroke *inkStroke, int inkStrCount, long aveSize);

		double getPointDistance(POINT& point1, POINT& point2);
		double getDistance(InkStroke *inkStroke, int count);
		void interpolation(InkStroke *inkStroke, int count);
		void writeDb1(char *fName, InkStroke *inkStroke, int count);

//        void GetLineRect(InkStroke *inkStroke, int inkStrCount, POINT *CenterPt, RECT *RectBox);

        //
        SHORT Enabled;

        //���σT�C�Y�p�z��
        LONG *AveSizeA;
        LONG AveSizeACount;
        LONG LineCount;

        //�t���O
        enum { m_DiviNum = 12};
        //�s�����̎w��(����������C�c��������C�M�L�������R etc)

        long SetLineAlpha(InkStroke *inkStroke, int inkStrCount, long aveSize);
        long SetLineAlpha_d1(InkStroke *inkStroke, int inkStrCount, long aveSize);
        LONG lGetOvelapRate(const RECT& rcBound1, const RECT& rcBound2, long dir);
        long SetLineAlpha_d2(InkStroke *inkStroke, int inkStrCount, long aveSize);
        long SetLineAlpha_d2a(InkStroke *inkStroke, int inkStrCount, long aveSize);
    
        void resamplePoint(vector<POINT> &points);
        void resampling(InkStroke *strokes, int strokeNum);
    
    public:
		SegmentCharacter *mySegCharacter;
        bool IsEmpty;
		LONG LastError;
		bool IsOneLine;
        void Execute(InkPage *inkPage);

    	int GetPageAvarageSize(InkPage *inkPage);
	    int GetLineCount();
    	int GetLineAvarageSize(InkStroke *inkStroke, int inkStrCount);

		SegmentLine();
		SegmentLine(char *fileName);
        ~SegmentLine();
};

#endif
