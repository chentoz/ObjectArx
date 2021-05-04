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
	CModifyEnt::ChangeLayer(lineId, L"����");
	CModifyEnt::ChangeLineType(lineId, L"������");
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

	// ���㷨����Բ��
	AcGePoint2d pStart(100, 0);
	AcGePoint2d pOnArc(120, 50);
	AcGePoint2d pEnd(100, 100);
	CCreateEnt::CreateArc(pStart, pOnArc, pEnd);

	// ��㣬 Բ�㣬 �յ�
	pStart.set(100, 100);
	pCenter.set(50, 50);
	pEnd.set(0, 100);
	CCreateEnt::CreateArcSCE(pStart, pCenter, pEnd);

	// ��㣬Բ�ģ�Բ���Ƕ�
	pStart.set(0, 100);
	pCenter.set(50, 50);
	CCreateEnt::CreateArc(pStart, pCenter, CCalculation::PI() / 2);
})


END_DECLARE_CMDS

#endif