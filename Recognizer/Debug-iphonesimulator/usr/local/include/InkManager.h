/*
=============================================================================
プロジェクト名  HandsInk
ファイル名      InkManager.h
クラス名        InkManager
解説            Inkデータ管理クラス
担当者          朱碧蘭

=============================================================================
履歴
05/05/08        作成
05/09/11        InkDocumentクラスを削除
				ArrayList<InkPage>クラスを追加
07/09/10        ReadDntFile関数を追加
08/06/08  　　  担当者は織田から朱へ変更
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
