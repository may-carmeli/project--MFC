#include "StdAfx.h"
#include "MyShape.h"

IMPLEMENT_SERIAL(MyShape, CObject, 1)

MyShape::MyShape(void)
{
}

MyShape::~MyShape(void)
{
}

void MyShape::Serialize(CArchive& archive)
{
	// call base class function first
	// base class is CObject in this case
	CObject::Serialize(archive);

	// now do the stuff for our specific class
	if (archive.IsStoring())//Determines whether the archive is storing.
		archive << start.x << start.y << end.x << end.y << bgColor;//save
	else
		archive >> start.x >> start.y >> end.x >> end.y >> bgColor;//load
}

void MyShape::draw(CDC *dc)
{
	CPen pen(PS_SOLID, 2, bgColor);
	CBrush brush(bgColor);
	CBrush *old = dc->SelectObject(&brush);
	CPen *oldPen = dc->SelectObject(&pen);
	innerDraw(dc);

}

bool MyShape::IsContained(CPoint p)
{
	if (start.x < end.x)
	{
		if (start.y < end.y)
		{
			if ((p.x >= start.x && p.x <= end.x) && (p.y >= start.y && p.y <= end.y))
				return true;
		}
		else
		{
			if ((p.x >= start.x && p.x <= end.x) && (p.y <= start.y && p.y >= end.y))
				return true;
		}
	}
	else
	{
		if (start.y < end.y)
		{
			if ((p.x <= start.x && p.x >= end.x) && (p.y >= start.y && p.y <= end.y))
				return true;
		}
		else
		{
			if ((p.x <= start.y && p.x >= end.y) && (p.y <= start.y && p.y >= end.y))
				return true;
		}
	}
	return false;
}
