#include <stdio.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PrintLib.h>

// The caller is responsible for freeing this buffer with FreePool().
VOID* mGetVariable(CHAR16 *name, EFI_GUID *guid, UINTN *size)
{
    EFI_STATUS  status;
    UINTN       realSize;
    VOID        *value;

    //ASSERT(name != NULL);
    //ASSERT(guid != NULL);

    //
    // Try to get the variable size.
    //
    value = NULL;
    realSize = 0;
    status = gRT->GetVariable(name, guid, NULL, &realSize, value);
    if (status != EFI_BUFFER_TOO_SMALL) {
        return NULL;
    }

    //
    // Allocate buffer to get the variable.
    //
    value = AllocatePool(realSize);
    if (value == NULL) {
        return NULL;
    }

    //
    // Get the variable data.
    //
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
    VOID *value;
    UINTN size;

    UINTN varCount;
    UINTN i;

    UINT16 bootString[10];
    UINT16 *desc;

    value = mGetVariable(L"BootOrder", &gEfiGlobalVariableGuid, &size);
    if (value == NULL) {
        printf("Can't get BootOrder Variable \n");
        return -1;
    }

    FreePool(value);

    varCount = size / 2;
    for (i = 0; i < varCount; i++) {
        UnicodeSPrint(bootString, sizeof(bootString), L"Boot%04x", i);

        value = mGetVariable(bootString, &gEfiGlobalVariableGuid, &size);
        if (value == NULL) {
            printf("Can't get Boot%04X Variable \n", i);
            return -1;
        }

        desc = (UINT16*)((char*)value + 6);
        Print(L"Boot%04X¡G%s \n", i, desc);
        FreePool(value);
    }

    return 0;
}


