#include <Windows.h>
#include "discord-files/discord.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "detours.lib")

#define ZXString char*

//---------------------------------------------------------------------------------------------

#define OPT_APPNAME			"SpiritMS"
#define OPT_APPVERSION		"3.2"
#define OPT_ADDR_HOSTNAME	"127.0.0.1"

#define OPT_ADDR_SEARCH		"8.31.99."
#define OPT_ADDR_NEXON		"8.31.99.141"
#define OPT_PORT_LOW		8484
#define OPT_PORT_HIGH		8989
#define RPC_CLIENT_ID       722180567550132225

//---------------------------------------------------------------------------------------------

void FuckMaple();

bool HookWinApi();
bool HookSockApi();
bool HookMapleApi();

//---------------------------------------------------------------------------------------------

void Log(const char* format, ...);

void PatchJmp(DWORD dwAddress, DWORD dwDest);
void PatchRetZero(DWORD dwAddress);
void PatchNop(DWORD dwAddress, DWORD dwCount);

DWORD GetFuncAddress(LPCSTR lpModule, LPCSTR lpFunc);

BOOL SetHook(BOOL bInstall, PVOID* ppvTarget, PVOID pvDetour);
//---------------------------------------------------------------------------------------------