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

	static Acad::ErrorStatus Rotate(AcDbObjectId entId, AcGePoint2d pBase, double rotation);

	static Acad::ErrorStatus Move(AcDbObjectId entId, AcGePoint3d pBase, AcGePoint3d pDest);

	static Acad::ErrorStatus Scale(AcDbObjectId entId, AcGePoint3d pBase, double scaleFactor);
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
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(hBlockTable, AcDb::kForRead);

	Handle<AcDbBlockTableRecord> hBlockTableRecord;
	hBlockTable->getAt(ACDB_MODEL_SPACE, &hBlockTableRecord, AcDb::kForWrite);

	AcDbObjectId entId;
	hBlockTableRecord->appendAcDbEntity(entId, pEnt);

	return entId;
}

Acad::ErrorStatus CModifyEnt::Rotate(AcDbObjectId entId, AcGePoint2d pBase, double rotation)
{
	AcGeMatrix3d xform;
	AcGeVector3d vec(0, 0, 1);
	xform.setToRotation(rotation, vec, CCalculation::Pt2dTo3d(pBase));

	Handle<AcDbEntity> pEnt;
	Acad::ErrorStatus es = acdbOpenObject(pEnt, entId, AcDb::kForWrite, false);

	pEnt->transformBy(xform);
	return es;
}

Acad::ErrorStatus CModifyEnt::Move(AcDbObjectId entId, AcGePoint3d pBase, AcGePoint3d pDest)
{
	AcGeMatrix3d xform;
	AcGeVector3d vec(pDest.x - pBase.x, pDest.y - pBase.y, pDest.z - pBase.z);
	xform.setToTranslation(vec);

	Handle<AcDbEntity> pEnt;
	auto es = acdbOpenObject(pEnt, entId, AcDb::kForWrite, false);
	pEnt->transformBy(xform);
	return es;
}

Acad::ErrorStatus CModifyEnt::Scale(AcDbObjectId entId, AcGePoint3d pBase, double scaleFactor)
{
	AcGeMatrix3d xform;
	xform.setToScaling(scaleFactor, pBase);

	Handle<AcDbEntity> pEnt;
	auto es = acdbOpenObject(pEnt, entId, AcDb::kForWrite, false);
	pEnt->transformBy(xform);

	return es;
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
	static AcDbObjectId CreatePolyline(AcGePoint2dArray points, double width = 0);
	static AcDbObjectId CreatePolyline(AcGePoint2d pStart, AcGePoint2d pEnd, double width = 0);
	static AcDbObjectId Create3DPolyline(AcGePoint3dArray points);
	static AcDbObjectId CreatePolygon(AcGePoint2d pCenter, int number, double radius, double rotation, double width);
	static AcDbObjectId CreateRectangle(AcGePoint2d p1, AcGePoint2d p2, double width);
	static AcDbObjectId CreatePolyCircle(AcGePoint2d pCenter, double radius, double width);
	static AcDbObjectId CreatePolyArc(AcGePoint2d pCenter, double radius, double angleStart, double angleEnd, double width);
	static auto CreateEllipse(AcGePoint3d pCenter, AcGeVector3d vecNormal, AcGeVector3d majorAxis, double ratio);
	static auto CreateEllipse(AcGePoint2d p1, AcGePoint2d p2);
	static auto CreateSpline(const AcGePoint3dArray& poinst, int order = 4, double fitTolerance = 0.0);
	static auto CreateSpline(const AcGePoint3dArray& poinst, const AcGeVector3d& startTangent, const AcGeVector3d& endTangent, int order = 4, double fitTolerance = 0.0);
	static auto CreateFromCurves(const AcDbVoidPtrArray& curveSegments, AcDbVoidPtrArray& regions);
	static auto CreateRegion(const AcDbObjectIdArray & curveIds);
	static auto CreateText(const AcGePoint3d& pInsert, const ACHAR* btext, AcDbObjectId style = AcDbObjectId::kNull, double height = 2.5, double rotation = 0);
	static auto CreateMultiLineText(const AcGePoint3d& pInsert, const ACHAR* text, AcDbObjectId style = AcDbObjectId::kNull, double height = 2.5, double width = 10);
	static void test(void);

protected:
private:
};

AcDbObjectId CCreateEnt::CreateLine(AcGePoint3d pStart, AcGePoint3d pEnd)
{
	H(AcDbLine,hLine) = new AcDbLine(pStart, pEnd);

	AcDbObjectId lineId;
	lineId = CModifyEnt::PostToModelSpace(&hLine);

	return lineId;
}

