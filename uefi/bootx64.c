typedef unsigned long long UINTN;
typedef unsigned long long EFI_STATUS;
typedef unsigned short CHAR16;
typedef void* EFI_HANDLE;
typedef unsigned long long EFI_PHYSICAL_ADDRESS;

#define EFI_SUCCESS 0
#define EFI_ERROR(value) ((value) != EFI_SUCCESS)
#define EFI_FILE_MODE_READ 0x0000000000000001ULL
#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x0000000000000001ULL
#define EFI_LOADED_IMAGE_PROTOCOL_GUID \
    {0x5B1B31A1,0x9562,0x11d2,{0x8e,0x3f,0x00,0xa0,0xc9,0x69,0x72,0x3b}}
#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
    {0x0964e5b2,0x6459,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct {
    unsigned int Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} EFI_GUID;

typedef struct {
    UINTN Revision;
    UINTN ParentHandle;
    UINTN SystemTable;
    UINTN DeviceHandle;
    UINTN FilePath;
    UINTN Reserved;
    UINTN LoadOptionsSize;
    UINTN LoadOptions;
    UINTN ImageBase;
    UINTN ImageSize;
    unsigned int CodeType;
    unsigned int DataType;
} EFI_LOADED_IMAGE;

typedef struct EFI_FILE_PROTOCOL EFI_FILE_PROTOCOL;
typedef EFI_STATUS (*EFI_FILE_OPEN)(EFI_FILE_PROTOCOL*, EFI_FILE_PROTOCOL**, CHAR16*, UINTN, UINTN);
typedef EFI_STATUS (*EFI_FILE_CLOSE)(EFI_FILE_PROTOCOL*);
typedef EFI_STATUS (*EFI_FILE_READ)(EFI_FILE_PROTOCOL*, UINTN*, void*);

typedef struct EFI_FILE_PROTOCOL {
    UINTN Revision;
    EFI_FILE_OPEN Open;
    EFI_FILE_CLOSE Close;
    void* Delete;
    EFI_FILE_READ Read;
    void* Write;
    void* GetPosition;
    void* SetPosition;
    void* GetInfo;
    void* SetInfo;
    void* Flush;
} EFI_FILE_PROTOCOL;

typedef struct {
    UINTN Revision;
    EFI_STATUS (*OpenVolume)(void*, EFI_FILE_PROTOCOL**);
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef struct {
    EFI_STATUS (*Reset)(void*, unsigned char);
    EFI_STATUS (*OutputString)(void*, CHAR16*);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct {
    UINTN Hdr[3];
    CHAR16* FirmwareVendor;
    unsigned int FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    void* ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdErr;
    void* RuntimeServices;
    void* BootServices;
} EFI_SYSTEM_TABLE;

typedef struct {
    EFI_STATUS (*RaiseTPL)(UINTN);
    void (*RestoreTPL)(UINTN);
    void* AllocatePages;
    void* FreePages;
    void* GetMemoryMap;
    void* AllocatePool;
    void* FreePool;
    void* CreateEvent;
    void* SetTimer;
    void* WaitForEvent;
    void* SignalEvent;
    void* CloseEvent;
    void* CheckEvent;
    void* InstallProtocolInterface;
    void* ReinstallProtocolInterface;
    void* UninstallProtocolInterface;
    void* HandleProtocol;
} EFI_BOOT_SERVICES;

typedef EFI_STATUS (*EFI_HANDLE_PROTOCOL)(EFI_HANDLE, EFI_GUID*, void**);
typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES)(EFI_HANDLE, UINTN);

typedef struct {
    UINTN Revision;
    UINTN ParentHandle;
    UINTN SystemTable;
    UINTN DeviceHandle;
    UINTN FilePath;
    UINTN Reserved;
    UINTN LoadOptionsSize;
    UINTN LoadOptions;
    UINTN ImageBase;
    UINTN ImageSize;
    unsigned int CodeType;
    unsigned int DataType;
} LOADED_IMAGE;

typedef struct {
    UINTN Revision;
    EFI_STATUS (*OpenVolume)(void*, EFI_FILE_PROTOCOL**);
} SIMPLE_FS;

static void print(EFI_SYSTEM_TABLE* table, const CHAR16* text)
{
    table->ConOut->OutputString(table->ConOut, (CHAR16*)text);
}

__declspec(dllexport) EFI_STATUS efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE* table)
{
    (void)image;
    print(table, u"EDORA OS UEFI BOOTX64\r\n");
    print(table, u"MADE BY XIAO LOUIE\r\n");
    print(table, u"UEFI firmware detected successfully.\r\n");
    print(table, u"This loader is ready for the x86 kernel handoff.\r\n");
    print(table, u"Kernel mode remains RAMFS-based.\r\n");
    while (1)
    {
        __asm__ volatile("hlt");
    }
    return EFI_SUCCESS;
}
