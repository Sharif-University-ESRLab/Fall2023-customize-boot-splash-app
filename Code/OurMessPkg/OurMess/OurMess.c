#include <Uefi.h>

#include <Library/UefiLib.h>

#include <Library/DebugLib.h>

#include <Library/UefiBootServicesTableLib.h>

#include <Library/MemoryAllocationLib.h>

#include <Library/FileHandleLib.h>

#include <Protocol/SimpleFileSystem.h>




EFI_STATUS RenameFile(EFI_FILE_PROTOCOL *Current_Dir, CHAR16* OldName, CHAR16* NewName) {
    EFI_STATUS status;

    EFI_FILE_PROTOCOL *OldFile;
    status = Current_Dir->Open(
        Current_Dir, &OldFile,
        OldName,  // Old file name
        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
        0  // No special attributes
    );
    if (EFI_ERROR(status)) {
        Print(L"Failed to open file for renaming: %r\n", status);
        return status;
    }

    // Get information about the old file
    EFI_FILE_INFO *FileInfo;
    EFI_FILE_INFO *NewFileInfo;
    UINTN BufferSize = sizeof(EFI_FILE_INFO) + StrSize(OldName);
    FileInfo = AllocatePool(BufferSize);
    NewFileInfo = AllocatePool(BufferSize);

    if (FileInfo == NULL || NewFileInfo == NULL) {
        status = EFI_OUT_OF_RESOURCES;
        Print(L"Memory allocation failed: %r\n", status);
        if (FileInfo != NULL) {
            FreePool(FileInfo);
        }
        if (NewFileInfo != NULL) {
            FreePool(NewFileInfo);
        }
        OldFile->Close(OldFile);
        return status;
    }

    status = OldFile->GetInfo(OldFile, &gEfiFileInfoGuid, &BufferSize, FileInfo);
    if (EFI_ERROR(status)) {
        Print(L"Failed to get file info for renaming: %r\n", status);
        FreePool(FileInfo);
        FreePool(NewFileInfo);
        OldFile->Close(OldFile);
        return status;
    }

    // Set the new file name in the file info structure
    StrCpyS(FileInfo->FileName, StrSize(NewName), NewName);

    // Set the new file name using SetInfo
    status = OldFile->SetInfo(OldFile, &gEfiFileInfoGuid, BufferSize, FileInfo);
    if (EFI_ERROR(status)) {
        Print(L"Failed to set new file name: %r\n", status);
        FreePool(FileInfo);
        FreePool(NewFileInfo);
        OldFile->Close(OldFile);
        return status;
    }

    // Clean up and close the old file
    FreePool(FileInfo);
    FreePool(NewFileInfo);
    OldFile->Close(OldFile);

    return EFI_SUCCESS;
}

