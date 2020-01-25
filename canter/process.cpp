#include <canter/process.hpp>


typedef struct _PEB_LDR_DATA* PPEB_LDR_DATA;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
    char Reserved1[16];
    PVOID Reserved2[10];
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

typedef VOID(NTAPI* PPS_POST_PROCESS_INIT_ROUTINE) (
    VOID);

typedef struct _PEB {
    char Reserved1[2];
    char BeingDebugged;
    char Reserved2[1];
    PVOID Reserved3[2];
    PPEB_LDR_DATA Ldr;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PVOID Reserved4[3];
    PVOID AtlThunkSListPtr;
    PVOID Reserved5;
    ULONG Reserved6;
    PVOID Reserved7;
    ULONG Reserved8;
    ULONG AtlThunkSListPtr32;
    PVOID Reserved9[45];
    char Reserved10[96];
    PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
    char Reserved11[128];
    PVOID Reserved12[1];
    ULONG SessionId;
} PEB, *PPEB;


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
