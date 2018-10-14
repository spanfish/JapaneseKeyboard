/*
=============================================================================
ファイル名  UnitHandsInk.h
クラス名    HandsInk
解説        汎用文字列認識ライブラリ
担当者      朱碧蘭

=============================================================================
履歴
05/05/08    作成
07/07/18	限定文字認識機能を追加()
07/07/18	限定文字認識機能を追加(ReadWordList関数, 
			RecognizeWidthWordList関数, GetRecognitionResultWidthWordList関数)
07/11/20    認識処理の重み変数qを追加　by 朱
08/06/08    認識処理の重み変数qを削除　by 朱
08/06/08    担当者は織田から朱へ変更
09/06/27	SetContextDictionaryを追加
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
