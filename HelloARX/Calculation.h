#pragma once
#include "pch.h"

//template <typename T>
#ifndef CALCULATION
#define CALCULATION

class CCalculation {
public:
	static AcGePoint2d MiddlePoint(AcGePoint2d p1, AcGePoint2d p2);
	static AcGePoint3d MiddlePoint(AcGePoint3d p1, AcGePoint3d p2);

	static AcGePoint3d Pt2dTo3d(AcGePoint2d pt);

	static double PI();

	template <typename T>
	static inline T Min(T a, T b);

	template <typename T>
	static inline T Max(T a, T b);

	template <typename T>
	static inline auto RtoG(T angle);

	template <typename T>
	static inline auto GtoR(T angle);
};

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

template <typename T>
T CCalculation::Min(T a, T b)
{
	return a < b ? a : b;
}

template <typename T>
T CCalculation::Max(T a, T b)
{
	return a > b ? a : b;
}

template <typename T>
auto CCalculation::RtoG(T angle)
{
	return angle * 180 / CCalculation::PI();
}

template <typename T>
auto CCalculation::GtoR(T angle)
{
	return angle * CCalculation::PI() / 180;
}

#endif
