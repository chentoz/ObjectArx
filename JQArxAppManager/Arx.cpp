#include "pch.h"

#ifndef _WIN64
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#else
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#endif

void InitApp()
{
	acedRegCmds->addCommand(L"JQArxAppManager", L"JQU", L"JQU", ACRX_CMD_MODAL, []()->void {
		//acrxDynamicLinker->unloadApp(L"HelloARX.arx", true);
		acrxDynamicLinker->unloadModule(L"HelloARX.arx", true);
	});

	acedRegCmds->addCommand(L"JQArxAppManager", L"JQH", L"JQH", ACRX_CMD_MODAL, []()->void {
		MessageBoxA(0, "JQArxAppManager", "", 0);
	});

	acedRegCmds->addCommand(L"JQArxAppManager", L"JQL", L"JQL", ACRX_CMD_MODAL, []()->void {
		//acrxDynamicLinker->loadApp(L"HelloARX.arx", AcadApp::kOnLoadRequest, true, true);
		acrxDynamicLinker->loadModule(L"HelloARX.arx", true, true);
	});

	acedRegCmds->addCommand(L"JQArxAppManager", L"bb", L"bb", ACRX_CMD_MODAL, []()->void {
		//AcApDocManager::sendStringToExecute(AcApDocManager::activateDocument(), )
		//acrxDynamicLinker->unloadApp(L"JQArxAppManager", true);
		//acrxDynamicLinker->unloadModule(L"JQArxAppManager.arx", true);
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