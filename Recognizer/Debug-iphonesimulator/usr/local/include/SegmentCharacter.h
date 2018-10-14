/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      SegmentCharacter.h
�N���X��        SegmentCharacter
���            �s�P�ʂ̃X�g���[�N�𕶎��\���v�f�P�ʂɕ�������N���X
�S����          �� �ɗ�

=============================================================================
����
05/05/08        ���`���쐬
05/05/17        �S���҂�D�c�����ɕύX�C�j���[�����ɂ��؏o�����@������
05/09/26        InkManager�p�b�P�[�W�̎d�l�ύX�ɔ����ύX by �D�c
07/03/08        �j���[�����ɂ��؏o�����@����SVM�ɂ��؏o�����@��ύX
07/06/03        SetOffStrokeTimeFlag�֐����폜
07/06/03        ExtractFeature��isUseOffstrokeTime�ϐ���ǉ�
07/08/30        �������g�p�ʂ��팸���邽�ߕύX
07/11/20        ������E�ւ̐��������񂾂��̔F���ɕύX
				�������̋����ɂ�艼�̞B���؏o���ɂ��C�����̐؏o����₩��
				SVM�Ő�ΐ؏o���_��I��������@�ɕύX
07/11/26        SEGMENT_PARAMETER_FILE�̒�`���w�b�_�Ɉړ�
				(���̃\�[�X����Q�Ƃ���)by�D�c
07/11/27		SetStructureInformation�̐��`��ǉ�
08/06/08        �ߕ����̒���
=============================================================================
*/

//---------------------------------------------------------------------------
#ifndef SegmentCharacterH
#define SegmentCharacterH

#include <stdio.h>
#include "InkPage.h"
#include "svm_common.h"
#define STRING_DIRECTION_NUMBER 4
#define SEGMENT_PARAMETER_FILE "ja_JP_w_segment.res"
//#define SEGMENT_PARAMETER_FILE "modelTimeless1"

#if defined(WIN32)
#else
#include "MemoryMappedMode.h"
#endif
//---------------------------------------------------------------------------
template <typename T>
inline const T& Max(const T& a, const T& b)
{
    return a < b ? b : a;
}
//---------------------------------------------------------------------------
template <typename T>
inline const T& Min(const T& a, const T& b)
{
    return a < b ? a : b;
}
//---------------------------------------------------------------------------
enum CharacterStringDirection
{
    LEFT_TO_RIGHT = 0,
    RIGHT_TO_LEFT = 1,
    TOP_TO_BOTTOM = 2,
    BOTTOM_TO_TOP = 3
};
//---------------------------------------------------------------------------
class SegmentCharacterException
{
    private:

        // ��O�𔭐������s��
        int line;
        // ��O�𔭐������t�@�C����
        char * file_name;

    public:

        int GetSegmentCharacterExceptionLine(void) const
        {
            return line;
        }

        const char *GetSegmentCharacterExceptionFile(void) const
        {
            return file_name;
        }

        void print( void ) const
        {
            FILE *fp = fopen("SegmentCharacterExceptionFile.txt", "w");
            if(fp != NULL)  {
                fprintf(fp,"Line:%d FileName:%s\n", line, file_name);
                fclose(fp);
            }
        }

        SegmentCharacterException(int tline, char *tfile_name)
        {
            line = tline;
            file_name = tfile_name;
        }
        ~SegmentCharacterException() throw(){ }
};
//---------------------------------------------------------------------------
class ExtractFeature
{
    private:

    protected:

		RECT *bound;
    	void MakeBound(RECT *strokeBound, int count);

	public:

		static int BoundCenterDistance(RECT &previous, RECT &next);
		static int BoundXCenterDistance(RECT &previous, RECT &next);
		static int BoundYCenterDistance(RECT &previous, RECT &next);
		static int BoundXDistance(RECT &previous, RECT &next);
		static int BoundYDistance(RECT &previous, RECT &next);
		static int BoundXDistanceV(RECT &previous, RECT &next);
		static int BoundYDistanceV(RECT &previous, RECT &next);
		static long GetOverlap(RECT &previous, RECT &next);
		static long GetOverlapV(RECT &previous, RECT &next);

	bool isUseOffstrokeTime;
        virtual void Execute(int *feature, InkStroke *inkStroke, int characterSize,
							 int dimension, RECT *strokeBound, int count
							 , POINT &p) = 0;
		static void MergBound(RECT &previous, RECT &next);

        ExtractFeature(){ }
        virtual ~ExtractFeature(){ }
};
//---------------------------------------------------------------------------
class ExtractFeatureLeftToRight : public ExtractFeature
{
    protected:

    private:

    public:

        void Execute(int *feature, InkStroke *inkStroke, int characterSize,
					 int dimension, RECT *strokeBound, int count, POINT &p);

        ExtractFeatureLeftToRight(){ };
        ~ExtractFeatureLeftToRight() { };
};
//---------------------------------------------------------------------------
class ExtractFeatureRightToLeft : public ExtractFeature
{
    protected:

    private:

    public:

        void Execute(int *feature, InkStroke *inkStroke, int characterSize,
					 int dimension, RECT *strokeBound, int count, POINT &p);

        ExtractFeatureRightToLeft(){ };
        ~ExtractFeatureRightToLeft() { };
};
//---------------------------------------------------------------------------
class ExtractFeatureTopToBottom : public ExtractFeature
{
    protected:

    private:

    public:

        void Execute(int *feature, InkStroke *inkStroke, int characterSize,
					 int dimension, RECT *strokeBound, int count, POINT &p);

        ExtractFeatureTopToBottom(){ };
        ~ExtractFeatureTopToBottom() { };
};
//---------------------------------------------------------------------------
class ExtractFeatureBottomToTop : public ExtractFeature
{
    protected:

    private:

    public:

        void Execute(int *feature, InkStroke *inkStroke, int characterSize,
					 int dimension, RECT *strokeBound, int count, POINT &p);

        ExtractFeatureBottomToTop(){ };
        ~ExtractFeatureBottomToTop() { };
};
//---------------------------------------------------------------------------
// AS K.Iwakura 2010/12/07
//#define SIZE_SEGMENT_CHARACTER_DATA 8000000
//#define SIZE_SEGMENT_CHARACTER_DATA 2400000
#define SIZE_SEGMENT_CHARACTER_DATA 4000000
//#define SIZE_SEGMENT_CHARACTER_DATA 2404303

typedef struct tagModelHead { // CHG K.Iwakura 2010/12/10
    int    offsetFeature;
    int    offsetSupvec;
    int    offsetAlpha;
    int    offsetIndex;
    
    int   sv_num;//long->int
    int   at_upper_bound;//long->int
    int   totwords;//long->int
    int   totdoc;//long->int
    
    double b;
    KERNEL_PARM kernel_parm;
    double loo_error, loo_recall, loo_precision;
    double xa_error,xa_recall,xa_presicion;
    double maxdiff;
    int    offsetLin_weights;
    int	 dummy;		// for 8byte boundary
} ModelHead;

typedef struct tagSegmentCharactaerHead {
    int isUseOffstrokeTime;
    int dataSize;
    int padding1[2];
    int dimension[STRING_DIRECTION_NUMBER];
    int offsetMean[STRING_DIRECTION_NUMBER];
    int offsetVariance[STRING_DIRECTION_NUMBER];
    ModelHead modelHead[STRING_DIRECTION_NUMBER];
} SegmentCharacterHead;

typedef struct tagSegmentCharactaerData {
    SegmentCharacterHead head;
    unsigned char data[1];
} SegmentCharacterData;
// AE K.Iwakura 2010/12/07
//---------------------------------------------------------------------------
class SegmentCharacter
{
    protected:

    private:
#if defined(MM_FILE_USE)
    int		hFile;
    int		map_size;
    //HANDLE		hMMMap;
#endif
#if defined(MM_FILE_WRITE) || defined(MM_FILE_MODEL) || defined(MM_FILE_READ) || defined(MM_FILE_USE)
    SegmentCharacterData *pData;		// ADD K.Iwakura 2010/12/07
#endif
    
		int dimension[STRING_DIRECTION_NUMBER];
        double *mean[STRING_DIRECTION_NUMBER];
        double *variance[STRING_DIRECTION_NUMBER];
        MODEL *model[STRING_DIRECTION_NUMBER];
		MODEL *segmentModel;
		int segmentDimension;
        bool isUseOffstrokeTime;
    	int centerHigh;
		int left;
		int right;

        int characterSize;
        CharacterStringDirection direction;

		bool isHeavySegmentation;

#if defined(MM_FILE_MODEL) || defined(MM_FILE_READ) || defined(MM_FILE_USE)
    void ReadSegmentParameterMM(const char *mmFileName); //throw (SegmentCharacterException); // ADD K.Iwakura 2010/12/07
    void FreeSegmentParameterMM(void); // ADD K.Iwakura 2010/12/07
    MODEL * readModelMM(int index); // ADD K.Iwakura 2010/12/08
#else
        void ReadSegmentParameter(char* fileName) throw (SegmentCharacterException);
        void FreeSegmentParameter(void);
        void SetCharacterStringDirection(RECT *strokeBound, int count);
        double sprod_ss(SVECTOR *a, SVECTOR *b);
        SVECTOR * create_svector(WORD_NEW *words, char *userdefined, double factor);
        DOC * create_example(long docnum, long queryid, long slackid
            , double costfactor, SVECTOR *fvec);
#if defined(MM_FILE_WRITE)
    MODEL * readModel(FILE *modelfl, int dim, int index); // ADD 1param K.Iwakura 2010/12/07
#else
        MODEL * readModel(FILE *modelfl, int dim);
#endif
        void * my_malloc(size_t size);
        int space_or_null(int c);
        int parse_document(char *line, WORD_NEW *words, double *label,
            long *queryid, long *slackid, double *costfactor,
            long int *numwords, long int max_words_doc, char **comment);
        void free_svector(SVECTOR *vec);
        void free_example(DOC *example, long deep);
        void freeModel(MODEL *model, int deep);
#endif
        void SetSize(RECT *strokeBound, int count);
		double sprod_ss_new1( float *feature1, float *feature2, int dim );
        double sprod_ss_new2(float *feature, int dim);
        double recognize(MODEL *model, float *feature, int dim);
		int readLineValue(char *line, double *value);
		RECT getBoundingBox(InkStroke *inkStroke, int count);
		int BoundH(RECT &Bound);
		void setSegment(InkStroke *inkStroke, int count, POINT &p);
		void modifySegment(InkStroke *inkStroke, int count, RECT *strokeBound);
		void modifySegment(InkStroke *inkStroke, int count);
		void MakeBound(RECT *strokeBound, int count, RECT *bound);
		void  ExtractingFeatureOne(int count,
			RECT *bound, RECT* strokeBound, int *boundDistance);
		int overSegment(InkStroke *inkStroke, int count, int *boundDistance,
		    int lineCenterHigh, RECT *allBound);
		void setSegment(InkStroke *inkStroke, int count, RECT *strokeBound);
		int ExtractingNewFeature(int *feature, InkStroke *inkStroke,
			int count, RECT *bound, RECT* strokeBound, int *boundDistance);
		void MergBoundHigh(RECT &previous, RECT &next);
		double distance(POINT &p1, POINT &p2);
		double getAngle(POINT &p1, POINT &p2);
		void getConvexHull(int pCount, POINT *point, ArrayList<POINT> &convex
			, bool isBefore = true);
		void setConvexAndOverlap(InkStroke *inkStroke, int count);
		int getPointToCurveDistance(POINT &point, ArrayList<POINT> &curve);
		int getPointToSengmentDistance(POINT &point, POINT &sengment1
			, POINT &sengment2);
		bool isIntersect(POINT &point1, POINT &point2, POINT &point3, POINT &point4);
		int getMinDistance(ArrayList<POINT> &point1, ArrayList<POINT> &point2);
    	double getPointDistance(POINT& point, double *line);
		bool getIntersect(POINT &point1, POINT &point2, POINT &point3
			, POINT &point4, POINT &point);
		int getStrokeMinDistance(ArrayList<POINT> &point1
			, ArrayList<POINT> &point2);
		int getStrokeLength(POINT *point, int count);
		int getIntersectLong(InkStroke &inkStroke1, InkStroke &inkStroke2);
		void setOverlap(InkStroke *inkStroke, int count, int *boundDistance);
		void extractOverSegmentFeature(InkStroke *inkStroke, int count
			, RECT* strokeBound, int *boundDistance);
		int reOverSegment(InkStroke *inkStroke, int count);
		int setNodeBound(InkStroke *inkStroke, int count, RECT *bound, int *starts, int *countBs);
		int setNodeBound(InkStroke *inkStroke, int count);
		int repeatSegmentation(InkStroke *inkStroke, int count);
		void reduceGaps(InkStroke *inkStroke, int count, RECT *strokeBound,
								   RECT *bound, int *boundDistance);

    public:
		bool IsEmpty;
		void Execute(InkStroke *inkStroke, int count);
		void ExtractOverSegmentFeature(InkStroke *inkStroke, int count);
		void SetStructureInformation(InkStroke *inkStroke, int count);
		void SetHeavySegmentation(bool isHeavySegmentation);

        SegmentCharacter();
        SegmentCharacter(char *fileName);
        ~SegmentCharacter();
};
//---------------------------------------------------------------------------
#endif
