#ifndef __BTYPEIO_H__

#define __BTYPEIO_H__

#include "btype.h"

#ifdef __cplusplus
extern "C" {
#endif

BYTE freadbyte(FILE *fp, int *err);
WORD freadword(FILE *fp, int *err);
DWORD freaddword(FILE *fp, int *err);

int fwritebyte(FILE *fp, BYTE b);
int fwriteword(FILE *fp, WORD w);
int fwritedword(FILE *fp, DWORD dw);

#ifdef __cplusplus
}
#endif

#endif
