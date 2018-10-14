/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      Recognizer.h
�N���X��        Recognizer
���            ������F���N���X
�S����          ��ɗ�

=============================================================================
����
05/05/08        �쐬
05/05/08        �쐬
05/06/13        OutGap�N���X, Context�N���X��ǉ�
05/06/20        SrResult�N���X��ǉ�
05/06/25        Back�֐����C��
05/11/07        searchNode�֐��ɂ�����LINE_HEAD�̊m����ǉ� by ��
07/05/02		�t�@�C���ۑ��ʒu�ύX�֐�(SupplyPath.h)�ɑΉ� by �D�c�C���c
07/07/20        �S���҂�D�c�����ɕύX
07/07/30		Trigram�̏�����ǉ�
07/08/17        �s�̊Ԃ������������s���悤�ɕύX
07/09/14        GetResult�֐��̃������m�ەύX
07/11/20        ������X�R�A�̌v�Z�ɗאڂ��镶���p�^���Ԃ̈ʒu���̊m�������邽�߁C
				BinaryFeature��ǉ�
07/11/27		SetWaitWithBounds�֐�, SetWaitWithoutBounds�֐���ǉ�
08/06/08        �F�������̏d�ݕϐ�q��2�����ɕύX
09/06/27		SetContextDictionary��ǉ�
=============================================================================
*/

#ifndef RecognizerH
#define RecognizerH

#include "ViterbiSolver.h"
#include "Context.h"
#include "BinaryFeature.h"
#include "SrResult.h"
#include "ArrayList.h"
#include <map>
using namespace std;

//---------------------------------------------------------------------------
const int SEARCH_COUNT = 1;
//---------------------------------------------------------------------------
class Recognizer : public ViterbiSolver
{
	private :
		SrResult    	   *mySrResult;
		double 		threshhold;
		double 		highestScore;

		// ���ۊ֐��̒�`
		void        searchNode(LatticeNode *node);
		void        back(LatticeNode *node);
		double      getProbability(LatticeNode *prevNode, int prevIndex,
								LatticeNode *currentNode, int currentIndex);
		char        *Result;
		void		recogAll(LatticeNode *current, LatticeNode *prev, int prevIndex,
						double score, string result, multimap<double, string> &m);

		void searchTrigramNode(LatticeNode *node);
		void searchTrigramNodeOne(LatticeNode *node);
		void backTrigram(LatticeNode *node);
		int searchPosition(double *highestScore, double score, int *check, int count);

		ArrayList<LatticeNode> result;
		ArrayList<unsigned short> codeResult;
		vector<char> myContextFileName;

	public :
		Context     *myContext;
		Context     *myOriginalContext;
		BinaryFeature      *myBinaryFeature;
		ArrayList<LatticeNode*> Node;
		bool 		IsEmpty;

		void        Recognize();
		void        RecognizeAll(const int index);
		void        Recognize(const int index);
		char        *GetResult();
		const LatticeNode *GetResultNode();
		int         GetResultNodeCount();
		SR_RESULT*  GetSrResult();

		void 		SetWaitWithBounds(double q[3][2]);
		void 		SetWaitWithoutBounds(double q[3][2]);
		void        SetContextDictionary(char *fileName);

		double		q[3][2], q1[3][2], q2[3][2];
		//double		TriThre;

        Recognizer();
        Recognizer(InkManager *ink, LatticeManager *lattice);
		void SetRecognitionCode(const char *str);
		void WriteDictionary(const char dicPathName[]);

        ~Recognizer();
};
//---------------------------------------------------------------------------
#endif
