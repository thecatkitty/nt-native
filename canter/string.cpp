#define NTSTRSAFE_LIB

#include <canter/string.hpp>
#include <dietndk/nt.h>
#include <ntstrsafe.h>
#include <cstdarg>


canter::string::string()
{
    ZeroMemory(_buff, sizeof(_buff));
    RtlInitEmptyUnicodeString(&_nts, _buff, sizeof(_buff));
}

canter::string::string(
    IN PCWSTR str)
{
    RtlInitUnicodeString(&_nts, str);
}

canter::string::string(
    IN UNICODE_STRING& nts)
{
    RtlCopyUnicodeString(&_nts, &nts);
}

canter::string& canter::string::operator=(
    IN PCWSTR str)
{
    RtlInitUnicodeString(&_nts, str);
    return *this;
}

canter::string& canter::string::operator=(
    IN UNICODE_STRING& nts)
{
    RtlCopyUnicodeString(&_nts, &nts);
    return *this;
}

canter::string::operator PCWSTR() const
{
    return _nts.Buffer;
}

canter::string::operator PUNICODE_STRING()
{
    return &_nts;
}

WCHAR& canter::string::operator[](
    SIZE_T index)
{
    return _nts.Buffer[index];
}

NTSTATUS canter::string::printf(
    IN PCWSTR fmt,
    ...)
{
    va_list args;
    va_start(args, fmt);
    auto status = RtlUnicodeStringVPrintf(&_nts, fmt, args);
    va_end(args);
    return status;
}

NTSTATUS canter::display(
    IN string& str)
{
    return NtDisplayString(str);
}

NTSTATUS canter::display(
    IN PCWSTR str)
{
    UNICODE_STRING nts;
    RtlInitUnicodeString(&nts, str);
    return NtDisplayString(&nts);
}
