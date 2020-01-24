#include <canter/device.hpp>

canter::device::device(
    IN PCWSTR name,
    IN object_attribute attributes)
    : _hfile{ 0 }
{
    RtlInitUnicodeString(&_name, name);
    InitializeObjectAttributes(
        &_oattrs,
        &_name,
        static_cast<ULONG>(attributes),
        NULL,
        NULL);
}

NTSTATUS canter::device::open(
    IN access access_mask)
{
    return ZwOpenFile(
        &_hfile,
        static_cast<ULONG>(access_mask),
        &_oattrs,
        &_iosb,
        0,
        (_oattrs.Attributes & OBJ_OPENIF) ? FILE_OPEN_IF : FILE_OPEN);
}

NTSTATUS canter::device::close()
{
    return ZwClose(_hfile);
}
