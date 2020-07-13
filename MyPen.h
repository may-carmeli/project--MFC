#pragma once
#include "myline.h"


class MyPen : public MyLine
{
public:
	MyPen(void);
	virtual ~MyPen(void);
	void draw(CDC *dc);

		

	
};

