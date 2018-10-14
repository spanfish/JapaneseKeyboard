#ifndef QDFH
#define QDFH

#if defined(WIN32)
#else
#include "MemoryMappedMode.h"
#endif

#include <stdio.h>
#include "Sorter.h"
#include <vector>

using namespace std;

typedef unsigned char BYTE;
#define SIZE_QDF_DATA		40000000

typedef struct tagQDFHead {
	int classNum;
	int ftrDim;
	int vecNum;
	int knum;
    
	short dimOfCDLow;
	short MaxMean;
	short MinMean;
	short w;
	short diffM;
    
	short minMean;//used for coarse classification
	float wei;
    
	//double averageVar;
	int classNum1;
	int classIndexSize;
    
	unsigned char NumOfCenter;//for code Book
	short stepOfsub;		  //for code Book
    
	int offsetEigVecVQ;
	int offsetMeanVecCH;
	int offsetDLowMean;
	int offsetMean;
    
	int offsetMeanVec;
	int offsetEigVec;
	int offsetEigVal;
	int offsetCoTrace;
	int offsetLogeig;
    
	int offsetMeanT;
	int offsetMeanVecT;
	int offsetEigVecT;
	int offsetEigValT;
	int offsetCoTraceT;
	int offsetCodebook;//for code Book fname1
	int offsetClassIndex;
	int dataSize;
    
	
	double hh;
	double loghh;
} QDFHead;

typedef struct tagQDFData {
	QDFHead head;
	unsigned char data[1];
} QDFData;

// AE K.Iwakura 2010/12/08

//---------------------------------------------------------------------------
struct Parameter
{
	short* MeanVec;	
	short* EigVec;
	int* EigVal;
	int CoTrace;	
	double Logeig;
	
	void Set(short* meanVec, short* eigVec, int* eigVal, int coTrace)
	{
		MeanVec = meanVec;
		EigVec = eigVec;
		EigVal = eigVal;
		CoTrace = coTrace;

		return;
	}
	Parameter(void)
	{
		MeanVec = NULL;
	}
	~Parameter(void)
	{
	}
};
//---------------------------------------------------------------------------
struct OfflineModel
{
	//Parameter *Parameters;
	int *ParaId;
	short Count;

	/*void Add(short* meanVec, short* eigVec, int* eigVal, int coTrace)
	{
		Parameter *para = new Parameter[Count + 1];
		if(Count != 0) 
		{
			memmove(para, Parameters, sizeof(Parameter) * Count);
			delete []Parameters;
		}
		Parameters = para;
		Parameters[Count].Set(meanVec, eigVec, eigVal, coTrace);
		Count++;
	}*/
	void Add(int id)
	{
		int *para = new int[Count + 1];
		if(Count != 0) 
		{
			memmove(para, ParaId, sizeof(int) * Count);
			delete []ParaId;
		}
		ParaId = para;
		ParaId[Count] = id;
		Count++;
	}
	OfflineModel(void)
	{
		//Parameters = NULL;
		Count = 0;
	}
	~OfflineModel(void)
	{
		if(Count != 0) 
		{
			//delete []Parameters;
			delete []ParaId;
		}
	}
};
//---------------------------------------------------------------------------
class CQDF {
    
#if defined(MM_FILE_USE)
	int		hFile;
	int		map_size;
	//HANDLE		hMMMap;
#endif
    
#if defined(MM_FILE_WRITE) || defined(MM_FILE_READ) || defined(MM_FILE_USE)
	QDFData	*pData;
#endif
    
#if defined(MM_FILE_WRITE)
    void CreatMMFFile(const char fname[]);
#endif
    
#if defined(MM_FILE_WRITE) || defined(MM_FILE_READ) || defined(MM_FILE_USE)
    int MMFclassNum1;
    int MMFClassIndexSize;
#endif
    
	int vecNum, knum;		// number of eigen vectors
	int ftrDim;

