#include <canter/device.hpp>
#include <canter/process.hpp>


#define BUFFER_LENGTH 100


static VOID UnicodeToAscii7(
    IN PUNICODE_STRING unicode,
    OUT PSTR ascii7,
    IN USHORT length);


VOID NTAPI NtProcessStartup(
    IN PPEB peb)
{
    canter::device vid{
        L"\\Device\\BVidCelo",
        canter::object_attribute::existent
    };

    auto status = vid.open(
        canter::access::read | canter::access::write);
    if (NT_SUCCESS(status))
    {
        char msg[] = "Hello World!\nI love programming!\n";
        char nl[] = "\n";
        char buff[BUFFER_LENGTH];

        vid.write(msg, sizeof(msg));
        canter::process::delay(CANTER_DURATION_MS(1500));

        UnicodeToAscii7(
            canter::process::get_path(peb),
            buff,
            BUFFER_LENGTH);
        vid.write(buff, BUFFER_LENGTH);
        vid.write(nl, sizeof(nl));
        canter::process::delay(CANTER_DURATION_MS(1500));

        UnicodeToAscii7(
            canter::process::get_command_line(peb),
            buff,
            BUFFER_LENGTH);
        vid.write(buff, BUFFER_LENGTH);
        canter::process::delay(CANTER_DURATION_MS(1500));

        vid.close();

        canter::process::terminate(STATUS_SUCCESS);
    }

    canter::process::terminate(status);
}


VOID UnicodeToAscii7(
    IN PUNICODE_STRING unicode,
    OUT PSTR ascii7,
    IN USHORT length)
{
    USHORT i;
    for (i = 0; (i < unicode->Length) && (i < length - 1); i++)
    {
        ascii7[i] = unicode->Buffer[i] > 0x7F ? '?' : (CHAR)unicode->Buffer[i];
    }
    ascii7[i] = 0;
}
