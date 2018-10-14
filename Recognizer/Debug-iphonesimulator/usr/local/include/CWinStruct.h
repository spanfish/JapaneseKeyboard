//
//  CWinStruct.h
//  HandsInkRecognizer
//
//  Created by  on 12/02/07.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef HandsInkRecognizer_CWinStruct_h
#define HandsInkRecognizer_CWinStruct_h

#ifndef WIN32
typedef long int LONG;
// 2-D point with short coordinate
typedef struct tagPOINTS{
	short x;
	short y;
} POINTS, *PPOINTS;

 // 2-D point with int coordinate
typedef struct tagPOINT{
    int x;
    int y;
} POINT, *PPOINT;


typedef unsigned short WORD;
typedef short SHORT;


typedef struct {
    int left;
    int top;
    int right;
    int bottom;
} RECT;


#endif

#endif
