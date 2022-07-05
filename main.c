#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <taihen.h>
#include <psp2kern/kernel/modulemgr.h>

void _start() __attribute__ ((weak, alias ("module_start")));

static tai_hook_ref_t gHookRef;
static SceUID gHook;

typedef int pointer32;
typedef int SceSSize;
typedef SceSSize SceVSSize;
typedef uint SceUInt;
typedef unsigned char SceUChar8;
typedef signed int SceInt32;
typedef uint32_t SceUInt32;
typedef uint8_t SceByte8;
typedef double SceDouble64;
typedef struct SceLibStubTable_0x34 SceLibStubTable_0x34, *PSceLibStubTable_0x34;
typedef ushort SceUInt16;
typedef uint8_t SceUInt8;

typedef enum LIBRARY_ATTRIBUTES {
    SCE_LIBRARY_ATTR_NONE=0,
    SCE_LIBRARY_ATTR_AUTO_EXPORT=1,
    SCE_LIBRARY_ATTR_WEAK_EXPORT=2,
    SCE_LIBRARY_ATTR_PLUGIN_LINK_EXPORT=4,
    SCE_LIBRARY_ATTR_LOOSE_IMPORT=8,
    SCE_LIBRARY_ATTR_SYSCALL_EXPORT=16384, // Functions of this library are exported as syscall,
    SCE_LIBRARY_ATTR_MAIN_EXPORT=32768, // Module main export (NONAME library)
} LIBRARY_ATTRIBUTES;

struct SceLibStubTable_0x34 {
    SceUInt16 size; // Size of this structure
    SceUInt8 version[2]; // Library version
    enum LIBRARY_ATTRIBUTES attributes; // Library attributes
    SceUInt16 numFuncs; // Number of functions imported from this library
    SceUInt16 numVars; // Number of variables imported from this library
    SceUInt16 numTLSVars; // Number of TLS variables imported from this library
    SceUInt32 reserved0xC;
    SceUInt32 libraryNID; // Numeric ID of the library
    char * pLibName; // Pointer to library name
    SceUInt32 reserved0x18;
    SceUInt32 * pFuncNidTbl; // Pointer to functions NID table
    pointer32 * pFuncEntryTbl; // Pointer to functions entrypoints table
    SceUInt32 * pVarNidTbl; // Pointer to variables NID table
    pointer32 * pVarEntryTbl; // Pointer to variables entry table
    SceUInt32 * pTlsNidTbl; // Pointer to TLS variables NID table
    pointer32 * pTlsEntryTbl; // Pointer to TLS variables entry table
};

static void _apply_1080p(SceLibStubTable_0x34 *pInput) {
  pInput = (SceLibStubTable_0x34 *)0x8710;
  
  TAI_CONTINUE(int, gHookRef, pInput);
  return;
}

int module_start(SceSize argc, const void *args)
{
	int sRet;
	/*
	 * 0x4d37f036 : sceAVConfigHdmiSetResolution
	 * 0x79e0f03f : SceAVConfig
	*/
	gHook = taiHookFunctionExportForKernel (KERNEL_PID, &gHookRef, "SceAVConfig", 0x79e0f03f, 0x4d37f036, _apply_1080p);
	if (gHook < 0) {
		sRet = SCE_KERNEL_START_FAILED;
	} else {
		sRet = SCE_KERNEL_START_SUCCESS;
	}
	return sRet;
}

int module_stop(SceSize argc, const void *args)
{
	if (gHook >= 0) {
		taiHookReleaseForKernel(KERNEL_PID, gHookRef);
	}
	return SCE_KERNEL_STOP_SUCCESS;
}
