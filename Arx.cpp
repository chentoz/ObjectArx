#include "pch.h"

#ifndef _WIN64
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#else
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#endif

void InitApp();
void UnloadApp();
void CmdHelloWorld();
void CmdChangeColor();
void CmdAddLine();

template <typename T>
struct Handle
{
public:
	Handle()
	{
		Init();
	}
	~Handle()
	{
		DecrementRef();

		if (*refCount == 0) {
			if (p)
			{
				p->close();
				p = nullptr;
				//delete p; // for we get pointer for Adobe systems
			}
			delete refCount;
		}
	}
	Handle(const Handle<T>& _src) :p(_src.p), refCount(_src.refCount)
	{
		AddRef();
	}

	T& operator*() {
		return *p;
	}

	T* & operator->() {
		return p;
	}

	T* & operator&() {
		return p;
	}
	VOID operator=(T *_p) {
		p = _p;
	}

	//T* & get() {
	//	return p;
	//}

private:
	void Init()
	{
		refCount = new std::size_t(1); // we have set ref as 0 
	}
	void AddRef()
	{
		if (!refCount) Init();
		++(*refCount);
	}
	void DecrementRef()
	{
		--(*refCount);
	}
private:
	T* p = nullptr;
	std::size_t *refCount = nullptr;
};

class CCreateEnt
{
public:
	static AcDbObjectId CreateLine(AcGePoint3d pStart, AcGePoint3d pEnd);
protected:
private:
};

class CModifyEnt
{
public:
	static Acad::ErrorStatus ChangeColor(AcDbObjectId entId, Adesk::UInt16 colorIndex);

	static Acad::ErrorStatus ChangeLayer(AcDbObjectId entId, std::wstring strLayerName);

	static Acad::ErrorStatus ChangeLineType(AcDbObjectId entId, std::wstring strLineType);

	static AcDbObjectId PostToModelSpace(AcDbEntity* pEnt);
};

//AcDbObjectId CreateLine();
//Acad::ErrorStatus ChangeColor(AcDbObjectId entId, Adesk::UInt16 colorIndex);

void InitApp()
{
	acedRegCmds->addCommand(L"HelloArx", L"Hello", L"Hello", ACRX_CMD_MODAL, CmdHelloWorld);
	acedRegCmds->addCommand(L"HelloArx", L"ChangeColor", L"ChangeColor", ACRX_CMD_MODAL, CmdChangeColor);
	acedRegCmds->addCommand(L"HelloArx", L"AddLine", L"AddLine", ACRX_CMD_MODAL, CmdAddLine);
}

void UnloadApp()
{
	acedRegCmds->removeGroup(L"HelloArx");
}

void CmdHelloWorld()
{
	acutPrintf(L"\nHello World!");
}

void CmdChangeColor()
{
	AcGePoint3d pStart(0, 0, 0);
	AcGePoint3d pEnd(100, 100, 0);
	AcDbObjectId lineId;
	lineId = CCreateEnt::CreateLine(pStart, pEnd);
	CModifyEnt::ChangeColor(lineId, 1);
}

void CmdAddLine()
{
	AcGePoint3d pStart(0, 0, 0);
	AcGePoint3d pEnd(100, 100, 0);
	AcDbObjectId lineId = CCreateEnt::CreateLine(pStart, pEnd);
	CModifyEnt::ChangeColor(lineId, 1);
	CModifyEnt::ChangeLayer(lineId, L"虚线");
	CModifyEnt::ChangeLineType(lineId, L"中心线");
}

AcDbObjectId CreateLine()
{
	AcGePoint3d pStart(0, 0, 0);
	AcGePoint3d pEnd(100, 100, 0);

	Handle<AcDbLine> hLine;
	hLine = new AcDbLine(pStart, pEnd);

	Handle<AcDbBlockTable> hBlockTable;

	acdbHostApplicationServices()->workingDatabase()
		->getBlockTable(&hBlockTable, AcDb::kForRead);

	Handle<AcDbBlockTableRecord> hBlockTableRecord;
	hBlockTable->getAt(ACDB_MODEL_SPACE, &hBlockTableRecord, AcDb::kForWrite);

	AcDbObjectId lineId;

	hBlockTableRecord->appendAcDbEntity(lineId, &hLine);
	hLine->setColorIndex(1);

	return lineId;
}

//Acad::ErrorStatus ChangeColor(AcDbObjectId entId, Adesk::UInt16 colorIndex)
//{
//	AcDbObjectId lineId;
//	lineId = CreateLine();
//
//	::ChangeColor(lineId, 1);
//}

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

AcDbObjectId CCreateEnt::CreateLine(AcGePoint3d pStart, AcGePoint3d pEnd)
{
	Handle<AcDbLine> hLine;
	hLine = new AcDbLine(pStart, pEnd);

	AcDbObjectId lineId;
	lineId = CModifyEnt::PostToModelSpace(&hLine);

	return lineId;
}

Acad::ErrorStatus CModifyEnt::ChangeColor(AcDbObjectId entId, Adesk::UInt16 colorIndex)
{
	Handle<AcDbEntity> hEntity;
	acdbOpenAcDbEntity(&hEntity, entId, AcDb::kForWrite);
	hEntity->setColorIndex(colorIndex);
	return Acad::eOk;
}

Acad::ErrorStatus CModifyEnt::ChangeLayer(AcDbObjectId entId, std::wstring strLayerName)
{
	Handle<AcDbEntity> hEntity;
	acdbOpenObject(&hEntity, entId, AcDb::kForWrite);
	hEntity->setLayer(strLayerName.c_str());
	return Acad::eOk;
}

Acad::ErrorStatus CModifyEnt::ChangeLineType(AcDbObjectId entId, std::wstring strLineType)
{
	Handle<AcDbEntity> hEntity;
	acdbOpenObject(&hEntity, entId, AcDb::kForWrite);
	hEntity->setLinetype(strLineType.c_str());
	return Acad::eOk;
}

AcDbObjectId CModifyEnt::PostToModelSpace(AcDbEntity *pEnt)
{
	Handle<AcDbBlockTable> hBlockTable;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(&hBlockTable, AcDb::kForRead);

	Handle<AcDbBlockTableRecord> hBlockTableRecord;
	hBlockTable->getAt(ACDB_MODEL_SPACE, &hBlockTableRecord, AcDb::kForWrite);

	AcDbObjectId entId;
	hBlockTableRecord->appendAcDbEntity(entId, pEnt);

	return entId;
}
