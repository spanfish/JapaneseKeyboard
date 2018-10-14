#ifndef _NRUTIL_H_
#define _NRUTIL_H_

#define LING 1E-6

void nrerror(const char* error_text);

float *vector(long nl, long nh);
float **matrix(long nrl, long nrh, long ncl, long nch);
float ***matrix3D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh);
float ****matrix4D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh);
float *****matrix5D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh, long nsl, long nsh);
float ******matrix6D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh, long nsl, long nsh, long ntl, long nth);
void free_vector(float *v, long nl, long nh);
void free_matrix(float **m, long nrl, long nrh, long ncl, long nch);
void free_matrix3D(float ***m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh);
void free_matrix4D(float ****m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh);
void free_matrix5D(float *****m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh, long nsl, long nsh);					
void free_matrix6D(float ******m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh, long nsl, long nsh, long ntl, long nth);
/*
double *dvector(long nl, long nh);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
double ***dmatrix3D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh);
double ****dmatrix4D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh);
double *****dmatrix5D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh, long nsl, long nsh);
double ******dmatrix6D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh, long nsl, long nsh, long ntl, long nth);
void free_dvector(double *v, long nl, long nh);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);
void free_dmatrix3D(double ***m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh);
void free_dmatrix4D(double ****m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh);
void free_dmatrix5D(double *****m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh, long nsl, long nsh);					
void free_dmatrix6D(double ******m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh, long nsl, long nsh, long ntl, long nth);
*/
unsigned long *lvector(long nl, long nh);
int *ivector(long nl, long nh);
int **imatrix(long nrl, long nrh, long ncl, long nch);
int ***imatrix3D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh);
int ****imatrix4D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh);
void free_lvector(unsigned long *v, long nl, long nh);
void free_ivector(int *v, long nl, long nh);
void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch);
void free_imatrix3D(int ***m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh);
void free_imatrix4D(int ****m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh);

unsigned char *cvector(long nl, long nh);
char **cmatrix(long nrl, long nrh, long ncl, long nch);
char ***cmatrix3D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh);
char ****cmatrix4D(long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh);	
void free_cvector(unsigned char *v, long nl, long nh);
void free_cmatrix(char **m, long nrl, long nrh, long ncl, long nch);
void free_cmatrix3D(char ***m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh);
void free_cmatrix4D(char ****m, long nxl, long nxh, long nyl, long nyh, long nzl, long nzh, long nrl, long nrh);

float **submatrix(float **a, long oldrl, long oldrh, long oldcl, long oldch, long newrl, long newcl);
float **convert_matrix(float *a, long nrl, long nrh, long ncl, long nch);
void free_submatrix(float **b, long nrl, long nrh, long ncl, long nch);
void free_convert_matrix(float **b, long nrl, long nrh, long ncl, long nch);

class CJUZHEN
{
public:
	void JUXXIANG( float**, float*, int, float* );	
	void JUXXIANG( float** A, int m, int n, float* vect, float* outv );
	void JUXJU( float**, float**, int, float** );
	void JUXJU( float**, float**, int );
	void JUXJU( float** A, float** B, int m, int r, int n, float** C );
	void ZHUANZHI( float**, int, float** );
	void ZHUANZHI( float** A, int m, int n, float** B );
	void DUIJIAOHUA( float**, int, float** );
	float KBIANHUAN( float**, int, float*, float* );
	void ERDE( float**, int, float** );
	int FANSHE( float*, int, int, float* );
	void GENGXIN( float**, float*, int, int );
	int QLD( float**, int, int, float** );
	float SQL( float**, int, int, float** );
	float** FENPEI( int );
	float** FENPEI( int m, int n );
	void SHIFANG( float**, int );
	void SHIFANG( float** A, int m, int n );
	void CHUSHIHUA( float**, int );	
	void WAIJI( float*, float*, int, float** );		
	float NEIJJI( float*, float*, int );		
};
					 			 					
#endif /* _NRUTIL_H_ */
