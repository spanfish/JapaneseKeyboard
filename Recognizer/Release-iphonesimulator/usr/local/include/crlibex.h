/*
============================================================================

				crlib extension library header file

													Copyrighted by K.A

============================================================================
*/

#ifndef __CRLIBEX_H__

#define __CRLIBEX_H__

#include "crlib.h"

// �����_����
#define CA_DivideChar			1
#define CA_ReverseOrder			2
#define CA_KeepRatio			4
#define CA_ComparePos			8
#define CA_SmallChar			0x80

// �p�^�[������
#define CPA_LearnedPattern		0x40

// �F�����[�h
enum{ CR_WithCodeCategory = 0, CR_AllCategory, CR_UseFilter };

// �����J�e�S���e�[�u���T�C�Y
enum{ CR_MaxCategoryTableSize = 15000 };

// �F�����t�B���^�Ԃ�l
enum{
	CR_UseLtm = 1, CR_Reject = 0, CR_UseLtmAndDpm = -1, CR_UseDpm = -2
};

// �\���̒�`
typedef struct{
	PATTERN_B *pat;
	SHORT count;
} PATDIC;

struct tagCATEGORY;

typedef struct{
	int ctg_no;
	int x, y;
	int sx, sy;
} SUBCTG;

typedef struct{
	unsigned code;
	unsigned status;
	int sx, sy;
	SUBCTG subctg[2];
} CTGINFO;

typedef struct{
	PAT_POS pos;
	int ctg_no, pat_size;
	PATTERN_B inpd;
PATTERN_B inpd2;
PAT_POS pp;
	void *tmp_dic_data;
	void *npt_pair;
	void *table;
	void *reslink;
	CR_RESULT *res_buf;
	int res_count;
} CRSTATE;

typedef struct{
	int (*proc)(unsigned code, void *param);
	void *param;
} CRFILTER;

struct tagCATEGORY;

// �������
typedef struct{
	struct tagCATEGORY *part;
	BYTE pos, size;
} DIVINFO;

// �J�e�S�����
typedef struct tagCATEGORY{
	SHORT ctg_no;
	WORD code;
	BYTE status, size;
	DIVINFO div[2];
	PATDIC patdic;
} CATEGORY;

typedef struct{
	CATEGORY **ctg;
	int count;
	int maxctgtblsize;
	int maxpointcount;
} CRDIC;

typedef struct{
	int ctg_no;
	int pt_no;
	int pt_count;
} CRLEARNINFO;

typedef struct{
	int div_min_score;
} CRLEARNCFG;

