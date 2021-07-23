#include "pch.h"
#include "Commands.h"

//#ifndef _WIN64
//#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
//#else
//#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
//#endif

void InitApp()
{
	REGISTER_CMDS([](const CMD& cmd_func)->void {
		//auto [name, func] = cmd_func;
		auto name = std::get<0>(cmd_func);
		auto func = std::get<1>(cmd_func);

		acedRegCmds->addCommand(L"HelloArx", name, name, ACRX_CMD_MODAL, func);
	});
}

void UnloadApp()
{
	acedRegCmds->removeGroup(L"HelloArx");
}

extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) {
	switch (msg)
	{
	case AcRx::kNullMsg:
		break;
	case AcRx::kInitAppMsg:
		acrxDynamicLinker->unlockApplication(pkt);
		acrxRegisterAppMDIAware(pkt);
		InitApp();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApp();
		break;
	case AcRx::kLoadDwgMsg:
		break;
	case AcRx::kUnloadDwgMsg:
		break;
	case AcRx::kInvkSubrMsg:
		break;
	case AcRx::kCfgMsg:
		break;
	case AcRx::kEndMsg:
		break;
	case AcRx::kQuitMsg:
		break;
	case AcRx::kSaveMsg:
		break;
	case AcRx::kDependencyMsg:
		break;
	case AcRx::kNoDependencyMsg:
		break;
	case AcRx::kOleUnloadAppMsg:
		break;
	case AcRx::kPreQuitMsg:
		break;
	case AcRx::kInitDialogMsg:
		break;
	case AcRx::kEndDialogMsg:
		break;
	case AcRx::kSuspendMsg:
		break;
	case AcRx::kInitTabGroupMsg:
		break;
	case AcRx::kEndTabGroupMsg:
		break;
	default:
		break;
	}
	return AcRx::kRetOK;

}