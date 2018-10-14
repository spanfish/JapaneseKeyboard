/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      SrResult.h
�N���X��
���
�S����          ���� ���P

=============================================================================
����
05/06/14        �쐬
                �S���҂���������D�c�ɕύX
                GetRotateData�N���X�����ɍ쐬
05/06/20        �@�\�ǉ�
05/06/20a       �R���X�g���N�^�̌Ăяo�����s��ύX
05/09/26        InkManager�p�b�P�[�W�̎d�l�ύX�ɔ����ύX by �D�c
=============================================================================
*/
#ifndef SrResultH
#define SrResultH

#include "InkManager.h"
#include "LatticeManager.h"
#include <vector>

using namespace std;
//---------------------------------------------------------------------------
/* �ꕶ���������� */
typedef struct tagSR_ONECHAR
{
    BYTE Code[3];	//Word = Code[0]*0x100 + Code[1]; //Code[2] = '\0';
} SR_ONECHAR, *PSR_ONECHAR;
//---------------------------------------------------------------------------
typedef struct tagSR_CHARINFO
{
	LONG    lID;            //----- ��������ID
	BYTE    pCode[3];       //----- �����R�[�h
	PSR_ONECHAR pCands;     //----- �������
	LONG*   pCompStrokes;   //----- �����Ɋ܂܂��X�g���[�N�ԍ��̏W��
	LONG    lStrokeCount;   //----- �����Ɋ܂܂��X�g���[�N��
	LONG    lSkew;          //----- �����X�Ίp�x
	LONG    lDir;           //----- �s����
	POINT   ptBound[4];     //----- �O�ڋ�`
	POINT   ptSizChar;      //----- �T�C�Y
	POINT   ptCenter;       //----- ���S�_
} SR_CHARINFO, *PSR_CHARINFO;
//---------------------------------------------------------------------------
/* ���ʍs��� */
typedef struct tagSR_LINE
{
	LONG    lID;
	LONG*   lCharID;
	LONG    lSkew;          //----- �����X�Ίp�x
	LONG    lDir;           //----- �s����
	POINT   ptAveSiz;       //----- ���σT�C�Y
} SR_LINE, *PSR_LINE;
//---------------------------------------------------------------------------
/* ���ʕ����� */
typedef struct tagSR_RESULT
{
	LONG            lCharCount;
	BYTE*           pText;
	PSR_CHARINFO*   pChar;
	PSR_LINE*       pLine;
} SR_RESULT, *PSR_RESULT;

//---------------------------------------------------------------------------
class SrResult
{
    protected:
    private:
        InkManager  *myInk;
        POINT       Bound[4];
        POINT       SizChar;
        POINT       Center;
        SR_RESULT   result;
        long        pCharCount;
        long        pCharAddCount;
        long        pCharIndex;
        long        Direct;

        // �K���ɏ������̂ňꉞ�m�F���Ă�������
        PSR_CHARINFO getSR_CHARINFO(LatticeNode *node, int index);

        void InputStroke(InkStroke *inkStroke, int inkStrCount, LONG lSkew);
        void GetRotationBoundingBox(POINT ptBound[4], POINT *ptSizChar, POINT *ptCenter, long *Dir);
        void deleteSR_CHARINFO(SR_CHARINFO *charInfo);

        long CandidateSize;
        void Create(InkManager *ink);
    public:

        void Clear();
        void CreateSrResult();
        void AddCharInfo(LatticeNode *node, int index);
        SR_RESULT* GetResult();
        void SetInk(InkManager *ink);
        SrResult(InkManager *ink);
        SrResult();
        ~SrResult();
};
//ID���`����F
//    ����F�����̓��͏��ɂ��Ă���
//    �����ł̋�ʂɂ����g���Ă��Ȃ�(�����b�n���h��)
//    �I�u�W�F�N�g�̃|�C���^�ɂ��鎖���\

#endif