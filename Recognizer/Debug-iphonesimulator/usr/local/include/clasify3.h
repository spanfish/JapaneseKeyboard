/*=============================================================

			�啪�ރ��C�u���� �V�X�e���w�b�_�t�@�C��

by �{�� ����
	1994.??.??	fujidata.h �I�����C���I��@
	1994.10. 4�`classify.h �I�t���C���I��@
	1994.11.15�`ndata.h �I�����C���I��@
	1995. 1.13�`choclas.h ���@����
	1995. 1.16	����܂ł̃w�b�_�t�@�C��������
	1995. 5.19	���X�g�\���̎�����ǉ�
	1995. 6.10	Ver 1.0 (comclas.h)
	1995.10.16	Ver 1.1 comclas.h ���番��(classify.h)
	1995.10.16	Ver 1.11 ��������
	1996. 6. 4	Ver 1.12 ��������8�����ɑΉ�
	1996. 7. 7	Ver 1.13 ����Ȃ��\���̂Ȃǂ��폜
by Katsuhiko Akiyama
	1998/ 1		���낢�뒼����

=============================================================
=============================================================================
����
07/07/30        DFVDATA��dv�̃T�C�Y��傫�������Dby��
=============================================================================
*/

#ifndef __classify_h__

#define __classify_h__

#include "crlib.h"

//#define homma
//#define homma_err_check							// �f�o�b�O�p�G���[�`�F�b�N
#define bunkatsu4x4  							// ������ 4x4 (default�� 8x8)
#define non_binarized							// 2�l���łȂ� (default��2�l��)
#define dfv8direction							// 8�����g��

// �����̍ő�l(int)
#define NDISTANCE_MAX			0x7fff
// �����̍ő�l(long)
#define LDISTANCE_MAX			0x7fffffffL

// �}�X�̕W���T�C�Y
#define BOX_SIZE				128
#define BOX_SIZE_CLSS			(DIVISION_NUM * (1 << LOG_DIV_SIZE))
// �}�X�̕W���T�C�Y(�啪��)������8x8->128, 4x4->64
// �搔�̍ő�l - 1
#define ST_MAX					30

// �����_���o��臒l
#define DefMaxArc				7

// �X�g��臒l�̂���
//#define LEN_LOOSENESS			8
#define LEN_LOOSENESS			50
// �ϓ���臒l�̂���
//#define TURN_LOOSENESS			2
#define TURN_LOOSENESS			5
// �搔臒l�̂���
#define K_LOOSENESS				1
// �X�g�����w�K����Ƃ��̕�
#define STUDY_WIDTH				2

/*
----------------------------------------------------------------------------
LEN_STUDY_WIDTH �͎��̂悤�Ȏ��Ŏg�p�����B
len_study_width = (len_max - len_min) >> LEN_STUDY_WIDTH; ......(1)
�����ŁA�ϐ� len_study_width �̓X�g���[�N�����w�K����Ƃ��Ɏ������镝�ł���B
�X�g���[�N���̊w�K�ł́A�w�K�����������̃X�g���[�N�����������]�T����������
�w�K����B
len_max �� len_min �́A�����̃X�g���[�N���͈̔͂ł���B
������A��̎��́A�����̃X�g���[�N���͈̔͂� LEN_STUDY_WIDTH = 3 ����
�E�ɃV�t�g���邱�ƁA�܂� 8 �Ŋ��邱�Ƃ��Ӗ�����B
�܂Ƃ�
�X�g���[�N���̊w�K�ł́A�����̃X�g���[�N���͈̔͂� 8 �Ŋ�����������
�]�T���������Ċw�K����B
----------------------------------------------------------------------------
*/

/*
----------------------------------------------------------------------------
�p�����
�Z��...�ŏ������P��
���̈�...�Z���l����Ȃ�P��
----------------------------------------------------------------------------
*/

#ifdef dfv8direction
	// 8����
	#define DIRECTION_NUM		8
#else
	// 4����
	#define DIRECTION_NUM		4
#endif

// ��������ς������ꍇ�A���̕ӂ�ύX����
#ifndef bunkatsu4x4
	// ������ 8�~8 �̏ꍇ
	#define DIVISION_NUM		8
#else
	// ������ 4�~4 �̏ꍇ
	#define DIVISION_NUM		4
#endif

// �Z�����̃r�b�g��
#define LOG_DIV_SIZE		4
// �O�́A8x8�̂Ƃ���LOG_DIV_SIZE��3�ɂ��Ă����B
#define CELL_NUM			(DIVISION_NUM - 1)
// ���̈�̐�
#define CLSS_VCTR_DIM		(CELL_NUM * CELL_NUM)
// ��������������
#define CLSS_DFDATA_DIM		(CLSS_VCTR_DIM * DIRECTION_NUM)
// 2�l�������Ƃ��̃o�C�g��
#define CLSS_DF2_DIM		((CLSS_DFDATA_DIM + 7) >> 3)

// ���������x�N�g��������
#ifdef non_binarized
	#define CLSS_DFV_DIM		CLSS_DFDATA_DIM
#else
	// �������i2�l�������ꍇ�j
	#define CLSS_DFV_DIM		CLSS_DF2_DIM
#endif

