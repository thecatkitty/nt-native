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
    IN access access_mask,
    IN share_access share_access_mask,
    IN synchronous_io sync_io_type)
{
    ACCESS_MASK DesiredAccess{
        static_cast<ULONG>(access_mask) };
    ULONG OpenOptions{ 0 };

    if (_oattrs.Attributes & OBJ_OPENIF)
    {
        OpenOptions |= FILE_OPEN_IF;
    }
    else
    {
        OpenOptions |= FILE_OPEN;
    }

    if (sync_io_type != synchronous_io::none)
    {
        DesiredAccess |= SYNCHRONIZE;
        OpenOptions |= static_cast<ULONG>(sync_io_type);
    }

    return NtOpenFile(
        &_hfile,
        DesiredAccess,
        &_oattrs,
        &_iosb,
        static_cast<ULONG>(share_access_mask),
        OpenOptions);
}

NTSTATUS canter::device::close()
{
    return NtClose(_hfile);
}

NTSTATUS canter::device::read(
    OUT PVOID buffer,
    IN ULONG count)
{
    return NtReadFile(
        _hfile,
        NULL,
        NULL,
        NULL,
        &_iosb,
        buffer,
        count,
        NULL,
        NULL);
}

NTSTATUS canter::device::write(
    IN PVOID buffer,
    IN ULONG count)
{
    return NtWriteFile(
        _hfile,
        NULL,
        NULL,
        NULL,
        &_iosb,
        buffer,
        count,
        NULL,
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
