
/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      LatticeNode.h
�N���X��        LatticeNode
���            Lattice�f�[�^�N���X
�S����          ��ɗ�

=============================================================================
����
05/09/26        LatticeDocument.h���番��
07/07/30        Candidate�N���X�ǉ��CLatticeNode��candidate��Num��ǉ�  by ��
07/11/20        BaseNum�CIsCheckScore�CSegmentProbability�CIsTrue�CCenterHigh��ǉ� by ��
07/12/10        �m�[�h������ɍő剽���̃p�X���c�������������̂��߂̃f�[�^�ǉ� by ��
08/06/08        NoSegmentProbability�̒ǉ� by��
08/06/08  �@�@  �S���҂͐D�c�����֕ύX
=============================================================================
*/

#ifndef LatticeNodeH
#define LatticeNodeH


#include <stdio.h>
#include "Crlibp2pcc.h"
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
const int CANDIDATE_COUNT = 25;//20;//30;//60;//
const int MAX_PATH_COUNT = 20;//5;//20;//40;//
//---------------------------------------------------------------------------
// �m�[�h�̈ʒu
enum NodePosition
{
	LATTICE_HEAD = 0,
	LINE_HEAD    = 1,
	BLOCK_HEAD   = 2,
	ELEMENT      = 3,
	BLOCK_TAIL   = 4,
	LINE_TAIL    = 5,
	LATTICE_TAIL = 6,
	SINGLE_NODE_LATTICE = 7,
	SINGLE_NODE_LINE    = 8,
	SINGLE_NODE_UNIT    = 9
};
//---------------------------------------------------------------------------
class LatticeNode;  // ��ɐ錾���Ƃ��Ȃ���ViterbiFlag�ŎQ�Ƃł��Ȃ�
//---------------------------------------------------------------------------
class ViterbiFlag
{
public:
	LatticeNode *Path;
	int         Index;
	double      Probability;

	ViterbiFlag()
	{
		Path = NULL;
		Index = 0;
		Probability = -99999;
	}

	ViterbiFlag &operator=(const ViterbiFlag &flag)
	{
		Index = flag.Index;
		Probability = flag.Probability;
		Path = flag.Path;
		
		return *this;
	}
};
//---------------------------------------------------------------------------
class Candidate
{
public:
	Candidate 		**CandidateP;
	int		  	*SelectedIndex;
	double	  		*Probability;
	//int				*NodeNum;
	int 			*MaxPath;
	int			MaxPathNum;
	int       		Num;
	unsigned short  Code;
	LatticeNode 	*Node;
	int 		Index;

	Candidate()
	{
		Num = 0;
		MaxPathNum = 0;
	}
	~Candidate()
	{
		if(Num != 0)
		{
			delete []CandidateP;
			delete []SelectedIndex;
			delete []Probability;
			//delete []NodeNum;
			delete []MaxPath;
		}
	}
	Candidate &operator=(const Candidate &c)
	{
		MaxPathNum = c.MaxPathNum;
		int Num = Num;
		Code = c.Code;
		Index = c.Index;
		Node = c.Node;
		
		return *this;
	}
	void Free(void)
	{
		if(Num != 0)
		{
			delete []CandidateP;
			delete []SelectedIndex;
			delete []Probability;
			delete []MaxPath;
			//delete []NodeNum;
			MaxPathNum = 0;
		}
	}
};
//---------------------------------------------------------------------------
class LatticeNode
{
private:

public:
	// �Ώۂ̕��������p�^�[��
	int             Start;        // �����p�^�[���̐擪�X�g���[�N
	int             End;          // �����p�^�[���̏I�[�X�g���[�N�@
	int 			BaseNum;

	// �F������
	char            Result[CANDIDATE_COUNT * 2 + 2 + 1];
	// �F�����*10��+�m�蕶��+'\0'
	double          NoStructScore[CANDIDATE_COUNT + 1];
	double          Score[CANDIDATE_COUNT + 1];
	unsigned short  Code[CANDIDATE_COUNT + 1];
	int				Num;
	Candidate       candidate[CANDIDATE_COUNT];
	//double			EachScore[4 * CANDIDATE_COUNT];

	// ���`���
	// 05/05/31�ǉ�
	PAT_POS         BoundingBox;  // �O�ڋ�`
	PAT_POS         WritingBox;   // ������͘g
	double          AverageSize;  // ������s�̕��ϕ����T�C�Y
	//        (������@�͎d�l�����Q�l)
	bool			IsCheckScore;
	double			SegmentProbability;
	double			NoSegmentProbability;
	//bool			IsTrue;
	int			CenterHigh;

	// �m�[�h�̈ʒu
	NodePosition    Position;
	bool            Enabled;
	bool            IsLatticeHead;
	bool            IsLineHead;
	bool            IsBlockHead;
	bool            IsBlockTail;
	bool            IsLineTail;
	bool            IsLatticeTail;

	// �m�[�h�Ԃ̃p�X
	LatticeNode     **Prev;       // �O���̃����N
	int             PrevCount;
	// Wang: not used
	LatticeNode     **Next;       // ����̃����N
	int             NextCount;

	// DP�}�b�`���O�p�t���O     // ���O������ɂ����B���̂����ς���
	int             Tag;          // DP�}�b�`���O�p

	ViterbiFlag     Flag[CANDIDATE_COUNT + 1];

	int             SelectedIndex;
	// �F����₪�m�肵���ꍇ�̃t���O
	char            FixedCode[3];
	bool            IsFixed;

	// ���o�͊֐�
	istream&    Read(istream &in);
	ostream&    Write(ostream &out);

	friend ostream  &operator<<(ostream &stream, LatticeNode &latticeNode);
	LatticeNode         &operator=(const LatticeNode &latticeNode);

	LatticeNode(const LatticeNode &latticeNode);
	LatticeNode();
	~LatticeNode();

	//19 WANG
	bool IsSearch;
};
#endif
