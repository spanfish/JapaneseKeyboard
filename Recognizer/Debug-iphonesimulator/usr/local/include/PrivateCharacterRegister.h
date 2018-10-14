/*
=============================================================================
�v���W�F�N�g��  PrivateCharacterRegister
�t�@�C����      PrivateCharacterRegister.h
�N���X��        PrivateCharacterRegister
���            �O���o�^�N���X
�S����          ��ɗ�
=============================================================================
����
09/11/02        �쐬
=============================================================================
*/

#ifndef PrivateCharacterRegisterH
#define PrivateCharacterRegisterH

#if defined(WIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include "PatternTransformer.h"
#include "MRFOnlineRecognizer.h"
#include "MQDFRecognizer.h"
//#include "MakeOnlineRecogDictionary.h"//�g��Ȃ��N���X
#include "Matrix.h"
#include "OnLinePatternProcesser.h"
#include "RecognitionCharacterFilter.h"

using namespace std;

#define PrivateCount 1890

//---------------------------------------------------------------------------
/*enum CharacterCategory
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
};*/
//---------------------------------------------------------------------------
struct PrivateStroke
{
	POINT           *Points;// �X�g���[�N�̕M�_��
    int             Count; // �X�g���[�N�M�_��̐�
	PrivateStroke()
	{
		Points = NULL;
		Count = 0;
	}
	~PrivateStroke(void)
	{
		if(Count > 0) 
		{
			delete []Points;
			Count = 0;
		}
	}
	void Free(void)
	{
		if(Count > 0) 
		{
			delete []Points;
			Count = 0;
		}
	}
	PrivateStroke &operator=(const PrivateStroke &stroke)
	{
		Free();
		if(stroke.Count == 0) return *this;
		Count = stroke.Count;
		Points = new POINT[Count];
		memmove(Points, stroke.Points, sizeof(POINT) * Count);
		return *this;
	}
	void Write(FILE* fp)
	{
		if(fp == NULL) return;
		fwrite((char *)&Count, sizeof(int) * 1, 1, fp);
		if(Count == 0) return;
		fwrite((char *)Points, sizeof(POINT) * Count, 1, fp);
	}
	void Read(FILE* fp)
	{
		if(fp == NULL) return;
		Free();
		fread((char *)&Count, sizeof(int) * 1, 1, fp);
		if(Count == 0) return;
		Points = new POINT[Count];
		fread((char *)Points, sizeof(POINT) * Count, 1, fp);
	}
};
//---------------------------------------------------------------------------
struct PrivateCharacter
{
	PrivateStroke    *Strokes; // �����p�^���̃X�g���[�N
    int               Count;   // �����p�^���̃X�g���[�N�̐�
   	unsigned short    Code;     // �����R�[�h
	CharacterCategory Category;	// �o�^����̃J�e�S��
	PrivateCharacter()
	{
		Strokes = NULL;
		Count = 0;
	}
	~PrivateCharacter(void)
	{
		if(Count > 0) 
		{
			delete []Strokes;
			Count = 0;
		}
	}
	void Free(void)
	{
		if(Count > 0) 
		{
			delete []Strokes;
			Count = 0;
		}
	}
	PrivateCharacter &operator=(const PrivateCharacter &character)
	{
		Free();
		if(character.Count == 0) return *this;
		Count = character.Count;
		Code = character.Code;
		Category = character.Category;
		Strokes = new PrivateStroke[Count];
		for(int i = 0; i < Count; i++) Strokes[i] = character.Strokes[i];
		return *this;
	}
	void Write(FILE* fp)
	{
		//MessageBox(NULL, "Write Charcter", "", MB_OK);
		if(fp == NULL) return;
		fwrite((char *)&Count, sizeof(int) * 1, 1, fp);
		fwrite((char *)&Code, sizeof(unsigned short) * 1, 1, fp);
		fwrite((char *)&Category, sizeof(CharacterCategory) * 1, 1, fp);

		//char str[100];
		//sprintf(str, "%d, %.4x, %d", Count, Code, Category);
		//MessageBox(NULL, str, "", MB_OK);
		for(int i = 0; i < Count; i++) Strokes[i].Write(fp);
	}
	void Read(FILE* fp)
	{
		if(fp == NULL) return;
		Free();
		fread((char *)&Count, sizeof(int) * 1, 1, fp);
		fread((char *)&Code, sizeof(unsigned short) * 1, 1, fp);
		fread((char *)&Category, sizeof(CharacterCategory) * 1, 1, fp);
		if(Count == 0) return;
		Strokes = new PrivateStroke[Count];
		for(int i = 0; i < Count; i++) Strokes[i].Read(fp);
	}
};
//---------------------------------------------------------------------------
struct RegisteredPrivateCharacter
{
	PrivateCharacter  *Character; // �o�^�ς݂̊O��
    int                Count;     //�o�^�ς݂̊O���̐�

