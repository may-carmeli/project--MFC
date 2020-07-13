#pragma once
#include "shapefactory.h"
#include"MyPen.h"

class PenFactory :public ShapeFactory
{
public:
	~PenFactory(void);
	MyShape* createShape() { return new MyPen(); }
	static PenFactory* getInstance()
	{
		static PenFactory *instance = new PenFactory();
		return instance;
	}
private:
	PenFactory(void);
};