	short* meanVec;	// mean feature vector, 10 times of true value//Åú
	short* eigVec;	// eigen vectors, 100 times of true value

//***************************Changed by Gao
	unsigned char* eigVecVQ;
	unsigned char* meanVecCH;
//*************************************************
	int* eigVal;	// eigen values, 100 times of true value//64bit long to int
	int* coTrace;	// trace of covariance matrix = variance, 100 times/64bit long to int
	double* logeig;

	short* meanVecT;	// mean feature vector, 10 times of true value//Åú
	short* eigVecT;	// eigen vectors, 100 times of true value
	int* eigValT;	// eigen values, 100 times of true value//64bit long to int
	int* coTraceT;	// trace of covariance matrix = variance, 100 times//64bit long to int

	unsigned char *mean;
	unsigned char *meanT;
	short minMean;//used for coarse classification
	short w;
	float wei;
	//************************Added by Gao

	short* codebook;
	char* DLowMean;
	short stepOfsub;
	unsigned char NumOfCenter;
	short dimOfCDLow;
	short MaxMean,MinMean;//used for the fine classification
	short diffM;
	
	//*******************************

	vector<OfflineModel> models;

	int totalClassNum;
	int *classIndex;

	double	hh, loghh;

	short *candidate;

	double maxQdist;
	Sorter *sort;
#if defined(MM_FILE_READ) || defined(MM_FILE_USE)
	bool ReadMMFDictionaryData(const char fname[]);
	bool ReadMMFMeanData(const char fname[]);
#endif
	int incPos( int, int*, int );	// position in increasing array
	double readEig(FILE *fpEig);
	double readMeanEig(FILE *fpEig);
	void setModels(int *classIndex, int baseId);
	void extractPartCharacters(int *index, int cNum, short** meanVec, short** eigVec, int** eigVal, int** coTrace);
	bool readDictionary( const char fname[],const char fname1[]);
	bool readDictionary( const char fname[]);
	bool readMean( const char fname[]);
	bool addCharacter(short *intMn, char *fileName);
	bool deleteCharacter(unsigned short id, char *fileName);
	bool addTemplate(short *intMn, int cls, char *fileName);
	void extractPartCharactersMean(int *index, int cNum, unsigned char** meanVec2);
public:
	CQDF( const char fname[]);
	CQDF( const char fname[],const char fname1[]);
	CQDF( const char fname[], bool isOnlyUseMean);
	~CQDF();
	bool IsEmpty;

	int classNum;
	bool isOnlyUseMean;

	void candiSrch( short*, int, int*, int*, int&);	// candidates from Euclidean distance
	void candiSrch( int*, int, int*, int*, int);	// candidates from Euclidean distance
	void candiSrchNew( short*, int, int*, int*, int);
	void candiSrchFast( short*, int, int*, int*, int&);
	void candiSrchFast( int *, short*, int, int*, int*, int &);
	void candiSrchFastMean( short*, int, int*, int*, int&);
	void candiSrchFastMean( int *, short*, int, int*, int*, int &);
	void ChangeDicOrder( const char fname[]);
	double MQDF2( short*, int, int, int );
	double MQDF2( int*, int, int, int );
	double MQDF2Fast( short* ftr, int dim, int cls, int euclid );
	double GetMQDF2( short*, int, int );
	double GetMQDF2( int*, int, int );
	double GetMQDF2Fast( short* ftr, int dim, int cls );
	int GetDim(void);
	bool AddCharacter(short *intMn, int *intEig, short* intVec,
		int intVar, char *fileName);
	bool DeleteCharacter(unsigned short id, char *fileName);
	void SetCandidate(short *candidate);
	int Recognize(int *index, int preClassifyCount, int count, short *fea, int dim
					, int *id, int *score);
	int Recognize(int *index, int preClassifyCount, int count, short *fea, int dim
					, int *id, double *score);
	void ExtractPartCharacters(int *index, int cNum);
	bool WriteDictionary(const char dicName[]);
	int GetEuclid(short *ftr, int dim, int cls);
	bool AddTemplate(short *intMn, int *intEig
					, short* intVec, int intVar, int cls, char *fileName);
	void GetClassIndex(int *index, int count);
	bool ReWriteDictionary( const char fname[]);
};
//---------------------------------------------------------------------------
#endif