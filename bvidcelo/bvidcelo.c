#include <ntddk.h>
#include <bootvid.h>


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

    VidInitialize(TRUE);
    VidResetDisplay(FALSE);

    VidSolidColorFill(0, 0, 639, 479, VGA_COLOR_BLUE);
    VidSetTextColor(VGA_COLOR_BRIGHT_PURPLE);

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

    VidCleanUp();

    DbgPrint("BVidCelo got closed\n");
    return STATUS_SUCCESS;
}


DRIVER_DISPATCH BVidWrite;
NTSTATUS BVidWrite(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp)
{
    NTSTATUS Status = STATUS_SUCCESS;
    PVOID UserData;
    ULONG DataSize;

    PIO_STACK_LOCATION IrpStack = IoGetCurrentIrpStackLocation(Irp);

    DataSize = IrpStack->Parameters.Write.Length;
    UserData = Irp->AssociatedIrp.SystemBuffer;

    VidDisplayString((PUCHAR)UserData);

    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = DataSize;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Status;
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
    UNREFERENCED_PARAMETER(RegistryPath);
    DbgPrint("Hello, World! BVidCelo sends greetings...\n");

    //PDEVICE_EXTENSION DeviceExtension;
    PDEVICE_OBJECT DeviceObject;
    UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\Device\\BVidCelo");
    NTSTATUS Status;

    Status = IoCreateDevice(
        DriverObject,
        sizeof(DEVICE_EXTENSION),
        &DeviceName,
        FILE_DEVICE_VIDEO,
        0,
        FALSE,
        &DeviceObject);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    DeviceObject->Flags |= DO_BUFFERED_IO;

    DriverObject->MajorFunction[IRP_MJ_CREATE] = BVidCreate;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = BVidClose;
    DriverObject->MajorFunction[IRP_MJ_WRITE] = BVidWrite;
    DriverObject->DriverUnload = BVidUnload;

    return STATUS_SUCCESS;
}