EFI_STATUS GetOldFileName(CHAR16* Buffer, CHAR16** OldFileName) {
    // Allocate memory for the old file name
    *OldFileName = AllocateCopyPool(StrSize(Buffer), Buffer);
    if (*OldFileName == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    return EFI_SUCCESS;
}




void PrintDirectoryInfo(EFI_FILE_PROTOCOL *Directory)
{
    EFI_FILE_INFO *FileInfo;
    EFI_STATUS status;
    UINTN BufferSize;
    CHAR16 FileName[256];

    Directory->SetPosition(Directory, 0);

    do {
        BufferSize = sizeof(EFI_FILE_INFO) + sizeof(FileName);
        FileInfo = AllocatePool(BufferSize);

        if (FileInfo == NULL) {
            status = EFI_OUT_OF_RESOURCES;
            break;
        }

        status = Directory->Read(Directory, &BufferSize, FileInfo);

        if (!EFI_ERROR(status) && BufferSize > 0) {
            StrCpyS(FileName, sizeof(FileName) / sizeof(FileName[0]), FileInfo->FileName);

            // Check if the file name ends with ".bmp"
            UINTN FileNameLen = StrLen(FileName);
            if (FileNameLen >= 4 && StrCmp(FileName + FileNameLen - 4, L".bmp") == 0) {
                Print(L"IMAGE PATH: %s\n", FileName);
            }
        }

        FreePool(FileInfo);

    } while (!EFI_ERROR(status) && BufferSize > 0);
}

EFI_STATUS GetInput(CHAR16* Buffer, UINTN BufferSize){
    EFI_STATUS status;
    EFI_INPUT_KEY Key;
    UINTN Index = 0;
    UINTN Pos = 0;
    Buffer[0] = '\0';

    while(Index < BufferSize - 1){
        status = gBS->WaitForEvent(1, &gST->ConIn->WaitForKey, &Index);
        if(EFI_ERROR(status)){
            return status;
        }
        status = gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
        if(EFI_ERROR(status)){
            return status;
        }
        if(Key.UnicodeChar == L'\r'){
            break;
        }
        if(Key.ScanCode == SCAN_DELETE){
            if(Pos > 0){
                Buffer[Pos] = L'\0';
                Pos --;
                gST->ConOut->OutputString(gST->ConOut, L"\b \b");
            }
            continue;
        }
        Buffer[Pos] = Key.UnicodeChar;
        Pos = Pos + 1;
        Buffer[Pos] = L'\0';
        gST->ConOut->OutputString(gST->ConOut, &Key.UnicodeChar);
    }
    Buffer[Pos] = L'\0';
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

  EFI_STATUS status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
 
  status = gBS->LocateProtocol(
        &gEfiSimpleFileSystemProtocolGuid,
        NULL,
        (VOID**)&FileSystem
    );
   
   Print(L"Boot was: %r\n", status);
   
   EFI_FILE_PROTOCOL *Root;
   status = FileSystem->OpenVolume(FileSystem, &Root);
   Print(L"Location Root was: %r\n", status);
   if (EFI_ERROR(status)) {
        return status;
    }
    
    EFI_FILE_PROTOCOL *Current_Dir = Root;

    while (1) {
    PrintDirectoryInfo(Current_Dir);
    Print(L"\nYou should first replace the current Logo's name with your desired path to save as a checkpoint.\nThe command format is: rename Logo *new_path*\n");
    Print(L"To set a new logo, the command format is: Rename *new_logo_path*\n");
    CHAR16 Buffer[256];
    status = GetInput(Buffer, sizeof(Buffer)/sizeof(Buffer[0]));
    if (EFI_ERROR(status)) {
        Print(L"Error Reading String: %r\n", status);
    }
    else if (StrnCmp(Buffer, L"rename Logo", 11) == 0) {
        CHAR16 *NewFile;
        status = GetOldFileName(Buffer + 11, &NewFile);
        if (EFI_ERROR(status)) {
            Print(L"Error extracting old file name: %r\n", status);
        }
        status = RenameFile(Current_Dir, L"Logo.bmp", NewFile);
        Print(L"\nRename status: %r\n", status);

        FreePool(NewFile);
    }
    else if (StrCmp(Buffer, L"leave") == 0){
            Print(L"Process finished.\n");
            return EFI_SUCCESS;}
    else if (StrnCmp(Buffer, L"Rename", 6) == 0) {
        CHAR16 *OldFileName;
        status = GetOldFileName(Buffer + 6, &OldFileName);
        if (EFI_ERROR(status)) {
            Print(L"Error extracting old file name: %r\n", status);
            continue;  // Skip to the next iteration of the loop
        }

        // Change the old file's name to "Logo.bmp"
        status = RenameFile(Current_Dir, OldFileName, L"Logo.bmp");
        Print(L"\nRename status: %r\n", status);

        // Free allocated memory for old file name
        FreePool(OldFileName);
    	}
	}



    if (EFI_ERROR(status)) {
        Root->Close(Root);
        return status;
    }

  return EFI_SUCCESS;
}


