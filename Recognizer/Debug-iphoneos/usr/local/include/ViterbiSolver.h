/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      ViterbiSolver.cpp
�N���X��        ViterbiSolver
���            Viterbi�A���S���Y���p���ۃN���X
�S����          �D�c�p�l

=============================================================================
����
05/05/08        �쐬
05/09/28        Clear�֐��AIsEmpty�֐��ASetInk�֐����폜
=============================================================================
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "InkManager.h"
#include "LatticeManager.h"
//#include "..\LatticeManager\CharacterRecognizer\CombinedRecognizer\CharacterRecognizer.h"
//#include ".\LatticeManager\HandsCharacterRecognizer\OnLineRecognizer\CrlibXPDll\Crlibp2pcc.h"

#define ArrayLength 1024
//---------------------------------------------------------------------------
#ifndef __VITERBISOLVER_H_
#define __VITERBISOLVER_H_

//---------------------------------------------------------------------------
class ViterbiSolver
{
    private:

    protected:
        int     processingPageIndex;

        void    Execute();
        void    Execute(const int index);
        void    SearchLattice(LatticePage *page);
        virtual void    searchNode(LatticeNode *node) = 0;
        virtual void    back(LatticeNode *node) = 0;

    public:
        InkManager     *Ink;
        LatticeManager *Lattice;

        ViterbiSolver();
        ViterbiSolver(InkManager *ink, LatticeManager *lattice);
        virtual ~ViterbiSolver() { };
};
//---------------------------------------------------------------------------
#endif
