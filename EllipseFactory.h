#pragma once
#include "shapefactory.h"
#include "MyEllipse.h"

class EllipseFactory :
	public ShapeFactory
{
public:
	~EllipseFactory(void);
	MyShape* createShape() { return new MyEllipse(); }
	static EllipseFactory* getInstance()
	{
		static EllipseFactory* instance = new EllipseFactory();
		return instance;
	}
private:
	EllipseFactory();
};

