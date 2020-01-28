#define NTSTRSAFE_LIB

#include <canter/device.hpp>
#include <canter/process.hpp>
#include <canter/string.hpp>
#include <ntddkbd.h>


using namespace canter;

VOID NTAPI NtProcessStartup(
    IN PPEB peb)
{
    display(L"Hello.\r\n");
    process::delay(CANTER_DURATION_MS(1000));

    device keyb{
        L"\\Device\\KeyboardClass0",
        object_attribute::existent
    };

    NTSTATUS status;
    status = keyb.open(
        access::read | access::write,
        share_access::read | share_access::write,
        synchronous_io::non_alert);

    if (!NT_SUCCESS(status)) {
        display(L"***ZwOpenFile: Unable to create keyboard device 0\r\n");

        process::delay(CANTER_DURATION_MS(5000));
        process::terminate(status);
    }

    display(L"Press some keys and have fun\r\n");

    KEYBOARD_INPUT_DATA kbdi;
    unsigned size{ sizeof(kbdi) };
    string msg{};

    BOOLEAN still{ TRUE };
    while (still) {
        RtlZeroMemory(&kbdi, size);
        status = keyb.read(&kbdi, size);

        if (!NT_SUCCESS(status)) {
            display(L"***ZwOpenFile: Unable to read keyboard device 0\r\n");

            msg.printf(L"***Status code %08X\r\n", status);
            display(msg);

            process::delay(CANTER_DURATION_MS(5000));
            process::terminate(status);
        }

        if (NT_SUCCESS(status)) {
            if (kbdi.MakeCode) {
                msg.printf(
                    L"Scan code %02X %s\r\n",
                    kbdi.MakeCode,
                    kbdi.Flags & KEY_BREAK ? L"up" : L"down");
                display(msg);
            }
            still = kbdi.MakeCode != 0x01; // Esc
        }
    }

    display(L"OK.\r\n");

    process::delay(CANTER_DURATION_MS(1000));

    keyb.close();
    process::terminate(STATUS_SUCCESS);
}
