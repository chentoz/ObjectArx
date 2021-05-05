#pragma once
#ifndef COMMANDS
#define COMMANDS
#include "pch.h"

#include "Helpers.h"
#include "Calculation.h"
#include "Entities.h"

BEGIN_DECLARE_CMDS

ADD_CMD("HelloWorld", []()->void
{
	acutPrintf(L"\nHello World!");
})

ADD_CMD("ChangeColor", []()->void
{
	AcGePoint3d pStart(0, 0, 0);
	AcGePoint3d pEnd(100, 100, 0);
	AcDbObjectId lineId;
	lineId = CCreateEnt::CreateLine(pStart, pEnd);
	CModifyEnt::ChangeColor(lineId, 1);
})

ADD_CMD("AddLine", []()->void
{
	AcGePoint3d pStart(0, 0, 0);
	AcGePoint3d pEnd(100, 100, 0);
	AcDbObjectId lineId = CCreateEnt::CreateLine(pStart, pEnd);
	CModifyEnt::ChangeColor(lineId, 1);
	CModifyEnt::ChangeLayer(lineId, L"虚线");
	CModifyEnt::ChangeLineType(lineId, L"中心线");
})

ADD_CMD("AddCircle", []()->void
{
	AcGePoint3d pCenter(100, 100, 0);
	CCreateEnt::CreateCircle(pCenter, 20);

	AcGePoint2d p1(70, 100);
	AcGePoint2d p2(130, 100);
	CCreateEnt::CreateCircle(p1, p2);
	p1.set(60, 100);
	p2.set(140, 100);
	AcGePoint2d p3(100, 60);
})

ADD_CMD("AddArc", []()->void
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
})

ADD_CMD("AddPolyline", []()->void
{
	AcGePoint2d pStart(0, 0);
	AcGePoint2d pEnd(100, 100);
	CCreateEnt::CreatePolyline(pStart, pEnd, 1);

	//AcGePoint3d p1(0, 0, 0),

	AcGePoint3d p1(0, 0, 0);
	AcGePoint3d p2(100, 0, 0);
	AcGePoint3d p3(100, 100, 0);

	AcGePoint3dArray points;
	points.append(p1);
	points.append(p2);
	points.append(p3);

	CCreateEnt::Create3DPolyline(points);

	CCreateEnt::CreatePolygon(AcGePoint2d::kOrigin, 6, 30, 0, 1);
	AcGePoint2d p(60, 70);
	CCreateEnt::CreateRectangle(p, pEnd, 1);
	p.set(50, 50);
	CCreateEnt::CreatePolyCircle(p, 30, 1);

	CCreateEnt::CreatePolyArc(p, 50, CCalculation::GtoR(45), CCalculation::GtoR(225), 1);
})

ADD_CMD("AddEllipse", []()->void
{
	AcGeVector3d vecNormal(0, 0, 1);
	AcGeVector3d majorAxis(40, 0, 0);
	AcDbObjectId entId;
	entId = CCreateEnt::CreateEllipse(AcGePoint3d::kOrigin, vecNormal, majorAxis, 0.5);

	AcGePoint2d p1(60, 80);
	AcGePoint2d p2(140, 120);
	CCreateEnt::CreateEllipse(p1, p2);
})

ADD_CMD("AddSpline", []()->void
{
	AcGePoint3d p1(0, 0, 0);
	AcGePoint3d p2(10, 30, 0);
	AcGePoint3d p3(60, 80, 0);
	AcGePoint3d p4(100, 100, 0);

	AcGePoint3dArray points;
	points.append(p1);
	points.append(p2);
	points.append(p3);
	points.append(p4);
	CCreateEnt::CreateSpline(points);

	p2.set(30, 10, 0);
	p3.set(80, 60, 0);

	points.removeSubArray(0, 3);
	points.append(p1);
	points.append(p2);
	points.append(p3);
	points.append(p4);

	AcGeVector3d startTangent(5, 1, 0);
	AcGeVector3d endTangent(5, 1, 0);
	CCreateEnt::CreateSpline(points, startTangent, endTangent);
})

ADD_CMD("AddRegion", []()->void
{
	ads_name ss;
	auto rt = acedSSGet(NULL, NULL, NULL, NULL, ss);
	AcDbObjectIdArray objectIds;

	if (rt == RTNORM)
	{
		int length;
		acedSSLength(ss, &length);
		for (auto i : whoshuu::range(0, length))
		{
			ads_name ent;
			acedSSName(ss, i, ent);
			AcDbObjectId objId;
			acdbGetObjectId(objId, ent);

			objectIds.append(objId);
		}
	}
	acedSSFree(ss);

	AcDbObjectIdArray regionsIds = CCreateEnt::CreateRegion(objectIds);
	if (regionsIds.length() > 0)
	{
		acutPrintf(L"\n已经创建%d个面域！", regionsIds.length());
	}
	else {
		acutPrintf(L"\n创建0个面域");
	}
})

ADD_CMD("AddText", []()->void {
	AcGePoint3d pInsert(0, 4, 0);
	CCreateEnt::CreateText(pInsert, L"CAD大观园");

	pInsert.set(0, 0, 0);
	CCreateEnt::CreateMultiLineText(pInsert, L"http://www.cadhelp.net");
})

END_DECLARE_CMDS

#endif