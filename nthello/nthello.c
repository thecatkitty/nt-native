#ifdef ARCH_x86
#define _X86_
#endif
#ifdef ARCH_x64
#define _AMD64_
#endif

#include <ntddk.h>

NTSTATUS NTAPI NtDisplayString(
    IN PUNICODE_STRING Message);
NTSTATUS NTAPI NtDelayExecution(
    IN BOOLEAN Alertable,
    IN PLARGE_INTEGER DelayInterval);
NTSTATUS NTAPI NtTerminateProcess(
    IN HANDLE ProcessHandle,
    IN NTSTATUS ExitStatus);

#define DELAY_MS(ms) ((ms) * -10000)

VOID NTAPI NtProcessStartup(
    IN PPEB peb)
{
    UNICODE_STRING hello, dot;
    LARGE_INTEGER delay;

    NTSTATUS status;
    HANDLE file;
    OBJECT_ATTRIBUTES oattrs;
    IO_STATUS_BLOCK iosb;
    UNICODE_STRING device = RTL_CONSTANT_STRING(L"\\Device\\BVidCelo");
    InitializeObjectAttributes(
        &oattrs,
        &device,
        OBJ_OPENIF,
        NULL,
        NULL);
    status = ZwOpenFile(
        &file,
        GENERIC_READ | GENERIC_WRITE,
        &oattrs,
        &iosb,
        0,
        FILE_OPEN);

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

    if (NT_SUCCESS(status)) {
        ZwClose(file);
    }
    NtTerminateProcess((HANDLE)-1, 0);
}
