#include <platform.h>
#include <phnt_windows.h>
#include <phnt.h>

uintptr_t __security_cookie = 0xBADBEEF;
#ifdef ARCH_x86
#define __gscall __fastcall
#else
#define __gscall __cdecl
#endif

void __gscall __security_check_cookie(uintptr_t _StackCookie) {
    if (_StackCookie != __security_cookie) NtTerminateProcess((HANDLE)-1, -1);
}
