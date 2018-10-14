/*
=============================================================================
�v���W�F�N�g��  HandsInk
�t�@�C����      InkManager.h
�N���X��        InkManager
���            Ink�f�[�^�Ǘ��N���X
�S����          ��ɗ�

=============================================================================
����
05/05/08        �쐬
05/09/11        InkDocument�N���X���폜
				ArrayList<InkPage>�N���X��ǉ�
07/09/10        ReadDntFile�֐���ǉ�
08/06/08  �@�@  �S���҂͐D�c�����֕ύX
=============================================================================
*/

//---------------------------------------------------------------------------
#include "InkPage.h"
#include "ArrayList.h"
#ifndef InkManagerH
#define InkManagerH

//---------------------------------------------------------------------------
class InkManager
{
	private:
		void	splitString(string source, char splitter, vector<string> &v);
		string& replaceChar(string& str,
							const string oldChar, const string newChar);
	protected:

	public:
		ArrayList<InkPage> Page;
		void    Clear();
		bool    IsEmpty();

		bool    ReadWndFile(const char *fileName);
		bool    AddFromWndFile(const char *fileName);		
		bool    ReadPwlFile(const char *fileName);
		bool    ReadDhwFile(const char *fileName);
		bool    LoadFromFile(const char *fileName);
		bool    SaveToFile(const char *fileName);
		bool	LoadFromInkML(const char *fileName);
		bool	AddFromInkML(const char *fileName);
		bool	LoadFromSvg(const char *fileName);
		bool	AddFromSvg(const char *fileName);
		bool    ReadDntFile(const char *fileName);
		void	HalfWidthToFullWidth(char *string);



        InkManager      &operator=(const InkManager &inkManager);
        InkManager();
        ~InkManager();


};
#endif
