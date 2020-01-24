#pragma once

#include <platform.h>
#include <ntddk.h>
#include <dietndk/nt.h>
#include <cstdint>

namespace canter
{
    struct process {
        inline static NTSTATUS delay(
            IN int64_t duration)
        {
            LARGE_INTEGER delay;
            delay.QuadPart = duration;
            return NtDelayExecution(FALSE, &delay);
        }

        inline static NTSTATUS terminate(
            IN NTSTATUS status)
        {
            return NtTerminateProcess(reinterpret_cast<HANDLE>(-1), status);
        }
    };
}

#define CANTER_DURATION_MS(ms) ((ms) * -10000)