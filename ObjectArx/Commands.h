#pragma once
#ifndef COMMANDS
#define COMMANDS
#include "pch.h"

#include "Helpers.h"
#include "Calculation.h"
#include "Entities.h"

void change_color(void)
{
	AcGePoint3d pStart(0, 0, 0);
	AcGePoint3d pEnd(100, 100, 0);
	AcDbObjectId lineId;
	lineId = CCreateEnt::CreateLine(pStart, pEnd);
	CModifyEnt::ChangeColor(lineId, 1);
}

void add_block(void)
{
	H(AcDbBlockTable, pBlkTbl);
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);

	H(AcDbBlockTableRecord, pBlkTblRcd) = new AcDbBlockTableRecord();

	ACHAR blkName[40];

	if (acedGetString(Adesk::kFalse, L"\n输入图块的名称：", blkName) != RTNORM)
	{
		return;
	}
	pBlkTblRcd->setName(blkName);

	AcCmColor colors;

	AcDbObjectId blkDefId;
	pBlkTbl->add(blkDefId, pBlkTblRcd);

	auto es = colors.setColorMethod(AcCmEntityColor::kByBlock); // 块内跟随块（参照）

	AcGePoint3d pStart(-10, 0, 0);
	AcGePoint3d pEnd(10, 0, 0);
	H(AcDbLine, pLine1) = new AcDbLine(pStart, pEnd);
	pLine1->setColor(colors);

	pStart.set(0, -10, 0);
	pEnd.set(0, 10, 0);
	H(AcDbLine, pLine2) = new AcDbLine(pStart, pEnd);
	pLine2->setColor(colors);

	AcGeVector3d vecNormal(0, 0, 1);
	H(AcDbCircle, pCircle) = new AcDbCircle(AcGePoint3d::kOrigin, vecNormal, 6);
	pCircle->setColor(colors);

	AcDbObjectId entId;
	pBlkTblRcd->appendAcDbEntity(entId, pLine1);
	pBlkTblRcd->appendAcDbEntity(entId, pLine2);
	pBlkTblRcd->appendAcDbEntity(entId, pCircle);
}

