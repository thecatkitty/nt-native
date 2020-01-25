#pragma once

#include <platform.h>
#include <dietndk/nt.h>
#include <cstdint>

namespace canter
{
    struct process {
        static NTSTATUS delay(
            IN int64_t duration);

        static NTSTATUS terminate(
            IN NTSTATUS status);

        static PUNICODE_STRING get_path(
            IN PVOID peb);

        static PUNICODE_STRING get_command_line(
            IN PVOID peb);
    };
}

#define CANTER_DURATION_MS(ms) ((ms) * -10000)
