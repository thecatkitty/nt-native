#include <canter/process.hpp>


NTSTATUS canter::process::delay(
    IN int64_t duration)
{
    LARGE_INTEGER delay;
    delay.QuadPart = duration;
    return NtDelayExecution(FALSE, &delay);
}

NTSTATUS canter::process::terminate(
    IN NTSTATUS status)
{
    return NtTerminateProcess(reinterpret_cast<HANDLE>(-1), status);
}

PUNICODE_STRING canter::process::get_path(
    IN PVOID peb)
{
    auto ppeb = reinterpret_cast<PPEB>(peb);
    return &ppeb->ProcessParameters->ImagePathName;
}

PUNICODE_STRING canter::process::get_command_line(
    IN PVOID peb)
{
    auto ppeb = reinterpret_cast<PPEB>(peb);
    return &ppeb->ProcessParameters->CommandLine;
}
