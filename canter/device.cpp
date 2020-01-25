#include <canter/device.hpp>

#include <ntifs.h>

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
    return NtOpenFile(
        &_hfile,
        static_cast<ULONG>(access_mask),
        &_oattrs,
        &_iosb,
        0,
        (_oattrs.Attributes & OBJ_OPENIF) ? FILE_OPEN_IF : FILE_OPEN);
}

NTSTATUS canter::device::close()
{
    return NtClose(_hfile);
}

NTSTATUS canter::device::write(
    IN PVOID buffer,
    IN ULONG count)
{
    LARGE_INTEGER offset;
    offset.QuadPart = 0;

    return NtWriteFile(
        _hfile,
        NULL,
        NULL,
        NULL,
        &_iosb,
        buffer,
        count,
        &offset,
        NULL);
}

NTSTATUS canter::device::control(
    IN ULONG code,
    IN PVOID in_buffer,
    IN ULONG in_count,
    OUT PVOID out_buffer,
    OUT ULONG out_count)
{
    return NtDeviceIoControlFile(
        _hfile,
        NULL,
        NULL,
        NULL,
        &_iosb,
        code,
        in_buffer,
        in_count,
        out_buffer,
        out_count);
}
