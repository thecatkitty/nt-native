#include <platform.h>
#include <ntddk.h>
#include <dietndk/nt.h>

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
