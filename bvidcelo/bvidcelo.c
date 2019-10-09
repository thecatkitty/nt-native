#include <ntddk.h>


typedef struct _BVID_DEVICE_EXTENSION {
    INT i;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;


DRIVER_DISPATCH BVidCreate;
NTSTATUS BVidCreate(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);
    UNREFERENCED_PARAMETER(Irp);
    DbgPrint("BVidCelo got created\n");
    return STATUS_SUCCESS;
}


DRIVER_DISPATCH BVidClose;
NTSTATUS BVidClose(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);
    UNREFERENCED_PARAMETER(Irp);
    DbgPrint("BVidCelo got closed\n");
    return STATUS_SUCCESS;
}


DRIVER_UNLOAD BVidUnload;
VOID BVidUnload(
    IN PDRIVER_OBJECT DriverObject)
{
    DbgPrint("BVidCelo is being unloaded...\n");
    IoDeleteDevice(DriverObject->DeviceObject);
}


NTSTATUS NTAPI DriverEntry(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);
    DbgPrint("Hello, World! BVidCelo sends greetings...\n");

    //PDEVICE_EXTENSION DeviceExtension;
    PDEVICE_OBJECT DeviceObject;
    UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\Device\\BVidCelo");
    NTSTATUS Status;

    Status = IoCreateDevice(DriverObject,
        sizeof(DEVICE_EXTENSION),
        &DeviceName,
        FILE_DEVICE_VIDEO,
        0,
        FALSE,
        &DeviceObject);
    if (!NT_SUCCESS(Status)) return Status;

    DriverObject->MajorFunction[IRP_MJ_CREATE] = BVidCreate;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = BVidClose;
    DriverObject->DriverUnload = BVidUnload;

    return STATUS_SUCCESS;
}
