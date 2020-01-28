#pragma once

#include <platform.h>
#include <ntddk.h>

namespace canter
{
    class string
    {
        UNICODE_STRING _nts;
        WCHAR _buff[64]; // TODO : dynamic size

    public:
        string();

        string(
            IN PCWSTR str);

        string(
            IN UNICODE_STRING &nts);

        string& operator=(
            IN PCWSTR str);

        string& operator=(
            IN UNICODE_STRING &nts);

        operator PCWSTR() const;

        operator PUNICODE_STRING();

        WCHAR& operator[](
            SIZE_T index);

        NTSTATUS printf(
            IN PCWSTR fmt,
            ...);
    };

    NTSTATUS display(
        IN string& str);

    NTSTATUS display(
        IN PCWSTR str);
}
