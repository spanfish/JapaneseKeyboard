/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      Context.cpp
�N���X��        Context
���            ���������N���X
�S����          �� �ɗ�

=============================================================================
����
05/05/30        ���`���쐬
05/05/30        �S���҂�D�c�����ɕύX
05/06/09        ���������̃\�[�X���쐬
07/08/30        �������g�p�ʂ��팸���邽�ߕύX
07/12/09        �������̂��߂�log�Əd�ݕ������̌v�Z�������ɓ����

=============================================================================
*/

//---------------------------------------------------------------------------

#ifndef ContextH
#define ContextH
#include <vector>
using namespace std;

#if defined(WIN32)
#else
#include "MemoryMappedMode.h"
#define MAX_PATH 512
#endif
//#define CONTEXT_DICT  "nikei02ANDasahi93_small.tgr"
#define CONTEXT_DICT  "ja_JP_w_context.res"
//---------------------------------------------------------------------------
class ContextException
{
    private:

        // ��O�𔭐������s��
        int line;
        // ��O�𔭐������t�@�C����
        char * fileName;

    public:

        ContextException(int line, char *fileName)
        {
            this->line = line;
            this->fileName = fileName;
        }
        ~ContextException() throw(){ }
};

// AS K.Iwakura 2010/12/08
//---------------------------------------------------------------------------

#define SIZE_CONTEXT_DATA		20000000

typedef struct tagContextHead {
	int offsetWco;
	int offsetLico;
	int offsetLicoHead;
	int offsetCategoryNum;
    //	int offsetTotalNum;
	int offsetBiIndex;
	int offsetTriCategoryNum;
	int offsetTriWco;
	int offsetTriLico;
	int offsetTriIndex;
    
	int offsetProTable;
	int offsetBiProTable;
	int offsetUniProTable;
	int offsetUniProTableHead;
    
	int offsetWcpCode;
    
	int dataSize;
    
	short iCategoryNumber;
	int liTotalCount;
} ContextHead;

typedef struct tagContextData {
	ContextHead head;
	unsigned char data[1];
} ContextData;

// AE K.Iwakura 2010/12/08

//---------------------------------------------------------------------------
class Context
{
    private:
#if defined(MM_FILE_USE)
    int		hFile;
    int		map_size;
    //HANDLE		hMMMap;
#endif
#if defined(MM_FILE_WRITE) || defined(MM_FILE_READ) || defined(MM_FILE_USE)
    ContextData *pData;			// ADD K.Iwakura 2010/12/08
#endif
		unsigned short *wco;
		unsigned short *lico;
		unsigned short *licoHead;
		short *CategoryNum;
		int *TotalNum;
		unsigned int *biIndex;

		short *triCategoryNum;
		unsigned short *triWco;
		unsigned char *triLico;
		unsigned int *triIndex;

#if defined(MM_FILE_READ) || defined(MM_FILE_USE)
    float *proTable;			// CHG K.Iwakura 2010/12/08
    float *biProTable;			// CHG K.Iwakura 2010/12/08
#else
    float proTable[256];
    float biProTable[65536];
#endif
		float *uniProTable;
		float *uniProTableHead;
		float maxUniPro;
		float maxUniHeadPro;
		unsigned short maxBiId;
		unsigned short maxBiHeadId;
		unsigned char maxTriId;

		unsigned short *wcpCode;
        short iCategoryNumber;
		// Bigram �o�����̍��v
        int liTotalCount;

		vector<char> myContextFileName;

		void Initialize(const char *contextDict);
		int iSearch (unsigned short wcKey, unsigned short *wcTab, short num);
		int getBiProIndex(unsigned short firstWord, unsigned short secondWord);
		int getTriProIndex(unsigned short firstWord, unsigned short secondWord,
			unsigned short thirdWord);
		void deleteBiCharacter(int start, int end);
		void deleteTriCharacter(int start, int end, int max2);
		void freeDictionary();
		float getMaxId(float *table, int count);
		unsigned short getMaxId(float *table, unsigned short *idTable, int count);
		unsigned char getMaxId(float *table, unsigned char *idTable, int count);
		void registerWord(unsigned short firstWord, unsigned short secondWord, unsigned short thirdWord);
		int getPosition(unsigned short wcKey, unsigned short *wcTab, short num);
		int addTriCharacter(int iIndex2, unsigned short word);
		int addBiCharacter(int iIndex1, unsigned short word);
		int addUniCharacter(unsigned short word);

    public:
		bool IsEmpty;

		double GetUniProbability(unsigned short word);
		double GetBiProbability(unsigned short firstWord, unsigned short secondWord);
		double GetThreeProbability(unsigned short firstWord
            , unsigned short secondWord, unsigned short thirdWord);
		double GetProbability(unsigned short firstWord
			, unsigned short secondWord, unsigned short thirdWord);
		double GetProbability(unsigned short firstWord, unsigned short secondWord);
		void GetProbability(unsigned short firstWord
			, unsigned short secondWord, unsigned short thirdWord, double *probability);
		void DeleteCharacter(unsigned short word);
		void ExtractPartCharacters(unsigned short *word, int count);
		void SetRecognitionCode(const char *str);
		void WriteDictionary(const char *contextDict);
		void AttachDictionary(const char *contextDict);
		void DetachDictionary();
		void RegisterString(const char *str);

		Context();
        Context(const char *ContextDict);
        ~Context();
};
//---------------------------------------------------------------------------


#endif
