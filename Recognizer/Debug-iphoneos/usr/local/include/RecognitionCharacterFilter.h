/*
=============================================================================
プロジェクト名  HandsRecognizer
ファイル名      RecognitionCharacterFilter.h
クラス名        RecognitionCharacterFilter
解説            認識文字フィルタ管理クラス
担当者          朱　碧蘭

=============================================================================
履歴
11/11/21        作成
=============================================================================
*/

#ifndef RecognitionCharacterFilterH
#define RecognitionCharacterFilterH
#include <stdio.h>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------
typedef enum tagCharacterCategory
{
	ALL           = 0,	// 全字種
	HIRAGANA      = 1,	// ひらがな
	KATAKANA      = 2,	// カタカナ
	ALPHABET      = 3,	// アルファベット
	JIS1KANJI       = 4,	// JIS第一水準漢字
	JIS2KANJI      = 5,	// JIS第二水準漢字
	NUMERIC      = 6,	// 数字
	SYMBOL       = 7,	// 記号
	GREEK         = 8,	// ギリシャ文字
	PUNCTUATION = 9	// 句読点
}CharacterCategory;
//---------------------------------------------------------------------------
class RecognitionCharacterFilter
{
    private:

	public:

		// カテゴリフィルタ
		CharacterCategory Category;
		vector<unsigned short> Characters;

		RecognitionCharacterFilter(const unsigned short *codes, int count);
		RecognitionCharacterFilter(CharacterCategory category);

        RecognitionCharacterFilter();
        ~RecognitionCharacterFilter();
};
//---------------------------------------------------------------------------
#endif