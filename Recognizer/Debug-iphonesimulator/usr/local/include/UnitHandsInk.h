/*
=============================================================================
�t�@�C����  UnitHandsInk.h
�N���X��    HandsInk
���        �ėp������F�����C�u����
�S����      ��ɗ�

=============================================================================
����
05/05/08    �쐬
07/07/18	���蕶���F���@�\��ǉ�()
07/07/18	���蕶���F���@�\��ǉ�(ReadWordList�֐�, 
			RecognizeWidthWordList�֐�, GetRecognitionResultWidthWordList�֐�)
07/11/20    �F�������̏d�ݕϐ�q��ǉ��@by ��
08/06/08    �F�������̏d�ݕϐ�q���폜�@by ��
08/06/08    �S���҂͐D�c�����֕ύX
09/06/27	SetContextDictionary��ǉ�
=============================================================================
*/

//---------------------------------------------------------------------------
#include "InkManager.h"
#include "LatticeManager.h"
#include "Recognizer.h"

#ifndef UnitHandsInkH
#define UnitHandsInkH
//---------------------------------------------------------------------------
class HandsInk
{
    private:

    public:

        InkManager       *Ink;
        LatticeManager   *Lattice;
        Recognizer       *myRecognition;
		bool			 IsEmpty;

		Context* SetContext(Context *context);
		void SetInk(InkManager *ink);

        HandsInk();
        ~HandsInk();
};
#endif
