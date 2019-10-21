#define NTSTRSAFE_LIB

#include <platform.h>
#include <ntddk.h>
#include <ntddkbd.h>
#include <ntstrsafe.h>
#include <dietndk/nt.h>
#include <dietndk/str.h>

#define DELAY_MS(ms) ((ms) * -10000)

VOID NTAPI NtProcessStartup(
    IN PPEB peb)
{
    LARGE_INTEGER delay;
    UNICODE_STRING msg;

    RtlInitUnicodeString(&msg, L"Hello.\r\n");
    NtDisplayString(&msg);
    delay.QuadPart = DELAY_MS(1000);
    NtDelayExecution(FALSE, &delay);

    NTSTATUS status;
    HANDLE file;
    OBJECT_ATTRIBUTES oattrs;
    IO_STATUS_BLOCK iosb;
    UNICODE_STRING device = RTL_CONSTANT_STRING(L"\\Device\\KeyboardClass0");
    InitializeObjectAttributes(
        &oattrs,
        &device,
        OBJ_OPENIF,
        NULL,
        NULL);
    status = ZwOpenFile(
        &file,
        GENERIC_READ | GENERIC_WRITE | SYNCHRONIZE,
        &oattrs,
        &iosb,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        FILE_OPEN | FILE_SYNCHRONOUS_IO_NONALERT);

    if (!NT_SUCCESS(status)) {
        RtlInitUnicodeString(&msg,
            L"***ZwOpenFile: Unable to create keyboard device 0\r\n");
        NtDisplayString(&msg);
        delay.QuadPart = DELAY_MS(5000);
        NtDelayExecution(FALSE, &delay);
        NtTerminateProcess((HANDLE)-1, status);
    }

    RtlInitUnicodeString(&msg, L"Press some keys and have fun\r\n");
    NtDisplayString(&msg);

    KEYBOARD_INPUT_DATA kbdi;
    unsigned size = sizeof(kbdi);

    delay.QuadPart = DELAY_MS(50);

    BOOLEAN still = TRUE;
    while (still) {
        ZeroMemory(&kbdi, size);
        status = ZwReadFile(
            file,
            NULL,
            NULL,
            NULL,
            &iosb,
            &kbdi,
            size,
            NULL,
            NULL);

        if (!NT_SUCCESS(status)) {
            RtlInitUnicodeString(&msg,
                L"***ZwOpenFile: Unable to read keyboard device 0\r\n");
            NtDisplayString(&msg);
            RtlUnicodeStringPrintf(&msg, L"***Status code %08X\r\n", status);
            NtDisplayString(&msg);
            delay.QuadPart = DELAY_MS(5000);
            NtDelayExecution(FALSE, &delay);
            NtTerminateProcess((HANDLE)-1, status);
        }

        if (NT_SUCCESS(status)) {
            if (kbdi.MakeCode) {
                RtlUnicodeStringPrintf(&msg,
                    L"Scan code %02X %s\r\n",
                    kbdi.MakeCode,
                    kbdi.Flags & KEY_BREAK ? L"up" : L"down");
                NtDisplayString(&msg);
            }
            still = kbdi.MakeCode != 0x01; // Esc
        }
    }

    RtlInitUnicodeString(&msg, L"OK.\r\n");
    NtDisplayString(&msg);

    delay.QuadPart = DELAY_MS(1000);
    NtDelayExecution(FALSE, &delay);

    ZwClose(file);
    NtTerminateProcess((HANDLE)-1, STATUS_SUCCESS);
}
