#pragma once

#include <platform.h>
#include <ntifs.h>


#define CANTER_FLAG_FIELD(name, value_type)                                   \
    constexpr name operator|(                                                 \
        IN name left,                                                         \
        IN name right)                                                        \
    {                                                                         \
        return static_cast<name>(                                             \
            static_cast<value_type>(left) | static_cast<value_type>(right));  \
    }                                                                         \
                                                                              \
    constexpr name operator&(                                                 \
        IN name left,                                                         \
        IN name right)                                                        \
    {                                                                         \
        return static_cast<name>(                                             \
            static_cast<value_type>(left) & static_cast<value_type>(right));  \
    }                                                                         \
    struct {}


namespace canter
{
    enum class access : ULONG
    {
        none         = 0,
        read         = 0x80000000L,
        write        = 0x40000000L,
        execute      = 0x20000000L,
        all          = 0x10000000L,
        remove       = 0x00010000L,
        read_control = 0x00020000L,
        write_dac    = 0x00040000L,
        write_owner  = 0x00080000L
    };

    enum class object_attribute : ULONG
    {
        none             = 0,
        inheritable      = 0x00000002L,
        permament        = 0x00000010L,
        exclusive        = 0x00000020L,
        case_insensitive = 0x00000040L,
        existent         = 0x00000080L,
        symlink          = 0x00000100L
    };

    enum class share_access : ULONG
    {
        none   = 0,
        read   = 0x00000001L,
        write  = 0x00000002L,
        remove = 0x00000004L
    };

    enum class synchronous_io : ULONG
    {
        none      = 0,
        alert     = 0x00000010,
        non_alert = 0x00000020
    };

#pragma warning(push)
#pragma warning(disable : 4094)
    CANTER_FLAG_FIELD(access, ULONG);
    CANTER_FLAG_FIELD(object_attribute, ULONG);
    CANTER_FLAG_FIELD(share_access, ULONG);
#pragma warning(pop)


    class device
    {
        UNICODE_STRING _name;
        HANDLE _hfile;
        OBJECT_ATTRIBUTES _oattrs;
        IO_STATUS_BLOCK _iosb;

    public:
        device(
            IN PCWSTR name,
            IN object_attribute attributes = object_attribute::none);

        NTSTATUS open(
            IN access access_mask,
            IN share_access share_access_mask = share_access::none,
            IN synchronous_io sync_io_type = synchronous_io::none);

        NTSTATUS close();

        NTSTATUS read(
            OUT PVOID buffer,
            IN ULONG count);

        NTSTATUS write(
            IN PVOID buffer,
            IN ULONG count);

        NTSTATUS control(
            IN ULONG code,
            IN PVOID in_buffer,
            IN ULONG in_count,
            OUT PVOID out_buffer = NULL,
            IN ULONG out_count = 0);
    };
}
