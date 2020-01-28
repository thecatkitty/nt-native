#ifdef ARCH_x86
#ifndef _X86_
#define _X86_
#endif
#endif // ARCH_x86

#ifdef ARCH_x64
#ifndef _AMD64_
#define _AMD64_
#endif
#endif // ARCH_x64

#include <ntddk.h>

NTSYSCALLAPI NTSTATUS NTAPI NtDisplayString(
    IN PUNICODE_STRING DisplayString);

NTSYSCALLAPI NTSTATUS NTAPI NtDelayExecution(
    IN BOOLEAN Alertable,
    IN LARGE_INTEGER* Interval);

NTSYSCALLAPI NTSTATUS NTAPI NtTerminateProcess(
    IN HANDLE ProcessHandle,
    IN NTSTATUS ExitStatus);


VOID NTAPI NtProcessStartup(
    IN PPEB peb)
{
    UNICODE_STRING hello;
    LARGE_INTEGER delay;
    RtlInitUnicodeString(&hello, L"Hello World!");
    NtDisplayString(&hello);
    delay.QuadPart = -50000000;
    NtDelayExecution(FALSE, &delay);
    NtTerminateProcess((HANDLE)-1, STATUS_SUCCESS);
}
