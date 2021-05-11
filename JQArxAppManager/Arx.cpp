#include "pch.h"

#ifndef _WIN64
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#else
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#endif

void InitApp()
{
	acedRegCmds->addCommand(L"JQArxAppManager", L"JQU", L"JQU", ACRX_CMD_MODAL, []()->void {
		//acrxDynamicLinker->unloadApp(LR"(D:\C\Desktop\Arx\x64\Release\HelloARX.arx)", true);
		acrxDynamicLinker->unloadApp(LR"(D:\C\Desktop\Arx\x64\Dev\HelloARX.arx)", true);
		//acrxDynamicLinker->unloadModule(LR"(D:\C\Desktop\Arx\x64\Release\HelloARX.arx)", true);
		acrxDynamicLinker->unloadModule(LR"(D:\C\Desktop\Arx\x64\Dev\HelloARX.arx)", true);
	});

	acedRegCmds->addCommand(L"JQArxAppManager", L"JQH", L"JQH", ACRX_CMD_MODAL, []()->void {
		MessageBoxA(0, "JQArxAppManager", "", 0);
	});

	acedRegCmds->addCommand(L"JQArxAppManager", L"JQL", L"JQL", ACRX_CMD_MODAL, []()->void {
		//acrxDynamicLinker->loadApp(LR"(D:\C\Desktop\Arx\x64\Release\HelloARX.arx)", AcadApp::kOnLoadRequest, true, true);
		acrxDynamicLinker->loadApp(LR"(D:\C\Desktop\Arx\x64\Dev\HelloARX.arx)", AcadApp::kOnLoadRequest, true, true);
		//acrxDynamicLinker->loadModule(LR"(D:\C\Desktop\Arx\x64\Release\HelloARX.arx)", AcadApp::kOnLoadRequest, true);
		acrxDynamicLinker->loadModule(LR"(D:\C\Desktop\Arx\x64\Dev\HelloARX.arx)", AcadApp::kOnLoadRequest, true);
	});
}

void UnloadApp()
{
	acedRegCmds->removeGroup(L"JQArxAppManagerx");
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