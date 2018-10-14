// Utilities for computation of symmetric matrices

class CMatrix
{
	// Diagonalization (K-L transform)
	void Jacobi( double**, int );
	void planeRotate( double**, int, int, int, double** );

	void Householder( double**, int, double** );
	int reflection( double*, int, int, double* );
	void updateMat( double**, double*, int, int );

	int QLdecomp( double**, int, int, double** );
	double shiftQL( double**, int, int, double** );

public:
	double** allocMat( int );
	void freeMat( double**, int );
	void initMat( double**, int );	// set identity matrix

	// Elementary matrix and vector compuations
	void outProduct( double*, double*, int, double** );		// outer product
	double innProduct( double*, double*, int );		// inner product
	double innProduct( float*, double*, int );

	void matXvec( double**, double*, int, double* );	// multiplication
	void matXmat( double**, double**, int, double** );
	void matXmat( double**, double**, int );

	void transpose( double**, int, double** );

	void diagonalize( double**, int, double** );

	// Check the orthonormality and characteristic equation
	double characteristic( double**, int, double*, double*, int );
	double KLT( double**, int, double*, double* );
	double PCA( double**, int, double*, double*, int );

	double matInverse( double**, int, double** );
};
