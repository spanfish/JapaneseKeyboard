/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      ViterbiSolver.cpp
クラス名        ViterbiSolver
解説            Viterbiアルゴリズム用抽象クラス
担当者          織田英人

=============================================================================
履歴
05/05/08        作成
05/09/28        Clear関数、IsEmpty関数、SetInk関数を削除
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
