#pragma once
#include "shapefactory.h"
#include "MyRectangle.h"

class RectangleFactory :
	public ShapeFactory
{
public:
	~RectangleFactory(void);
	MyShape* createShape() { return new MyRectangle(); }
	static RectangleFactory* getInstance()
	{
		static RectangleFactory *instance = new RectangleFactory();
		return instance;
	}
private:
	RectangleFactory();
};


