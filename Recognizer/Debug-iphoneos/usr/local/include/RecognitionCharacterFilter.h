/*
=============================================================================
�v���W�F�N�g��  HandsRecognizer
�t�@�C����      RecognitionCharacterFilter.h
�N���X��        RecognitionCharacterFilter
���            �F�������t�B���^�Ǘ��N���X
�S����          ��@�ɗ�

=============================================================================
����
11/11/21        �쐬
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
	ALL           = 0,	// �S����
	HIRAGANA      = 1,	// �Ђ炪��
	KATAKANA      = 2,	// �J�^�J�i
	ALPHABET      = 3,	// �A���t�@�x�b�g
	JIS1KANJI       = 4,	// JIS��ꐅ������
	JIS2KANJI      = 5,	// JIS��񐅏�����
	NUMERIC      = 6,	// ����
	SYMBOL       = 7,	// �L��
	GREEK         = 8,	// �M���V������
	PUNCTUATION = 9	// ��Ǔ_
}CharacterCategory;
//---------------------------------------------------------------------------
class RecognitionCharacterFilter
{
    private:

	public:

		// �J�e�S���t�B���^
		CharacterCategory Category;
		vector<unsigned short> Characters;

		RecognitionCharacterFilter(const unsigned short *codes, int count);
		RecognitionCharacterFilter(CharacterCategory category);

        RecognitionCharacterFilter();
        ~RecognitionCharacterFilter();
};
//---------------------------------------------------------------------------
#endif