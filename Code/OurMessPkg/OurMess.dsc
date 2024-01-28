[Defines]

  PLATFORM_NAME                  = OurMess

  PLATFORM_GUID                  = f67df959-c108-4755-a6df-6204a4719d22

  PLATFORM_VERSION               = 0.1

  DSC_SPECIFICATION              = 0x00010005

  OUTPUT_DIRECTORY               = Build/OurMess

  SUPPORTED_ARCHITECTURES        = IA32|X64|ARM|AARCH64|RISCV64

  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT

  SKUID_IDENTIFIER               = DEFAULT

[LibraryClasses]

UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf 

UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf

DebugLib|MdePkg/Library/UefiDebugLibConOut/UefiDebugLibConOut.inf

BaseLib|MdePkg/Library/BaseLib/BaseLib.inf

PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf

BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf

RegisterFilterLib|MdePkg/Library/RegisterFilterLibNull/RegisterFilterLibNull.inf

PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf   

DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf

UefiLib|MdePkg/Library/UefiLib/UefiLib.inf

MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf

DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf 

UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf

UefiFileHandleLib|MdePkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf

[Components]

  OurMessPkg/OurMess/OurMess.inf
