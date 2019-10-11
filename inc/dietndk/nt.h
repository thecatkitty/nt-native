// A subset of Nt* (ntoskrnl.exe) prototypes extracted from NDK
// by Alex Ionescu
#ifndef _DNDK_NT_H_
#define _DNDK_NT_H_

#include <ntdef.h>

NTSYSCALLAPI NTSTATUS NTAPI NtDisplayString(
    IN PUNICODE_STRING DisplayString);

NTSYSCALLAPI NTSTATUS NTAPI NtDelayExecution(
    IN BOOLEAN Alertable,
    IN LARGE_INTEGER* Interval);

NTSYSCALLAPI NTSTATUS NTAPI NtTerminateProcess(
    IN HANDLE ProcessHandle,
    IN NTSTATUS ExitStatus);

#endif // _DNDK_NT_H_
