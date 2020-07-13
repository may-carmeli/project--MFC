
#include "stdafx.h"
#include "MyPen.h"


MyPen::MyPen()
{
	
}

MyPen::~MyPen()
{
}

void MyPen::draw(CDC * dc)
{
	CPen pen(PS_SOLID, 5, bgColor);
	CPen *oldPen = dc->SelectObject(&pen);
	innerDraw(dc);

}