	RegisteredPrivateCharacter()
	{
		Character = NULL;
		Count = 0;
	}
	~RegisteredPrivateCharacter(void)
	{
		if(Count > 0) 
		{
			delete []Character;
			Count = 0;
		}
	}
	void Free(void)
	{
		if(Count > 0) 
		{
			delete []Character;
			Count = 0;
		}
	}
	void Add(PrivateCharacter &character)
	{
		PrivateCharacter *charP = new PrivateCharacter[Count+1];
		for(int i = 0; i < Count; i++)
			charP[i] = Character[i];
		delete []Character;
		Character = charP;
		Character[Count] = character;
		Count++;
	}
	void Add(PrivateCharacter *character, int count)
	{
		PrivateCharacter *charP = new PrivateCharacter[Count+count];
		int i;
		for(i = 0; i < Count; i++)
			charP[i] = Character[i];
		delete []Character;
		Character = charP;
		for(i = 0; i < count; i++)
		{
			Character[Count] = character[i];
			Count++;
		}
	}
	int GetId(unsigned short code)
	{
		for(int i = 0; i < Count; i++)	
			if(Character[i].Code == code) return i;
		return -1;
	}
	void Delete(int id)
	{
		if(id < 0 || id > Count) return;
		PrivateCharacter *charP = new PrivateCharacter[Count-1];
		int k = 0;
		int i;
		for(i = 0; i < id; i++)
			charP[k++] = Character[i];
		for(i = id + 1; i < Count; i++)
			charP[k++] = Character[i];
		delete []Character;
		Character = charP;
		Count--;
	}

	void Write(FILE* fp)
	{
		if(fp == NULL) return;
		fwrite((char *)&Count, sizeof(int) * 1, 1, fp);
		for(int i = 0; i < Count; i++) Character[i].Write(fp);
	}
	void Read(FILE* fp)
	{
		if(fp == NULL) return;
		Free();
		fread((char *)&Count, sizeof(int) * 1, 1, fp);
		if(Count == 0) return;
		Character = new PrivateCharacter[Count];
		for(int i = 0; i < Count; i++) Character[i].Read(fp);
	}
};
//---------------------------------------------------------------------------
class PrivateCharacterRegister
{
	private:
		short intMn[300];	// inter mean vector
		int intEig[300];		// integer eigen values
		int intVar;		// interger variance
		short* intVec;
		PatternTransformer *transformer;
		//MakeOnlineRecogDictionary *makeOnlineDic;
		CMatrix theMat;
		MRFOnlineRecognizer *onLine;
		MQDFRecognizer *offLine;
		RegisteredPrivateCharacter privateCharacter;

		void setPrivateCharacter(PrivateCharacter &character, Pattern &pattern
					, unsigned short code, CharacterCategory category);
		bool isPrivateCharacter(unsigned short code);
		bool registerOnLine(Pattern *pat, int count, unsigned short code);
		bool unregisterOnLine(unsigned short code);
		bool registerOffLine(Pattern *pat, int count
					, unsigned short code, const CharacterCategory category);
		bool unregisterOffLine(unsigned short code);

		void covariance( float* data, int sampNum, int dim, double** C );
		double variance( short* data, int sampNum
										  , int dim, float* mean, float* fdata );
		void learning( CMatrix* pMat, short *data, int dim, int trainNum);
		//void transformToPattern(PATTERN_W &m_patw, Pattern &pat);
		//void setOnlinePat(Pattern &pattern, PATTERN_W &m_patw);
		//void setPatternBounding(Pattern &pattern);
		short coindex(unsigned short code);
		void setCategory(void);

		bool registerOffLine(Pattern *pat, int count, unsigned short code);
		bool registerOnLineTemplate(Pattern *pat, int count, unsigned short code);
		bool registerOffLine(Pattern *pat, int count
					,unsigned int UTF8code, unsigned short code);

	public:

		bool IsEmpty;
		CharacterCategory CategoryCode[PrivateCount];

		bool Register(PATTERN_W &ptw, unsigned short code
										, const CharacterCategory category);
		bool Unregister(unsigned short code);
		const RegisteredPrivateCharacter* GetRegister(void);
		void ExtractPartCharacters(void);
		bool WriteDictionary(const char dicPathName[]);

		bool RegisterTemplate(PATTERN_W &ptw, unsigned short code);
		bool Register(PATTERN_W &ptw, unsigned int UTF8code, unsigned short code);

		PrivateCharacterRegister(MRFOnlineRecognizer *onLine
									, MQDFRecognizer *offLine);
		~PrivateCharacterRegister();
};
//---------------------------------------------------------------------------
#endif