// �d�݂̘g�̕��̃r�b�g��
#define LOG_WEIGHT_SIZE		(LOG_DIV_SIZE - WEIGHT_GRAD_BIT)
// �d�݂̒i�K���̃r�b�g��
#define WEIGHT_GRAD_BIT		2
// �d�݂̒i�K��
#define WEIGHT_NUM			(1 << WEIGHT_GRAD_BIT)
// �d�݂̃}�X�N
#define WEIGHT_MASK			(WEIGHT_NUM - 1)

// �������ɑΉ����������̃E�F�C�g
#define DISTANCE_WEIGHT		1
// 2�l��臒l(�V�K�����쐬�̏ꍇ)
#define NICHITHRESHOLD		49

// 2�̕�����
#define ROOT2				1.41421356
// 2�̕�������2����1
#define ROOT2SEC			(ROOT2 / 2)
// 2�̕�����/2*(2^(GETA_UP=7)))
#define ROOT2x64			90
// cos �𐮐��ɂ��邽�߂ɉ��ʂ��͂�����
#define GETA_UP				7

// ���ʂɂ��Ă̒���
// �������� 4x4 �̏ꍇ�A�e���l���傫���Ȃ��Ă��܂��̂ŁA
// �͂��������ʂ���]���ɉ��ʂ��͂����B
#define GETA_DOWN			(GETA_UP + 1)

#define FEATURE			8		// �����_

// �啪�ފw�K�ŁA�����w�K�������̃t���O
#define STUDY_ERR		-1		// �G���[
#define STUDY_K_MAX		1		// �搔�̍ő�l
#define STUDY_YLEN_MIN	2		// Y�����̃X�g���̍ŏ��l
#define STUDY_OTHER		4		// ���̑��̃I�����C������
#define STUDY_DFV		8		// ���������x�N�g��
#define STUDY_NEW		\
		(16 | STUDY_K_MAX | STUDY_YLEN_MIN | STUDY_OTHER | STUDY_DFV)
								// �V�K�����w�K

#define STUDY_ON				1
#define STUDY_OFF				0

// ���X�g���[�N�̈���
#define SW_NOBACK	1
#define SW_BACK		2
// �����������o���@
#define SW_COS		1
#define SW_SQRCOS	2
#define SW_THRESH	3
// �����v�Z���@
#define SW_EUCLID		1
#define SW_CITYBLOCK	2
// �����v�Z��int,long�I��
#define SW_INT		1
#define SW_LONG		2

typedef union{		// ���{�ꕶ���^�ichar �̓��{��Łj
	WORD w;								/* 2 �o�C�g�i1 ���[�h�j */
	struct{
		BYTE low;						/* ���ʃo�C�g */
		BYTE high;						/* ��ʃo�C�g */
	} b;
} jchar;

typedef struct {	// ���
	long distance;
	jchar jiscode;
	WORD dummy;
} CANDIDATE;

// ��╶����Ƃ��̓��_
typedef struct {
	CANDIDATE *candidate;
	// ��␔
	int num;
} DFVCAND;

typedef struct {	// ���̓p�^���̃X�g���[�N�Ɋւ�����
	int stnum;					// �搔
	int xlen;					// X �����X�g���[�N��(city block ����)
	int ylen;					// Y �����X�g���[�N��
	int xturn;					// X ����������
	int yturn;					// Y ����������
} STDATA;

// 8����	0:�E, 1:�E��, 2:��, 3:����, 4:��, 5:����, 6:��, 7:�E��
// 4����	0:����, 1:�E�オ��, 2:����, 3:�E������
typedef struct{
	unsigned int direct[DIRECTION_NUM];
} DIRECT;

// 8�����̏ꍇ�́C4�������瓮�I�Ɋ��蓖�Ă�D
// 8����	0:�E, 1:�E��, 2:��, 3:����, 4:��, 5:����, 6:��, 7:�E��
typedef struct{
	unsigned int amount[4];
	int d[4];
} DIRECT8;

// �x�N�g����������Ƃ��z��ŕ\�킷
typedef union{
	unsigned v[CLSS_DFDATA_DIM];
	DIRECT dv[CLSS_VCTR_DIM + 10];
} DFVDATA;

// ���������x�N�g��
typedef struct{
	BYTE v[CLSS_DFV_DIM];
} DFV;

// �X�g���[�N���ƕ������������킹���\����
typedef struct {
	STDATA stdata;
	DFV dfv;
} UDATA;

// ============================= �����\�� ============================
// �����̉搔�A�X�g���A�����ϓ��񐔂̕���
typedef struct{
	// �搔
	BYTE k_max;
	// �X�g���[�N��
	BYTE xlen_max;
	BYTE xlen_min;
	BYTE ylen_max;
	BYTE ylen_min;
	// �ϓ���
	BYTE xturn_max;
	BYTE xturn_min;
	BYTE yturn_max;
	BYTE yturn_min;
} ONLINE_CC_DIC;

// �����̕���������
typedef struct{
	DFV dfv;
} OFFLINE_CC_DIC;

typedef struct tagUNION_CC_DIC{
	// �I�t���C������
	OFFLINE_CC_DIC *offcd;
	// �I�����C������
	ONLINE_CC_DIC oncd;
	// �����N
	struct tagUNION_CC_DIC *previous, *next;
	// �����R�[�h
	jchar jiscode;
	// �I�t���C�������̐�
	BYTE offcd_num;
} UNION_CC_DIC;

#endif