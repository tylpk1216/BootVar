#include <stdio.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseLib.h>
#include <Library/DevicePathLib.h>

// The caller is responsible for freeing this buffer with FreePool().
VOID* mGetVariable(CHAR16 *name, EFI_GUID *guid, UINTN *size)
{
    EFI_STATUS  status;
    UINTN       realSize;
    VOID        *value;

    // Try to get the variable size.
    value = NULL;
    realSize = 0;
    status = gRT->GetVariable(name, guid, NULL, &realSize, value);
    if (status != EFI_BUFFER_TOO_SMALL) {
        return NULL;
    }

    // Allocate buffer to get the variable.
    value = AllocatePool(realSize);
    if (value == NULL) {
        return NULL;
    }

    // Get the variable data.
    status = gRT->GetVariable(name, guid, NULL, &realSize, value);
    if (EFI_ERROR(status)) {
        FreePool(value);
        return NULL;
    }

    *size = realSize;
    return value;
}

int main(void)
{
    VOID *bootOrder;
    VOID *bootVar;
    UINTN size;
    UINT16 *bootNum;
    UINTN varCount;
    UINTN varNowCount;

    UINT16 bootString[10];
    UINT16 *desc;

    UINT16 filePathLen;
    EFI_DEVICE_PATH_PROTOCOL *protocol;

    char *ptr;

    bootOrder = mGetVariable(L"BootOrder", &gEfiGlobalVariableGuid, &size);
    if (bootOrder == NULL) {
        printf("Can't get BootOrder Variable \n");
        return -1;
    }

    varCount = size / 2;

    varNowCount = 1;
    bootNum = (UINT16*)bootOrder;
    while (varNowCount <= varCount) {
        UnicodeSPrint(bootString, sizeof(bootString), L"Boot%04x", *bootNum);

        bootVar = mGetVariable(bootString, &gEfiGlobalVariableGuid, &size);
        if (bootVar == NULL) {
            printf("Can't get Boot%04X Variable \n", *bootNum);
            return -1;
        }

        ptr = (char*)bootVar;

        desc = (UINT16*)(ptr + 6);
        Print(L"Boot%04X : %s \n", *bootNum, desc);

        filePathLen = *((UINT16*)(ptr + 4));
        protocol = (EFI_DEVICE_PATH_PROTOCOL*)(ptr + 6 + 2*(StrLen(desc)+1));

        Print(L"FilePath Length %02X \n", filePathLen);
        Print(L"FilePath.Type %02X \n", protocol->Type);
        Print(L"FilePath.SubType %02X \n", protocol->SubType);
        Print(L"%s \n", ConvertDevicePathToText(protocol, TRUE, TRUE));
        Print(L"\n");

        FreePool(bootVar);

        bootNum++;
        varNowCount++;
    }

    FreePool(bootOrder);

    return 0;
}
