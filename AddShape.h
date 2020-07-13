#pragma once
#include "command.h"
#include "MyShape.h"

class AddShape :
	public Command
{
public:
	AddShape(CTypedPtrArray<CObArray, MyShape*> &myShapes, MyShape *s);
	~AddShape();
	virtual void perform();
	virtual void rollback();
private:
	CTypedPtrArray<CObArray, MyShape*> &myShapes;
	MyShape *s;
};

