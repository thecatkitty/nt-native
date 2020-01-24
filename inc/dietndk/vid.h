// Vid* (bootvid.dll) prototypes based on ReactOS documentation
#ifndef _DNDK_VID_H_
#define _DNDK_VID_H_

#include <ntdef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#define VGA_COLOR_BLACK                      0
#define VGA_COLOR_RED                        1
#define VGA_COLOR_GREEN                      2
#define VGA_COLOR_GR                         3
#define VGA_COLOR_BULE                       4
#define VGA_COLOR_DARK_MEGAENTA              5
#define VGA_COLOR_TURQUOISE                  6
#define VGA_COLOR_GRAY                       7
#define VGA_COLOR_BRIGHT_GRAY                8
#define VGA_COLOR_BRIGHT_RED                 9
#define VGA_COLOR_BRIGHT_GREEN               10
#define VGA_COLOR_BRIGHT_YELLOW              11
#define VGA_COLOR_BRIGHT_BULE                12
#define VGA_COLOR_BRIGHT_PURPLE              13
#define VGA_COLOR_BRIGHT_TURQUOISE           14
#define VGA_COLOR_WHITE                      15


//
// Installation Functions
//
NTKERNELAPI BOOLEAN NTAPI VidInitialize(
    IN BOOLEAN SetMode);

NTKERNELAPI VOID NTAPI VidCleanUp(
    VOID);

//
// Display Functions
//
NTKERNELAPI VOID NTAPI VidDisplayString(
    IN PUCHAR String);

NTKERNELAPI VOID NTAPI VidDisplayStringXY(
    IN PUCHAR String,
    IN ULONG Left,
    IN ULONG Top,
    IN BOOLEAN Transparent);

NTKERNELAPI VOID NTAPI VidResetDisplay(
    IN BOOLEAN HalReset);

NTKERNELAPI VOID NTAPI VidSetScrollRegion(
    IN ULONG Left,
    IN ULONG Top,
    IN ULONG Right,
    IN ULONG Bottom);

NTKERNELAPI ULONG NTAPI VidSetTextColor(
    IN ULONG Color);

NTKERNELAPI VOID NTAPI VidSolidColorFill(
    IN ULONG Left,
    IN ULONG Top,
    IN ULONG Right,
    IN ULONG Bottom,
    IN UCHAR Color);

NTKERNELAPI VOID NTAPI VidBufferToScreenBlt(
    IN PUCHAR Buffer,
    IN ULONG Left,
    IN ULONG Top,
    IN ULONG Width,
    IN ULONG Height,
    IN ULONG Delta);

NTKERNELAPI VOID NTAPI VidScreenToBufferBlt(
    IN PUCHAR Buffer,
    IN ULONG Left,
    IN ULONG Top,
    IN ULONG Width,
    IN ULONG Height,
    IN ULONG Delta);

NTKERNELAPI VOID NTAPI VidBitBlt(
    IN PUCHAR Buffer,
    IN ULONG Left,
    IN ULONG Top);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _DNDK_VID_H_
