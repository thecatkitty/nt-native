#ifndef _DNDK_STR_H_
#define _DNDK_STR_H_

#include <ntdef.h>

inline VOID ZeroMemory(
    IN PVOID dest,
    IN SIZE_T count)
{
    PCHAR pc = (PCHAR)dest;
    while (count) {
        *pc = 0;
        count--;
        pc++;
    }
}

#endif // _DNDK_STR_H_
