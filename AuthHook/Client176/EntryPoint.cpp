//---------------------------------------------------------------------------------------------
// v176.1 Localhost Enabler - Rajan
//---------------------------------------------------------------------------------------------

#include "Global.h"

discord::Core* core{};

VOID WINAPI HeaderProc(DWORD dwPID)
{
	Log("------------------------------------------------");
	Log("[Rajan] [%s] [v%s] [PID: %d]", OPT_APPNAME, OPT_APPVERSION, dwPID);
	Log("[Rajan]       \\    /\\  ");
	Log("[Rajan]        )  ( ')   ");
	Log("[Rajan]       (  /  )    ");
	Log("[Rajan] cat    \\(__)|   ");
	Log("[Rajan] [Built: %s]", __TIMESTAMP__);
	Log("------------------------------------------------");
}

DWORD WINAPI MainProc(PVOID)
{
	DWORD dwCurProcId = GetCurrentProcessId();
	HeaderProc(dwCurProcId);

	if (!HookSockApi())
		Log("Failed Hooking SockApi");

	if (!HookWinApi())
		Log("Failed Hooking WinApi");

	if (!HookMapleApi())
		Log("Failed Hooking MapleApi");

	return 0;
}

void StartRPC() {
	auto result = discord::Core::Create(RPC_CLIENT_ID, DiscordCreateFlags_NoRequireDiscord, &core);
	discord::Activity activity{};
	activity.SetDetails("Currently Grinding SpiritMS");
	activity.SetState("Bera");
	// Refer to Discord Developer Portal on what your ImageKeys are
	activity.GetAssets().SetLargeImage("spiritlogo");
	activity.GetAssets().SetSmallImage("spiritbanner");
	activity.GetAssets().SetLargeText("Spirit");
	activity.GetAssets().SetSmallText("A calm day in Spirit.");
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
		// Do something with results here
		});
	while (true) {
		Sleep(3000); // Update every 3 second
		::core->RunCallbacks();
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&MainProc, NULL, NULL, NULL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&StartRPC, NULL, NULL, NULL);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		//
	}

	return TRUE;
}