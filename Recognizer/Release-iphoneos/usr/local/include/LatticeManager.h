/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      LatticeManager.h
�N���X��        LatticeManager
                LatticeDocument
                LatticePage
                LatticeBlock
                LatticeNode
���            Lattice�f�[�^�Ǘ��N���X
                Lattice�f�[�^�N���X
�S����          ��ɗ�

=============================================================================
����
05/05/08        �쐬
05/05/31        LatticeNode�N���X��BoundingBox�ϐ��CWritingBox�ϐ�,
                AverageSize�ϐ���ǉ�
                LaticeDocument�N���X�ȉ���LatticeDocument.h�t�@�C���ɕ���
                Lattice�f�[�^�N���X�Q��LatticeDocument.h�ɕ���
05/06/10        ���̃����o��ǉ�
                    SegmentLine�N���X�CCharacterStructure�N���X
                    LineStructure�N���X�CCharacterRecognizer�N���X
                    segment�֐��CCreateLattice�֐��CCreateBlock�֐�
05/06/23        ���̃����o��ǉ�
                    IsLatticeHead�ϐ��CIsLineHead�ϐ�, IsBlockHead�ϐ�
                    IsLatticeTail�ϐ��CIsLineTail�ϐ�, IsBlockTail�ϐ�
                CreateLink�֐���O�������N����������悤�ɉ���
05/06/24        �������𐶐�����ʒu��ύX
05/06/25        CreateLink�֐��̃o�O���C��
05/09/11        InkManager�p�b�P�[�W�̕ύX�ɔ����C��
05/09/26        LatticeDocument�N���X���폜
                ArrayList<LatticePage>�N���X��ǉ�
                CreateLink�֐���LatticePage�N���X�ֈړ�
05/09/28        Create�֐�,SetPosition���֐���LatticePage�N���X�ֈړ�
07/11/20        �F�������̏d�ݕϐ�q��ǉ��@
				myLineStruct���폜 by ��
07/11/26		rotatedInk�������폜(�����C���^�t�F�[�X�͂��΂炭���Ȃ�)
07/11/27		SetWaitWithBounds�֐�, SetWaitWithoutBounds�֐���ǉ�
08/06/08        �F�������̏d�ݕϐ�q��2�����ɕύX
08/06/08  �@�@  �S���҂͐D�c�����֕ύX
=============================================================================
*/
#ifndef __LATTICEMANAGER_H_
#define __LATTICEMANAGER_H_

#include "LatticePage.h"
#include "InkManager.h"
#include "SegmentLine.h"
#include "CharacterStructure.h"
#include "CombinationRecognizer.h"

#include "ArrayList.h"


//const int CANDIDATE_COUNT = 10;
const int FrameRatio = 2;          // �O�ڋ�`�̏c���� 1:FrameRatio
//---------------------------------------------------------------------------
class LatticeManager
{
	private:
		// �@�\�N���X
		SegmentLine         *mySegment;
		short				topLine;
		short				baseLine;
		bool				isSetGuideLines;

		//InkManager          *rotatedInk;

		// ���e�B�X�����֐�
		void createPage(LatticePage *latticePage, InkPage *inkPage);
		void getRecognitionCandidate(LatticePage *latticePage,
															InkPage *inkPage);
		unsigned short getCode(char *code);
		bool stored(PAT_POS bounds, InkStroke *stroke, int count);

	public:
		bool                isEmpty;
		bool				isHasDic;
		InkManager          *Ink;
		CharacterStructure  *myCharStruct;
		double	q[6][2], q1[6][2], q2[6][2];
		//TProgressBar 		*ProgressBar;
		//double 				ScoreThre;
		//int 	CorrectScore[1000];
		//int 	MisScore[1000];
		bool IsCheck;

		void		SetQ(double q[6][2]);
		void 		SetWaitWithBounds(double q[6][2]);
		void 		SetWaitWithoutBounds(double q[6][2]);
		void		SetOneLineRecognition(bool isOneLine);
		void		SetGuideLines(short topLine, short	baseLine);
		void SetHeavySegmentation(bool isHeavySegmentation);
		
		void OneCharacterRecognize(InkStroke *pStroke, int count, 
										    PAT_POS &writtingBox, PAT_POS &bound, char *candidate, 
										  unsigned short *code, double *score);

		//CharacterRecognizerAdapter *Recognizer;
		CombinationRecognizer *Recognizer;
		ArrayList<LatticePage> Page;

		// ���e�B�X�����E�����֐�
		void        Create();
		void        Clear();
		bool        IsEmpty();

		// �t�@�C�����o�͊֐�
		bool        ExportToFile(const char *fileName, const int index);
		bool        SaveToFile(const char *fileName);
		bool        LoadFromFile(const char *fileName);
		bool		AddFromFile(const char *fileName);

		// �����C���^�t�F�[�X�p�֐�
		void        SelectNode(int page, int start, int end);
		void        SetAngle(int page, int start, int end, double angle);
		void        SetCode(int page, int start, int end, char *code);
		void        ReplaceStroke(int page, int start, int end,
												InkStroke *stroke, int count);

		void        RecreateLatticePage(int page);

		void 		Create(int index);

		void		UpdateLatticeResult(int index, const LatticeNode *result, int nResult);

		LatticeManager();
		LatticeManager(InkManager *ink);
		~LatticeManager();
};
//---------------------------------------------------------------------------
#endif


