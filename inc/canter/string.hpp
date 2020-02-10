#pragma once

#include <platform.h>
#include <phnt_windows.h>
#include <phnt.h>

namespace canter
{
    class string
    {
        UNICODE_STRING _nts;
        WCHAR _buff[64]; // TODO : dynamic size

    public:
        string();

        string(
            IN PWSTR str);

        string(
            IN UNICODE_STRING &nts);

        string& operator=(
            IN PWSTR str);

        string& operator=(
            IN UNICODE_STRING &nts);

        operator PWSTR();

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
