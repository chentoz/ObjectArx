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
void CmdAddCircle();
void CmdAddArc();

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

	T*& operator->() {
		return p;
	}

	T*& operator&() {
		return p;
	}
	VOID operator=(T* _p) {
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
	std::size_t* refCount = nullptr;
};

class CCalculation {
public:
	static AcGePoint2d MiddlePoint(AcGePoint2d p1, AcGePoint2d p2);
	static AcGePoint3d MiddlePoint(AcGePoint3d p1, AcGePoint3d p2);

	static AcGePoint3d Pt2dTo3d(AcGePoint2d pt);

	static double PI();
};

class CCreateEnt
{
public:
	static AcDbObjectId CreateLine(AcGePoint3d pStart, AcGePoint3d pEnd);
	static AcDbObjectId CreateCircle(AcGePoint3d pCenter, AcGeVector3d vec, double radius);
	static AcDbObjectId CreateCircle(AcGePoint3d pCenter, double radius);
	static AcDbObjectId CreateCircle(AcGePoint2d p1, AcGePoint2d p2);
	static AcDbObjectId CreateCircle(AcGePoint2d p1, AcGePoint2d p2, AcGePoint2d p3);
	static AcDbObjectId CreateCircle_API(AcGePoint2d p1, AcGePoint2d p2, AcGePoint2d p3);
	static AcDbObjectId CreateArc(AcGePoint3d pCenter, AcGeVector3d vec, double radius, double startAngle, double endAngle);
	static AcDbObjectId CreateArc(AcGePoint2d pCenter, double radius, double startAngle, double endAngle);
	static AcDbObjectId CreateArc(AcGePoint2d pStart, AcGePoint2d pOnArc, AcGePoint2d pEnd);
	static AcDbObjectId CreateArcSCE(AcGePoint2d pStart, AcGePoint2d pCenter, AcGePoint2d pEnd);
	static AcDbObjectId CreateArc(AcGePoint2d pStart, AcGePoint2d pCenter, double angle);
	static void test(void);

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
	acedRegCmds->addCommand(L"HelloArx", L"AddCircle", L"AddCircle", ACRX_CMD_MODAL, CmdAddCircle);
	acedRegCmds->addCommand(L"HelloArx", L"AddArc", L"AddArc", ACRX_CMD_MODAL, CmdAddArc);
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

void CmdAddCircle()
{
	AcGePoint3d pCenter(100, 100, 0);
	CCreateEnt::CreateCircle(pCenter, 20);

	AcGePoint2d p1(70, 100);
	AcGePoint2d p2(130, 100);
	CCreateEnt::CreateCircle(p1, p2);

	p1.set(60, 100);
	p2.set(140, 100);
	AcGePoint2d p3(100, 60);

	CCreateEnt::CreateCircle(p1, p2, p3);
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

AcDbObjectId CCreateEnt::CreateCircle(AcGePoint3d pCenter, AcGeVector3d vec, double radius)
{
	Handle<AcDbCircle> hCircle;
	&hCircle = new AcDbCircle(pCenter, vec, radius);
	AcDbObjectId circleId;
	circleId = CModifyEnt::PostToModelSpace(&hCircle);

	return circleId;
}

AcDbObjectId CCreateEnt::CreateCircle(AcGePoint3d pCenter, double radius)
{
	AcGeVector3d vec(0, 0, 1);
	return CCreateEnt::CreateCircle(pCenter, vec, radius);
}

AcDbObjectId CCreateEnt::CreateCircle(AcGePoint2d p1, AcGePoint2d p2)
{
	AcGePoint2d p = CCalculation::MiddlePoint(p1, p2);
	AcGePoint3d pCenter(p[X], p[Y], 0);

	double radius = p1.distanceTo(p2) / 2;

	return CCreateEnt::CreateCircle(pCenter, radius);
}

AcDbObjectId CCreateEnt::CreateCircle(AcGePoint2d p1, AcGePoint2d p2, AcGePoint2d p3)
{
	double xysm, xyse, xy;
	AcGePoint3d pCenter;
	double radius;

	xy = pow(p1[X], 2) + pow(p1[Y], 2);
	xyse = xy - (pow(p3[X], 2) + pow(p3[Y], 2));
	xysm = xy - (pow(p2[X], 2) + pow(p2[Y], 2));
	xy = (p1[X] - p2[X]) * (p1.y - p3.y) - (p1.x - p3.x) * (p1.y - p2.y);
	if (fabs(xy) < 0.000001)
	{
		MessageBoxA(0, "参数无法创建圆！", "", 0);
	}
	pCenter.x = (xysm * (p1.y - p3.y) - xyse * (p1.y - p2.y)) / (2 * xy);
	pCenter.y = (xyse * (p1.x - p2.x) - xysm * (p1.x - p3.x)) / (2 * xy);
	pCenter.z = 0;

	radius = sqrt((p1.x - pCenter.x) * (p1.x - pCenter.x) + (p1.x - pCenter.y) * (p1.y - pCenter.y));
	if (radius < 0.000001)
	{
		MessageBoxA(0, "半径太小！", "", 0);
	}

	return CCreateEnt::CreateCircle(pCenter, radius);
}

AcDbObjectId CCreateEnt::CreateCircle_API(AcGePoint2d p1, AcGePoint2d p2, AcGePoint2d p3)
{
	AcGeCircArc2d geArc(p1, p2, p3);
	AcGePoint3d pCenter(geArc.center().x, geArc.center().y, 0);
	return CCreateEnt::CreateCircle(pCenter, geArc.radius());
}

AcDbObjectId CCreateEnt::CreateArc(AcGePoint3d pCenter, AcGeVector3d vec, double radius, double startAngle, double endAngle)
{
	Handle<AcDbArc> hArc;
	&hArc = new AcDbArc(pCenter, vec, radius, startAngle, endAngle);
	AcDbObjectId arcId;
	arcId = CModifyEnt::PostToModelSpace(&hArc);

	return arcId;
}

AcDbObjectId CCreateEnt::CreateArc(AcGePoint2d pCenter, double radius, double startAngle, double endAngle)
{
	AcGeVector3d vec(0, 0, 1);
	return CCreateEnt::CreateArc(CCalculation::Pt2dTo3d(pCenter), vec, radius, startAngle, endAngle);
}

AcDbObjectId CCreateEnt::CreateArc(AcGePoint2d pStart, AcGePoint2d pOnArc, AcGePoint2d pEnd)
{
	AcGeCircArc2d geArc(pStart, pOnArc, pEnd);
	AcGePoint2d pCenter = geArc.center();
	double radius = geArc.radius();

	AcGeVector2d vecStart(pStart.x - pCenter.x, pStart.y - pCenter.y);
	AcGeVector2d vecEnd(pEnd.x - pCenter.x, pEnd.y - pCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = vecEnd.angle();

	return CCreateEnt::CreateArc(pCenter, radius, startAngle, endAngle);
}

void CCreateEnt::test(void)
{

}

AcDbObjectId CCreateEnt::CreateArcSCE(AcGePoint2d pStart, AcGePoint2d pCenter, AcGePoint2d pEnd)
{
	double radius = pCenter.distanceTo(pStart);

	AcGeVector2d vecStart(pStart.x - pCenter.x, pStart.y - pCenter.y);
	AcGeVector2d vecEnd(pEnd.x - pCenter.x, pEnd.y - pCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = vecEnd.angle();
	return CCreateEnt::CreateArc(pCenter, radius, startAngle, endAngle);
}

AcDbObjectId CCreateEnt::CreateArc(AcGePoint2d pStart, AcGePoint2d pCenter, double angle)
{
	double radius = pCenter.distanceTo(pStart);

	AcGeVector2d vecStart(pStart.x - pCenter.x, pStart.y - pCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = startAngle + angle;
	return CCreateEnt::CreateArc(pCenter, radius, startAngle, endAngle);
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

AcDbObjectId CModifyEnt::PostToModelSpace(AcDbEntity* pEnt)
{
	Handle<AcDbBlockTable> hBlockTable;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(&hBlockTable, AcDb::kForRead);

	Handle<AcDbBlockTableRecord> hBlockTableRecord;
	hBlockTable->getAt(ACDB_MODEL_SPACE, &hBlockTableRecord, AcDb::kForWrite);

	AcDbObjectId entId;
	hBlockTableRecord->appendAcDbEntity(entId, pEnt);

	return entId;
}

AcGePoint2d CCalculation::MiddlePoint(AcGePoint2d p1, AcGePoint2d p2)
{
	AcGePoint2d p;
	p.x = (p1.x + p2.x) / 2;
	p.y = (p1.y + p2.y) / 2;

	return p;
}

AcGePoint3d CCalculation::MiddlePoint(AcGePoint3d p1, AcGePoint3d p2)
{
	AcGePoint3d p;
	p.x = (p1.x + p2.x) / 2;
	p.y = (p1.y + p2.y) / 2;
	p.z = (p1.z + p2.z) / 2;

	return p;
}

AcGePoint3d CCalculation::Pt2dTo3d(AcGePoint2d pt)
{
	AcGePoint3d pTemp(pt.x, pt.y, 0);
	return pTemp;
}

double CCalculation::PI()
{
	return 4 * atan(1.0);
}


void CmdAddArc()
{
	AcGePoint2d pCenter(50, 50);
	CCreateEnt::CreateArc(pCenter, 100 * sqrt(2) / 2, 5 * CCalculation::PI() / 4, 7 * CCalculation::PI() / 4);

	// 三点法创建圆弧
	AcGePoint2d pStart(100, 0);
	AcGePoint2d pOnArc(120, 50);
	AcGePoint2d pEnd(100, 100);
	CCreateEnt::CreateArc(pStart, pOnArc, pEnd);

	// 起点， 圆点， 终点
	pStart.set(100, 100);
	pCenter.set(50, 50);
	pEnd.set(0, 100);
	CCreateEnt::CreateArcSCE(pStart, pCenter, pEnd);

	// 起点，圆心，圆弧角度
	pStart.set(0, 100);
	pCenter.set(50, 50);
	CCreateEnt::CreateArc(pStart, pCenter, CCalculation::PI() / 2);
}