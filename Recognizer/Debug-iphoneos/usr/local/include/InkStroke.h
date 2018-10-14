/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      InkPage.h
�N���X��        InkPage
���            Ink�f�[�^�N���X
�S����          ��ɗ�

=============================================================================
����
05/05/08        �쐬
05/09/11        InkDocument.h�t�@�C������Ɨ�
07/11/15		GetCenterPoint�֐���ǉ�
07/11/20        NodeBound�CWritingBox�CAverageSize�CStart�CEnd�CIsCheckScore�C
				SegmentProbability�CCenterHigh��ǉ�
08/06/08        NoSegmentProbability�Ɖߕ����̕ϐ��̒ǉ� by��
08/06/08    �@�@�S���҂͐D�c�����֕ύX
=============================================================================
*/

//---------------------------------------------------------------------------


#ifndef InkStrokeH
#define InkStrokeH

#include "ArrayList.h"
#include <iostream>

#if defined(WIN32)
#include <windows.h>
#else
#include "CWinStruct.h"
#endif

//#include <wndb.h>
using namespace std;

struct InkBounds
{
	public:
	int Width, Height;
	int Left, Top, Right, Bottom;

	InkBounds(ArrayList<POINT>    &point)
	{
		Left =    999999;
		Top  =    999999;
		Right =  -999999;
		Bottom = -999999;

		for(int i = 0 ; i < point.GetCount() ; i++)
		{
			int x = point[i].x;
			int y = point[i].y;

			if(Left   > x) Left = x;
			if(Top    > y) Top  = y;
			if(Right  < x) Right = x;
			if(Bottom < y) Bottom = y;
		}

		Width = Right - Left;
		Height = Bottom - Top;
	}
};
//---------------------------------------------------------------------------
enum SegmentStatus
{
	COMBINE     = 0,	// ����
	NEW_LINE    = 1,	// ���s
	VAGUE       = 2,	// �������
	DIVIDE      = 3		// ����
};
//---------------------------------------------------------------------------
class InkStroke
{
	private:

	public:
		//WNDB_STROKEAI 		Information;

        bool				IsFigure;
		RECT				Bound;
		WORD				TextTag;
		ArrayList<POINT>    Point;

		ArrayList<POINT>    ConvexBefore;
		ArrayList<POINT>    ConvexAfter;
		int					Overlap;
		int 				Distance;
		int 				IntersectLong;
		int					Feature[20];
		int 				Length;

		char                Code[3];
        SegmentStatus       Segment;  // �������
        double              Angle;
		unsigned short      offStrokeTime;
		//bool 				isPrint;
		//int 				number;
		RECT				NodeBound;
		RECT	         	WritingBox;   // ������͘g
		double          	AverageSize;  // ������s�̕��ϕ����T�C�Y
		double				SetAverageSize;
		int 				Start;
		int 				End;
		bool				IsCheckScore;
		double				SegmentProbability;
		double				NoSegmentProbability;
		int					CenterHigh;

		RECT				GetBounds();
		int					GetSize();
		POINT				GetCenterPoint();
        void                CopyTo(InkStroke &inkStroke);
		void  			    CopyToPoint(InkStroke &inkStroke);
        istream&            Read(istream &in);
        ostream&            Write(ostream &out);
        InkStroke           &operator=(const InkStroke &inkStroke);
        friend ostream      &operator<<(ostream &stream, InkStroke inkStroke);
		static				RECT GetBounds(InkStroke *stroke, int count);

        InkStroke(const InkStroke &inkStroke);
        InkStroke();
        ~InkStroke();
};
#endif
