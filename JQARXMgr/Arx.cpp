#include "pch.h"

#ifndef _WIN64
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#else
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#endif

auto cleandrawings()
{
	ads_name ssname, fname;
	ads_name sset, ent1, ent4, lastent;

	acedSSGet(L"A", NULL, NULL, NULL, ssname); // select all objects

	try
	{
		//if (acdbEntNext(NULL, fname) != RTNORM) {
		//	acdbFail(L"No entities in drawing\n");
		//	return;
		//}

		{
			ads_name ent;
			AcDbObjectId id;
			Adesk::Int32 length;
			if (acedSSLength(ssname, &length) == RTNORM)
			{
				for (size_t i = 0; i < length; i++)
				{
					if (ads_ssname(ssname, i, ent) == RTNORM)
					{
						if (acdbGetObjectId(id, ent) == Acad::eOk)
						{
							H(AcDbEntity, pEnt);
							acdbOpenAcDbEntity(pEnt, id, AcDb::kForWrite);

							if (pEnt->isKindOf(AcDbPoint::desc())
								|| pEnt->isKindOf(AcDbCircle::desc())
								|| pEnt->isKindOf(AcDbLine::desc())
								|| pEnt->isKindOf(AcDbText::desc())
								|| pEnt->isKindOf(AcDbArc::desc())
								|| pEnt->isKindOf(AcDbPolyline::desc())
								|| pEnt->isKindOf(AcDbBlockReference::desc())
								|| pEnt->isKindOf(AcDbBlockTableRecord::desc())
								|| pEnt->isKindOf(AcDbLinetypeTableRecord::desc())
								//|| pEnt->isKindOf(AcDbLinetypeTable  ::desc())
								)
							{
								pEnt->erase();
							}
						}
						else {
							//MB("failed get object id", i);
						}
					}
					else {
						//MB("failed get entity id", i);
					}

				}

			}

		}
	}
	catch (...)
	{

	}

	acedSSFree(ssname); // Free selection
}

void InitApp()
{
	acedRegCmds->addCommand(L"JQArxAppManager", L"JU", L"JU", ACRX_CMD_MODAL, []()->void {
		acrxDynamicLinker->unloadModule(L"JQCAD_ORG.arx", true);
	});

	acedRegCmds->addCommand(L"JQArxAppManager", L"JH", L"JH", ACRX_CMD_MODAL, []()->void {
		MessageBoxA(0, "JQArxAppManager", "", 0);
	});

	acedRegCmds->addCommand(L"JQArxAppManager", L"JL", L"JL", ACRX_CMD_MODAL, []()->void {
		acrxDynamicLinker->loadModule(L"JQCAD_ORG.arx", true, true);
	});

	acedRegCmds->addCommand(L"JQArxAppManager", L"JC", L"JC", ACRX_CMD_MODAL, []()->void {
		cleandrawings();
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