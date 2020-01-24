#include <canter/device.hpp>
#include <canter/process.hpp>


VOID NTAPI NtProcessStartup(
    IN PPEB peb)
{
    canter::device vid{
        L"\\Device\\BVidCelo",
        canter::object_attribute::existent
    };

    auto status = vid.open(
        canter::access::read | canter::access::write);
    if (status == STATUS_SUCCESS)
    {
        canter::process::delay(CANTER_DURATION_MS(1000));
        vid.close();

        canter::process::terminate(STATUS_SUCCESS);
    }

    canter::process::terminate(STATUS_SUCCESS);
}
