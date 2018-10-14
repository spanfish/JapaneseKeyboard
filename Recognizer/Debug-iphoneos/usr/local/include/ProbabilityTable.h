/*
=============================================================================
プロジェクト名  CharacterRecognizer
ファイル名      ProbabilityTable.h
クラス名        ProbabilityTable
解説            スコア確率変換クラス
担当者          織田英人

=============================================================================
履歴
05/11/27        作成
=============================================================================
*/
//---------------------------------------------------------------------------

#ifndef ProbabilityTableH
#define ProbabilityTableH
//---------------------------------------------------------------------------
#pragma pack(push,1)

class ProbabilityTable
{
    private:
        bool    isEmpty;
        double  *table;
        int     count;
        int     skip;

    public:
        bool    IsEmpty();
        void    Clear();

        void    SetSkip(int skip);
        int     GetSkip();

        void    SetTable(double *table, int count);
        const double* GetTable();

        int     GetCount();
        double  GetProbability(int score);
        bool    SaveToFile(const char fileName[]);
        bool    LoadFromFile(const char fileName[]);
        bool    ExportToTextFile(const char fileName[]);

        ProbabilityTable();
        ~ProbabilityTable();
};
#pragma pack(pop)
#endif
