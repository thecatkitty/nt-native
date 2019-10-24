#include <platform.h>
#include <ntddk.h>
#include <dietndk/nt.h>

#define DELAY_MS(ms) ((ms) * -10000)

VOID NTAPI NtProcessStartup(
    IN PPEB peb)
{
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

    delay.QuadPart = DELAY_MS(1000);
    NtDelayExecution(FALSE, &delay);

    if (NT_SUCCESS(status)) {
        ZwClose(file);
    }
    NtTerminateProcess((HANDLE)-1, 0);
}
