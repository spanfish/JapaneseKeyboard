//---------------------------------------------------------------------------

#ifndef DictionaryPathH
#define DictionaryPathH
//---------------------------------------------------------------------------
#if defined(WIN32)
#include "windows.h"
void SetFilePathToDefault(HINSTANCE htinst);
#endif
bool SetFilePath(const char *pathname);
void GetFileName(char *pathNameBuffer, const char *fileName);
#endif
