/*
=============================================================================
�v���W�F�N�g��  CharacterRecognizer
�t�@�C����      ProbabilityTable.h
�N���X��        ProbabilityTable
���            �X�R�A�m���ϊ��N���X
�S����          �D�c�p�l

=============================================================================
����
05/11/27        �쐬
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
