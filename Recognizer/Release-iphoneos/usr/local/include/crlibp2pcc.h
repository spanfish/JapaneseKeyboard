// Crlibp2p�ɑ啪�ނ������Ă݂悤�I�o�[�W����

#ifndef __CRLIBP2PCC_H__

#define __CRLIBP2PCC_H__

#define USE_CC//�啪�ގg�p���͒�`����

#ifdef USE_CC

//#include "ctclass.h"//ak.�啪�ޗp�ɒǉ�
#include "comclas3.h"//ak.�啪�ޗp�ɒǉ�
#include "crlibex.h"
#endif

#ifdef __BORLANDC__
#define EXPVAR __pascal

#else
#define EXPVAR

#endif
//20150323ADD
#define __stdcall

//���펯�ʗp
#define RK_Hiragana 1
#define RK_Katakana 2
#define RK_Alphabet 4
#define RK_Jis1Kanji 8
#define RK_Jis2Kanji 16
#define RK_Numeric 32	//ak@����
#define RK_Symbol 64	//ak@�L��
#define RK_Greek 128
#define RK_Punctuation 256	//ak@��Ǔ_

#define RK_AllCategory (RK_Hiragana \
			| RK_Katakana \
			| RK_Alphabet \
			| RK_Jis1Kanji \
			| RK_Jis2Kanji \
			| RK_Numeric \
			| RK_Symbol \
			| RK_Greek \
			| RK_Punctuation \
			)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef USE_CC
/*�Q�l�܂ł� from ComClass3.h
typedef struct{
	SHORT *linktbl;
	SHORT *hashtbl;
} CANDTBL;		*/

//�啪�ޗp�\����
typedef struct{
	WORD *code;
	int count;
	CANDTBL ct;
	int rank;
	int mflag;
} CCINFO;
#endif //#ifdef USE_CC

//�ÓI�Ȑ錾���O���Ɍ��J����ꍇ�͈ȉ��̗l�ɍs��
//extern __declspec(dllexport) int EXPVAR VAR;

/////////////////////////�F����{�֐��Q//////////////////////////////

//�F���V�X�e���̏�����
int __stdcall D_OpenOnCrRecSystem(const char dic_file[]);
//�t�@�C���̃N���[�Y
void __stdcall D_CloseOnCrRecSystem();
//�����F�����s
int __stdcall D_OnCrRecognize(
											PATTERN_W *in, CR_RESULT res[], int res_count);
//�啪�ގ��s
int __stdcall D_CoarseClassify(PATTERN_W *pat, WORD *cands, long *dist, int num);
//�����p�^�������͂��ꂽ�ۂ̋�`���V�X�e���ɋ�����
void __stdcall D_SetGuideBoxRect(PAT_POS *pos);

#ifdef USE_CC
//�啪�ނ��g�p����ꍇ�ɗ��p����L�k�}�b�`���O��ݒ�
int __stdcall D_SetMatchMode_CC(int m_alg);
#endif
//�啪�ނ��g�p���Ȃ��ꍇ�ɗ��p����L�k�}�b�`���O��ݒ�
int __stdcall D_SetMatchMode_NCC(int m_alg);
//�L�k�}�b�`���O��ݒ�
int __stdcall D_SetMatchMode(int m_alg);

//�����R�[�h�������Ȃ��p�^����F���Ώۂɂ���(�O��)�֐�(flag == 1�őΏہC== 0�őΏۊO)
void __stdcall D_SetSupportNonCodePat(int flag);
//�����R�[�h�������Ȃ��p�^�����F���Ώۂɂ��邩�𒲂ׂ�(==1 �őΏہC== 0�őΏۊO)
int __stdcall D_IsSupportNonCodePat();
/////////////////////�F���t�B���^�n�֐��Q//////////////////////////

//�t�B���^�֐����Z�b�g����(�V������)
void __stdcall D_SetCRPassFilter_CrecStat(
									int (*proc)(unsigned code, void *param), void *param);
//���ݐݒ肳��Ă���t�B���^�֐����擾����
void __stdcall D_GetCRPassFilter(CRFILTER *crflt);
//�������t�B���^�p�̃J�e�S���N���X��I������
void __stdcall D_SetFiltCodeClass(int filter);
//�����R�[�h�͈͂Ŏw�肷��t�B���^�֐��̃Z�b�g
void __stdcall D_SetFiltCodeRange();
//�����R�[�h�͈͂Ŏw�肷��t�B���^�֐��ւ͈̔͂̒ǉ�
int __stdcall D_AddFilterCodeRange(unsigned start, unsigned end);
//�����R�[�h�͈͂Ŏw�肷��t�B���^�֐��ɃR�[�h���P�����ǉ�
int __stdcall D_AddFilterCodeRangeSingle(unsigned code);
//�����R�[�h�͈͂Ŏw�肷��t�B���^�֐��ɃZ�b�g�����͈͂̃N���A
void __stdcall D_ClearFilerCodeRange();
//�����R�[�h�͈̓��X�g�̒������擾
int __stdcall D_GetFilterCodeRangeListNum();
//�������w�肵�ĕ����R�[�h�͈̓��X�g���擾
int __stdcall D_GetFilterCodeRangeList(
											unsigned start[], unsigned end[], int num);
//�t���I�[�g�ŕ����R�[�h�͈̓t�B���^���擾
int __stdcall D_GetFilterCodeRangeListEX(unsigned **start, unsigned **end);
//D_GetFilterCoderangeListEX()�Ŋm�ۂ����������̈���J��
void __stdcall D_FreeFilterCodeRangeListEX(unsigned **start, unsigned **end);

//����t�B���^���N���A
void __stdcall D_ClearCodeFilter();

///////////////////////�啪�ތn�֐�/////////////////////////////

#ifdef USE_CC
//�啪�ޏ�����
int __stdcall D_OpenCoarseClassification(const char dic_file[]);
//�啪�ޏI��
void __stdcall D_CloseCoarseClassification();
//�啪�ތ�␔�ύX
int __stdcall D_ChangeCandNumCC(unsigned cand_num);
#endif //#ifdef USE_CC

///////////////////////�G�p�n�֐�/////////////////////////////

//2byte��������֐�
int __stdcall D_IsLeadByte(unsigned char c);
//�����R�[�h��SJIS�R�[�h�ɕϊ�
void __stdcall D_Jctos(unsigned code, char s[]);
//SJIS�R�[�h(������^)��WORD�^�ɕϊ�
unsigned __stdcall D_MakeCrlibCode(const char s[], unsigned *c);
//SJIS�R�[�h(������^)��WORD�^�ɕϊ�(CString->c_str():unsigned char?�Ή�)
unsigned __stdcall  D_MakeCrlibCodeUS(unsigned char c1, unsigned char c2);

#ifdef __cplusplus
	};
#endif

#endif //#ifndef __CRLIBP2PCC_H__