#ifdef __cplusplus
extern "C" {
#endif

void GetCRLearnConfig(CRLEARNCFG *lc);
void SetCRLearnConfig(CRLEARNCFG *lc);
extern CRDIC _crdic;
// ���̓p�^�[�� pat �� ctg_no �Ɋw�K
int LearnCRDictionary(PATTERN_W *pat, int ctg_no, CRLEARNINFO *li);
// �w�K���ׂ������̏����擾
int GetCRLearnPart(PATTERN_W *pat, int ctg_no, CRLEARNINFO *li);
// �����p�^�[����o�^����
int RegistCRLearnPart(PATTERN_W *pat, CRLEARNINFO *li);

// �C�ӂ̎����p�^�[���Ƃ̗ގ��x�𓾂�
int GetPatternScore(PATTERN_W *pat, int ctg_no);

// �F���V�X�e�����g�p�ł���悤�ɂ���
int OpenCRSystem(const char dic_file[]);
// �F���V�X�e�����J������
void CloseCRSystem(void);

// �F�����s��
int RecognizeCP(PATTERN_W *in, CR_RESULT res[], int res_count);
// �o�b�N�O���E���h�F���̏������֐�
int InitBGRecognize(CRSTATE *crs,
		PATTERN_W *pat, CR_RESULT *res_buf, int res_count);
// �o�b�N�O���E���h�F�� (����������� 0 �ȊO)
int BGRecognizeCP(CRSTATE *crs, int match_count);

int RecognizeCPNew(PATTERN_W *id, int *score);
void BGRecognizeCPNew(CRSTATE *crs, int *score);
void SetFirstCandidate(short *candidate, int count);

// �o�b�N�O���E���h�F���̏I���֐�
void CloseBGRecognize(CRSTATE *crs);
// �}�b�`���O�̓r�����ʂ��ė��p���ĔF�����s���B���ݎg�p�s��
//int RecognizeCP2(PATTERN_W *in, CR_RESULT res[], int res_count);
// �g���C������p�����F�����s���B���ݎg�p�s��
// int TriRecognizeCP(PATTERN_W *in, CR_RESULT res[], int res_count);

// �V�t�g JIS �R�[�h�ɑΉ�����J�e�S���ԍ��𓾂�
int GetCategoryNo(unsigned code, int start_ctg_no);

// �J�e�S���̔񕪊��p�^�[���𓾂�
int GetCategoryPattern(PATTERN_B *pat, int ctg_no, int pat_no);
// �J�e�S���̔񕪊��p�^�[����ݒ肷��
int SetCategoryPattern(PATTERN_B *pat, int ctg_no, int pat_no);
// �J�e�S���̔񕪊��p�^�[����ǉ�����
int AddCategoryPattern(PATTERN_B *pat, int ctg_no, int pat_no);
// �J�e�S���̔񕪊��p�^�[�����폜����
int DeleteCategoryPattern(int ctg_no, int pat_no);
// �J�e�S���̔񕪊��p�^�[�����𓾂�
int GetCategoryPatternCount(int ctg_no);

// �J�e�S���̃p�^�[���𓾂�
int GetCharacterPatterns(PATDIC *pd, int ctg_no, int is_all);
// �J�e�S���̃p�^�[�����𓾂�
int GetCharacterPatternCount(int ctg_no);

// PATTERN_B �^�̃����o�z����J������
void FreePatternB(PATTERN_B *pat);
// �p�^�[���z����J������
void FreePatDic(PATDIC *pd);

// ctg1 �� ctg2 ���\���Ɋ܂ނ��ǂ������肷��
int IsIncludedCategory(int ctg1, int ctg2);
// �J�e�S�����𓾂�
int GetCategoryInfo(CTGINFO *ctg, int ctg_no);
// �J�e�S�������Z�b�g����
int SetCategoryInfo(CTGINFO *ctg, int ctg_no);
// �����J�e�S���e�[�u���̃T�C�Y�𓾂�
int GetCategoryCount(void);
// �����J�e�S���e�[�u���̃T�C�Y��ݒ肷��
int SetCategoryCount(int count);

// �����J�e�S����ǉ�����
int AddCategories(int ctg_no, int count);
// �����J�e�S�����폜����
int DeleteCategories(int ctg_no, int count);

// �������Z�[�u����
int SaveCRDictionary(const char fn[]);

// �F�����[�h�𓾂�
int GetCRMode(void);
// �F�����[�h��ݒ肷��
void SetCRMode(int mode);

// �F�����t�B���^��ݒ肷��
void SetCRPassFilter(int (*proc)(unsigned code, void *param), void *param);
// �F�����t�B���^�̐ݒ���擾����
void GetCRPassFilter(CRFILTER *crflt);
// ���_�t�B���^��ݒ肷��
void SetCRBonusFilter(int (*proc)(unsigned code, void *param), void *param);
// ���_�t�B���^�̐ݒ���擾����
void GetCRBonusFilter(CRFILTER *crflt);

// �������̑傫���̏����ݒ肷��
void SetSmallCharSize(int size);
// �����g��`��ݒ肷��
void SetGuideBoxRect(PAT_POS *pos);

// �F���������[�h
int LoadCRDictionary(const char fn[], CRDIC *dic);
// �F�������Z�b�g
void SetCRDictionary(CRDIC *dic, CRDIC *pre_dic);
// ���݂̎����𓾂�
void GetCRDictionary(CRDIC *dic);
// �������J������
void FreeCRDictionary(CRDIC *dic);

int setDic();
CRDIC getDic();
/*int MakePattern(CATEGORY *kj,
				PATDIC *patdic, int x, int y, int sx, int sy, int allflag);*/
#ifdef __cplusplus
}
#endif

#endif