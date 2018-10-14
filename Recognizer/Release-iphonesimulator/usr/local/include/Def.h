/* Definitions of constant and marco */

#ifndef	_DEF_H_	
#define	_DEF_H_

//----------------------------------------------------------------------------------------------------------------------------

#ifndef INF
#define INF 1e10
#endif

#ifndef ZERO
#define ZERO 1e-3
#endif

#ifndef DZERO
#define DZERO 1e-6
#endif

#ifndef PI
#define PI 3.1415926
#endif

#ifndef NULL
#define NULL                0
#endif

//----------------------------------------------------------------------------------------------------------------------------

#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN        512                
#endif

//----------------------------------------------------------------------------------------------------------------------------

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

//----------------------------------------------------------------------------------------------------------------------------

#ifndef _WINDEF_
typedef unsigned char BYTE;
#endif

#ifndef REAL
typedef float REAL;
#endif

#ifndef dType
typedef unsigned char dType;
//typedef float dType;
#endif

#endif /* _DEF_H_ */