void add_block_DianRong(void)
{
	H(AcDbBlockTable, pBlkTbl);
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);

	H(AcDbBlockTableRecord, pBlkTblRcd) = new AcDbBlockTableRecord();

	ACHAR blkName[40];

	if (acedGetString(Adesk::kFalse, L"\n输入图块的名称：", blkName) != RTNORM)
	{
		return;
	}
	pBlkTblRcd->setName(blkName);
	AcDbObjectId blkDefId;
	pBlkTbl->add(blkDefId, pBlkTblRcd);

	AcDbObjectId entId;

	{
		AcGePoint3d p1(5, 15, 0);
		AcGePoint3d p2(5, 10, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}

	{
		AcGePoint3d p1(0, 10, 0);
		AcGePoint3d p2(10, 10, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}

	{
		AcGePoint3d p1(5, -15, 0);
		AcGePoint3d p2(5, -10, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}

	{
		AcGePoint3d p1(0, -10, 0);
		AcGePoint3d p2(10, -10, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}
}

void add_block_GeliKaiGuan(void)
{
	H(AcDbBlockTable, pBlkTbl);
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);

	H(AcDbBlockTableRecord, pBlkTblRcd) = new AcDbBlockTableRecord();

	ACHAR blkName[40];

	if (acedGetString(Adesk::kFalse, L"\n输入图块的名称：", blkName) != RTNORM)
	{
		return;
	}
	pBlkTblRcd->setName(blkName);
	AcDbObjectId blkDefId;
	pBlkTbl->add(blkDefId, pBlkTblRcd);

	AcDbObjectId entId;

	{
		AcGePoint3d p1(5, 15, 0);
		AcGePoint3d p2(5, 10, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}

	// 斜面
	{
		AcGePoint3d p1(5, 10, 0);
		AcGePoint3d p2(0, -10, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}

	{
		AcGePoint3d p1(5, -15, 0);
		AcGePoint3d p2(5, -10, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}

	{
		AcGePoint3d p1(3, -10, 0);
		AcGePoint3d p2(7, -10, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}
}

void add_block_JieDiFuHao(void)
{
	H(AcDbBlockTable, pBlkTbl);
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);

	H(AcDbBlockTableRecord, pBlkTblRcd) = new AcDbBlockTableRecord();

	ACHAR blkName[40];

	if (acedGetString(Adesk::kFalse, L"\n输入图块的名称：", blkName) != RTNORM)
	{
		return;
	}
	pBlkTblRcd->setName(blkName);
	AcDbObjectId blkDefId;
	pBlkTbl->add(blkDefId, pBlkTblRcd);

	AcDbObjectId entId;
	{
		AcGePoint3d p1(5, 15, 0);
		AcGePoint3d p2(5, 5, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}

	{
		AcGePoint3d p1(0, 5, 0);
		AcGePoint3d p2(10, 5, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}

	{
		AcGePoint3d p1(2, -5, 0);
		AcGePoint3d p2(8, -5, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}

	{
		AcGePoint3d p1(4, -10, 0);
		AcGePoint3d p2(6, -10, 0);
		H(AcDbLine, pLine) = new AcDbLine(p1, p2);
		pBlkTblRcd->appendAcDbEntity(entId, pLine);
	}
}

#define ADD_2D_LINE(x_s, y_s, x_e, y_e) \
{\
	AcGePoint3d p1(x_s, y_s, 0);\
	AcGePoint3d p2(x_e, y_e, 0);  \
	H(AcDbLine, pLine) = new AcDbLine(p1, p2);\
	pBlkTblRcd->appendAcDbEntity(entId, pLine);\
}\

void add_block_JieDiKaiGuan(void)
{
	H(AcDbBlockTable, pBlkTbl);
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);

	H(AcDbBlockTableRecord, pBlkTblRcd) = new AcDbBlockTableRecord();

	ACHAR blkName[40];

	if (acedGetString(Adesk::kFalse, L"\n输入图块的名称：", blkName) != RTNORM)
	{
		return;
	}
	pBlkTblRcd->setName(blkName);
	AcDbObjectId blkDefId;
	pBlkTbl->add(blkDefId, pBlkTblRcd);

	AcDbObjectId entId;

	ADD_2D_LINE(4, 15, 6, 15);
	ADD_2D_LINE(3, 13, 7, 13);
	ADD_2D_LINE(2, 11, 8, 11);
	ADD_2D_LINE(5, 11, 5, 5);
	ADD_2D_LINE(5, 5, 8, -5);
	ADD_2D_LINE(4, -7, 6, -7);
	ADD_2D_LINE(5, -7, 5, -15);
}

void add_block_ref(void)
{
	ACHAR blkName[40];

	if (acedGetString(Adesk::kFalse, L"\n输入图块的名称：", blkName) != RTNORM)
	{
		return;
	}
	H(AcDbBlockTable, pBlkTbl);
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);
	std::wstring strBlkDef = blkName;
	if (!pBlkTbl->has(strBlkDef.c_str()))
	{
		acutPrintf(L"\n未找到块定义");
		return;
	}
	ads_point pt;
	if (acedGetPoint(NULL, L"\n输入块参照的插入点:", pt) != RTNORM)
	{
		return;
	}
	AcGePoint3d pInsert = asPnt3d(pt);

	H(AcDbBlockTableRecord, pBlkTblRcd);
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);

	AcDbObjectId blkDefId;
	pBlkTbl->getAt(strBlkDef.c_str(), blkDefId);

	H(AcDbBlockReference, pBlkRef) = new AcDbBlockReference(pInsert, blkDefId);

	AcCmColor colors; //设置块的颜色
	colors.setColorMethod(AcCmEntityColor::kByColor); //指定颜色
	//colors.setColorMethod(AcCmEntityColor::kByLayer); //指定颜色
	colors.setColorIndex(4); //设置块引用的颜色

	pBlkRef->setColor(colors);

	AcDbObjectId entId;
	pBlkTblRcd->appendAcDbEntity(entId, pBlkRef);
}

void add_block_with_properties(void)
{
	H(AcDbBlockTable, pBlkTbl);
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);

	H(AcDbBlockTableRecord, pBlkTblRcd) = new AcDbBlockTableRecord();
	ACHAR blkName[40];
	if (acedGetString(Adesk::kFalse, L"\n输入图块的名称: ", blkName) != RTNORM)
	{
		pBlkTblRcd.Delete();
		return;
	}
	pBlkTblRcd->setName(blkName);

	AcDbObjectId  blkDefId;
	pBlkTbl->add(blkDefId, pBlkTblRcd);
	AcGePoint3d pStart(-10, 0, 0);
	AcGePoint3d pEnd(10, 0, 0);
	H(AcDbLine, pLine1) = new AcDbLine(pStart, pEnd);

	pStart.set(0, -10, 0);
	pEnd.set(0, 10, 0);
	H(AcDbLine, pLine2) = new AcDbLine(pStart, pEnd);
	AcGeVector3d vecNormal(0, 0, 1);

	H(AcDbCircle, pCircle) = new AcDbCircle(AcGePoint3d::kOrigin, vecNormal, 6);
	H(AcDbAttributeDefinition, pAttDef) = new AcDbAttributeDefinition(pEnd, L"20", L"直径", L"输入直径");

	AcDbObjectId entId;
	pBlkTblRcd->appendAcDbEntity(entId, pLine1);
	pBlkTblRcd->appendAcDbEntity(entId, pLine2);
	pBlkTblRcd->appendAcDbEntity(entId, pCircle);
	pBlkTblRcd->appendAcDbEntity(entId, pAttDef);
}

void insert_block_with_properties(void)
{
	ACHAR blkName[40];
	if (acedGetString(Adesk::kFalse, L"\n输入图块的名称：", blkName) != RTNORM) {
		return;
	}
	H(AcDbBlockTable, pBlkTbl);
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);

	std::wstring strBlkDef = blkName;
	if(!pBlkTbl->has(strBlkDef.c_str()))
	{
		acutPrintf(L"\n当前图形中未包含指定名称的块定义");
		return;
	}

	ads_point pt;
	if (acedGetPoint(NULL, L"\n输入块参照的插入点: ", pt) != RTNORM)
	{
		return;
	}
	AcGePoint3d pInsert = asPnt3d(pt);
	AcDbObjectId blkDefId;
	pBlkTbl->getAt(strBlkDef.c_str(), blkDefId);

	H(AcDbBlockReference, pBlkRef) = new AcDbBlockReference(pInsert, blkDefId);

	H(AcDbBlockTableRecord, pBlkTblRcd);
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);

	AcDbObjectId entId;
	pBlkTblRcd->appendAcDbEntity(entId, pBlkRef);

	H(AcDbBlockTableRecord, pBlkDefRcd);
	acdbOpenObject(&pBlkDefRcd, blkDefId, AcDb::kForRead);

	if (pBlkDefRcd->hasAttributeDefinitions())
	{
		P(AcDbBlockTableRecordIterator, pltr);
		pBlkDefRcd->newIterator(pltr);
		H(AcDbEntity, pEnt);
		for (pltr->start(); !pltr->done(); pltr->step())
		{
			pltr->getEntity(pEnt, AcDb::kForRead);
			H(AcDbAttributeDefinition, pAttDef);
			pAttDef = AcDbAttributeDefinition::cast(pEnt);
			if (pAttDef)
			{
				H(AcDbAttribute, pAtt) = new AcDbAttribute();
				pAtt->setPropertiesFrom(pAttDef);
				pAtt->setInvisible(pAttDef->isInvisible());
				AcGePoint3d pBase = pAttDef->position();
				// set position
				pBase += pBlkRef->position().asVector();
				pAtt->setPosition(pBase);
				pAtt->setHeight(pAttDef->height());
				pAtt->setRotation(pAttDef->rotation());
				// set tag
				ACHAR* pStr;
				pStr = pAttDef->tag();
				pAtt->setTag(pStr);
				free(pStr);
				// prompt
				pStr = pAttDef->prompt();
				acutPrintf(L"%s%s", L"\n", pStr);
				free(pStr);
				pAtt->setFieldLength(30);
				pAtt->setTextString(L"40");
				pBlkRef->appendAttribute(pAtt);
			}
		}
		delete pltr;
	}
}

BEGIN_DECLARE_CMDS

ADD_CMD("Hi", []()->void
{
	acutPrintf(L"\nHello World!");
})

ADD_CMD("ChangeColor", []()->void
{
	change_color();
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

ADD_CMD("AddBlock", []()->void {
	add_block();
	//add_block_DianRong();
	//add_block_GeliKaiGuan();
	//add_block_JieDiFuHao();
	//add_block_JieDiKaiGuan();
})

ADD_CMD("InsertBlock", []()->void {
	add_block_ref();
})

ADD_CMD("AddBlockWithProperties", []()->void {
	add_block_with_properties();
})

ADD_CMD("InsertBlockWithProperties", []()->void {
	insert_block_with_properties();
})


END_DECLARE_CMDS

#endif