#include "Global.h"
#include <intrin.h>

void FuckMaple()
{
	Log(__FUNCTION__);

	{	//NGS Removal
		PatchRetZero(0x01960B00);
	}

	{	//MSCRC Bypass
		PatchJmp(0x019DD7AD, 0x019DD844);
	}

	{	//Logo Skipper
		//PatchNop(0x00B31AE6, 2);
		//PatchNop(0x00B31AEA, 2);
		//PatchNop(0x00B31AF7, 2);
	}
}

bool Hook_WriteStageLogA(bool bEnable)
{
	typedef int(__cdecl* pWriteStageLogA)(int nIdx, ZXString szMessage);
	static auto _WriteStageLogA = (pWriteStageLogA)(GetFuncAddress("nxgsm", "WriteStageLogA"));

	pWriteStageLogA Hook = [](int nIdx, ZXString szMessage) -> int
	{
		Log("WriteStageLogA: %s", szMessage);
		return 0;
	};

	return SetHook(bEnable, reinterpret_cast<void**>(&_WriteStageLogA), Hook);
}

bool Hook_WriteErrorLogA(bool bEnable)
{
	typedef int(__cdecl* pWriteErrorLogA)(int nIdx, ZXString szMessage);
	static auto _WriteErrorLogA = (pWriteErrorLogA)(GetFuncAddress("nxgsm", "WriteErrorLogA"));

	pWriteErrorLogA Hook = [](int nIdx, ZXString szMessage) -> int
	{
		Log("WriteErrorLogA: %s", szMessage);
		return 0;
	};

	return SetHook(bEnable, reinterpret_cast<void**>(&_WriteErrorLogA), Hook);
}

bool Hook_SetProgramState(bool bEnable)
{
	typedef int(__cdecl* SetProgramState_t)(int nState);
	static auto _SetProgramState = reinterpret_cast<SetProgramState_t>(0x0195F250);

	SetProgramState_t Hook = [](int nState) -> int
	{
		auto ret = _ReturnAddress();
		Log("SetProgramState %d [%#08x]", nState, ret);
		return _SetProgramState(nState);
	};

	return SetHook(bEnable, reinterpret_cast<void**>(&_SetProgramState), Hook);
}

bool Hook_StringPool__GetString(bool enable)
{
	typedef ZXString*(__fastcall* StringPool__GetString_t)(void* ecx, void* edx, ZXString* result, unsigned int nIdx, char formal);
	static auto StringPool__GetString = reinterpret_cast<StringPool__GetString_t>(0x00EC3BF0);

	StringPool__GetString_t Hook = [](void* ecx, void* edx, ZXString* result, unsigned int nIdx, char formal) -> ZXString*
	{
		auto ret = StringPool__GetString(ecx, edx, result, nIdx, formal);

		Log("StringPool__GetString: %s", *result);

		return ret;
	};

	return SetHook(enable, reinterpret_cast<void**>(&StringPool__GetString), Hook);
}

bool HookMapleApi()
{
	bool bResult = true;

	bResult &= Hook_WriteStageLogA(true);
	bResult &= Hook_WriteErrorLogA(true);
	//bResult &= Hook_SetProgramState(true);
	//bResult &= Hook_StringPool__GetString(true);

	return bResult;
}