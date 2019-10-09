#ifdef ARCH_x86
#define _X86_
#endif
#ifdef ARCH_x64
#define _AMD64_
#endif

#include <ntddk.h>

NTSTATUS NTAPI NtDisplayString(PUNICODE_STRING);
NTSTATUS NTAPI NtDelayExecution(BOOLEAN, PLARGE_INTEGER);
NTSTATUS NTAPI NtTerminateProcess(HANDLE, NTSTATUS);

#define DELAY_MS(ms) ((ms) * -10000)

VOID NTAPI NtProcessStartup(
    IN PPEB peb)
{
    UNICODE_STRING hello, dot;
    LARGE_INTEGER delay;

    RtlInitUnicodeString(&hello, L"Hello, World! Catkitty sends greetings");
    RtlInitUnicodeString(&dot, L".");
    delay.QuadPart = DELAY_MS(1000);

    NtDisplayString(&hello);
    NtDisplayString(&dot);
    NtDelayExecution(FALSE, &delay);
    NtDisplayString(&dot);
    NtDelayExecution(FALSE, &delay);
    NtDisplayString(&dot);
    NtDelayExecution(FALSE, &delay);
    NtDisplayString(&dot);
    NtDelayExecution(FALSE, &delay);
    NtDisplayString(&dot);
    NtDelayExecution(FALSE, &delay);

    NtTerminateProcess((HANDLE)-1, 0);
}
