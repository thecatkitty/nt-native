// Function prototypes extracted from NDK by Alex Ionescu
#pragma once

#include <ntdef.h>


//
// Boot Video Display Ownership Status
//
typedef enum _INBV_DISPLAY_STATE {
    INBV_DISPLAY_STATE_OWNED,
    INBV_DISPLAY_STATE_DISABLED,
    INBV_DISPLAY_STATE_LOST
} INBV_DISPLAY_STATE;

//
// Function Callbacks
//
typedef BOOLEAN(NTAPI* INBV_RESET_DISPLAY_PARAMETERS)(
    ULONG Cols,
    ULONG Rows);

typedef VOID(NTAPI* INBV_DISPLAY_STRING_FILTER)(
    PCHAR* Str);


//
// Ownership Functions
//
VOID NTAPI InbvAcquireDisplayOwnership(
    VOID);

BOOLEAN NTAPI InbvCheckDisplayOwnership(
    VOID);

VOID NTAPI InbvNotifyDisplayOwnershipLost(
    IN INBV_RESET_DISPLAY_PARAMETERS Callback);

//
// Installation Functions
//
VOID NTAPI InbvEnableBootDriver(
    IN BOOLEAN Enable);

VOID NTAPI InbvInstallDisplayStringFilter(
    IN INBV_DISPLAY_STRING_FILTER DisplayFilter);

BOOLEAN NTAPI InbvIsBootDriverInstalled(
    VOID);

//
// Display Functions
//
BOOLEAN NTAPI InbvDisplayString(
    IN PCHAR String);

BOOLEAN NTAPI InbvEnableDisplayString(
    IN BOOLEAN Enable);

BOOLEAN NTAPI InbvResetDisplay(
    VOID);

VOID NTAPI InbvSetScrollRegion(
    IN ULONG Left,
    IN ULONG Top,
    IN ULONG Right,
    IN ULONG Bottom);

VOID NTAPI InbvSetTextColor(
    IN ULONG Color);

VOID NTAPI InbvSolidColorFill(
    IN ULONG Left,
    IN ULONG Top,
    IN ULONG Right,
    IN ULONG Bottom,
    IN ULONG Color);

VOID NTAPI InbvSetProgressBarSubset(
    IN ULONG Floor,
    IN ULONG Ceiling);
