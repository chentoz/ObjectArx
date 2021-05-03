#pragma once
#include "pch.h"
#include "Calculation.h"

#ifndef MODIFY_ENTITIY
#define MODIFY_ENTITIY
class CModifyEnt
{
public:
	static Acad::ErrorStatus ChangeColor(AcDbObjectId entId, Adesk::UInt16 colorIndex);

	static Acad::ErrorStatus ChangeLayer(AcDbObjectId entId, std::wstring strLayerName);

	static Acad::ErrorStatus ChangeLineType(AcDbObjectId entId, std::wstring strLineType);

	static AcDbObjectId PostToModelSpace(AcDbEntity* pEnt);
};

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
#endif

#ifndef CREATE_ENTITY
#define CREATE_ENTITY
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
#endif