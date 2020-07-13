#pragma once
#include "shapefactory.h"
#include "MyLine.h"

class LineFactory :
	public ShapeFactory
{
public:
	~LineFactory(void);
	MyShape* createShape() { return new MyLine(); }
	static LineFactory* getInstance()
	{
		static LineFactory *instance = new LineFactory();
		return instance;
	}
private:
	LineFactory(void);
};

