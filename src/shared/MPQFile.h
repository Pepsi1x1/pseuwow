#ifndef MPQFILE_H
#define MPQFILE_H

#define _COMMON_NO_THREADS
#define __STORMLIB_SELF__               // Don't use StormLib.lib
#include "common.h"
#include <StormLib.h>

class MPQFile
{
public:
    MPQFile(const char*);
	~MPQFile();
    inline bool IsOpen(void) { return _isopen; }
    ByteBuffer ReadFile(const char*);
    uint32 GetFileSize(const char*);
    bool HasFile(const char*);
	void Close(void);

private:
    HANDLE _mpq;
    bool _isopen;

};

#endif