AcDbObjectId CCreateEnt::CreateCircle(AcGePoint3d pCenter, AcGeVector3d vec, double radius)
{
	H(AcDbCircle,hCircle) = new AcDbCircle(pCenter, vec, radius);

	AcDbObjectId circleId;
	circleId = CModifyEnt::PostToModelSpace(hCircle);

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

AcDbObjectId CCreateEnt::CreatePolyline(AcGePoint2dArray points, double width /*= 0*/)
{
	int numVertices = points.length();
	Handle<AcDbPolyline> hPoly;
	hPoly = new AcDbPolyline(numVertices);
	for (int i = 0; i < numVertices; i++) {
		hPoly->addVertexAt(i, points.at(i), 0, width, width);
	}
	AcDbObjectId polyId = CModifyEnt::PostToModelSpace(hPoly);
	return polyId;
}

AcDbObjectId CCreateEnt::CreatePolyline(AcGePoint2d pStart, AcGePoint2d pEnd, double width /*= 0*/)
{
	AcGePoint2dArray points;
	points.append(pStart);
	points.append(pEnd);

	return CCreateEnt::CreatePolyline(points, width);
}

AcDbObjectId CCreateEnt::Create3DPolyline(AcGePoint3dArray points)
{
	Handle<AcDb3dPolyline> hPoly3D = new AcDb3dPolyline(AcDb::k3dSimplePoly, points);
	return CModifyEnt::PostToModelSpace(hPoly3D);
}

AcDbObjectId CCreateEnt::CreatePolygon(AcGePoint2d pCenter, int number, double radius, double rotation, double width)
{
	AcGePoint2dArray points;
	auto angle = 2 * CCalculation::PI() / number;

	for (int i = 0; i <= number; i++)
	{
		AcGePoint2d p;
		p.x = pCenter.x + radius * cos(i * angle);
		p.y = pCenter.y + radius * sin(i * angle);

		points.append(p);
	}

	AcDbObjectId polyId = CCreateEnt::CreatePolyline(points, width);

	H(AcDbEntity, pEnt);
	acdbOpenAcDbEntity(pEnt, polyId, AcDb::kForWrite);

	if (pEnt->isKindOf(AcDbPolyline::desc()) == Adesk::kTrue) return polyId;

	H(AcDbPolyline, pPoly) = AcDbPolyline::cast(pEnt);

	if (pPoly) {
		pPoly->setClosed(Adesk::kTrue);
	}
	CModifyEnt::Rotate(polyId, pCenter, rotation);
	return polyId;
}

AcDbObjectId CCreateEnt::CreateRectangle(AcGePoint2d p1, AcGePoint2d p2, double width)
{
	auto x1 = p1.x, x2 = p2.x;
	auto y1 = p1.y, y2 = p2.y;

	AcGePoint2d pLeftBottom(CCalculation::Min(x1, x2), CCalculation::Min(y1, y2));
	AcGePoint2d pRightBottom(CCalculation::Max(x1, x2), CCalculation::Min(y1, y2));
	AcGePoint2d pRightTop(CCalculation::Max(x1, x2), CCalculation::Max(y1, y2));
	AcGePoint2d pLeftTop(CCalculation::Min(x1, x2), CCalculation::Max(y1, y2));

	H(AcDbPolyline, pPoly) = new AcDbPolyline(4);
	pPoly->addVertexAt(0, pLeftBottom, 0, width, width);
	pPoly->addVertexAt(1, pRightBottom, 0, width, width);
	pPoly->addVertexAt(2, pRightTop, 0, width, width);
	pPoly->addVertexAt(3, pLeftTop, 0, width, width);
	pPoly->setClosed(Adesk::kTrue);

	AcDbObjectId polyId;
	polyId = CModifyEnt::PostToModelSpace(pPoly);

	return polyId;
}

AcDbObjectId CCreateEnt::CreatePolyCircle(AcGePoint2d pCenter, double radius, double width)
{
	AcGePoint2d p1, p2, p3;
	p1.x = pCenter.x + radius;
	p1.y = pCenter.y;
	p2.x = pCenter.x - radius;
	p2.y = pCenter.y;
	p3.x = pCenter.x + radius;
	p3.y = pCenter.y;

	H(AcDbPolyline, pPoly) = new AcDbPolyline(3);
	pPoly->addVertexAt(0, p1, 1, width, width);
	pPoly->addVertexAt(1, p2, 1, width, width);
	pPoly->addVertexAt(2, p3, 1, width, width);
	pPoly->setClosed(Adesk::kTrue);

	AcDbObjectId polyId;
	polyId = CModifyEnt::PostToModelSpace(pPoly);

	return polyId;
}

AcDbObjectId CCreateEnt::CreatePolyArc(AcGePoint2d pCenter, double radius, double angleStart, double angleEnd, double width)
{
	AcGePoint2d p1, p2;
	p1.x = pCenter.x + radius * cos(angleStart);
	p1.y = pCenter.y + radius * sin(angleStart);

	p1.x = pCenter.x + radius * cos(angleStart);
	p1.y = pCenter.y + radius * sin(angleStart);

	H(AcDbPolyline, pPoly) = new AcDbPolyline(3);
	pPoly->addVertexAt(0, p1, tan((angleEnd - angleStart) / 4), width, width);
	pPoly->addVertexAt(1, p2, 0, width, width);

	AcDbObjectId polyId;
	polyId = CModifyEnt::PostToModelSpace(pPoly);

	return polyId;
}

auto CCreateEnt::CreateEllipse(AcGePoint3d pCenter, AcGeVector3d vecNormal, AcGeVector3d majorAxis, double ratio)
{
	H(AcDbEllipse, pEllipse) = new AcDbEllipse(pCenter, vecNormal, majorAxis, ratio);

	return CModifyEnt::PostToModelSpace(pEllipse);
}

auto CCreateEnt::CreateEllipse(AcGePoint2d p1, AcGePoint2d p2)
{
	AcGePoint3d pCenter;
	pCenter = CCalculation::MiddlePoint(CCalculation::Pt2dTo3d(p1), CCalculation::Pt2dTo3d(p2));

	AcGeVector3d vecNormal(0, 0, 1);
	AcGeVector3d majorAxis(fabs(p1.x - p2.x), 0, 0);
	auto ratio = fabs((p1.y - p2.y) / (p1.x - p2.x));

	return CCreateEnt::CreateEllipse(pCenter, vecNormal, majorAxis, ratio);
}

auto CCreateEnt::CreateSpline(const AcGePoint3dArray& poinst, int order, double fitTolerance)
{
	assert(order >= 2 && order <= 26);
	H(AcDbSpline, pSpline) = new AcDbSpline(poinst, order, fitTolerance);

	AcDbObjectId splineId;
	splineId = CModifyEnt::PostToModelSpace(pSpline);

	return splineId;
}

auto CCreateEnt::CreateSpline(const AcGePoint3dArray& poinst, const AcGeVector3d& startTangent, const AcGeVector3d& endTangent, int order /*= 4*/, double fitTolerance /*= 0.0*/)
{
	assert(order >= 2 && order <= 26);
	H(AcDbSpline, pSpline) = new AcDbSpline(poinst, startTangent, endTangent, order, fitTolerance);

	return CModifyEnt::PostToModelSpace(pSpline);
}

auto CCreateEnt::CreateFromCurves(const AcDbVoidPtrArray& curveSegments, AcDbVoidPtrArray& regions)
{

}

auto CCreateEnt::CreateRegion(const AcDbObjectIdArray& curveIds)
{
	AcDbObjectIdArray regionIds;
	AcDbVoidPtrArray curves;

	AcDbVoidPtrArray regions;
	H(AcDbEntity, pEnt);
	H(AcDbRegion, pRegion);

	for (int i = 0; i < curveIds.length(); i++)
	{
		acdbOpenAcDbEntity(pEnt, curveIds.at(i), AcDb::kForRead);
		if (pEnt->isKindOf(AcDbCurve::desc())) {
			curves.append(static_cast<void*>(pEnt));
		}
	}
	auto es = AcDbRegion::createFromCurves(curves, regions); // cad 2018 works, but failed on 2020
	if (es == Acad::eOk)
	{
		for (auto i : whoshuu::range(0, regions.length()))
		{
			pRegion = static_cast<AcDbRegion*>(regions[i]);
			pRegion->setDatabaseDefaults();
			AcDbObjectId regionId = CModifyEnt::PostToModelSpace(pRegion);
			regionIds.append(regionId);
		}
	}
	else {
		for (auto i : whoshuu::range(0, regions.length()))
		{
			delete (AcRxObject*)regions[i];
		}
	}
	for (auto i :  whoshuu::range(0, curves.length()))
	{
		//H(AcDbEntity, pEntTemp) = curves[i]->cast(pEnt);
		H(AcDbEntity, pEntTemp) = static_cast<AcDbEntity*>(curves[i]);
	}
	return regionIds;
}

auto CCreateEnt::CreateText(const AcGePoint3d& pInsert, const ACHAR* text, AcDbObjectId style /*= AcDbObjectId::kNull*/, double height /*= 2.5*/, double rotation)
{
	H(AcDbText, pText) = new AcDbText(pInsert, text, style, height, rotation);
	return CModifyEnt::PostToModelSpace(pText);
}

auto CCreateEnt::CreateMultiLineText(const AcGePoint3d& pInsert, const ACHAR* text, AcDbObjectId style /*= AcDbObjectId::kNull*/, double height /*= 2.5*/, double width /*= 10*/)
{
	H(AcDbMText, pMText) = new AcDbMText();
	pMText->setTextStyle(style);
	pMText->setContents(text);
	pMText->setLocation(pInsert);
	pMText->setTextHeight(height);
	pMText->setWidth(width);
	pMText->setAttachment(AcDbMText::kBottomLeft);

	return CModifyEnt::PostToModelSpace(pMText);
}

void CCreateEnt::test(void)
{
	for (const auto& i : whoshuu::range(10))
	{
	}
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