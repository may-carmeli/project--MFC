#pragma once
#include "StdAfx.h"
#include "Command.h" 

class Command
{
public:
	Command(void);
	~Command(void);
	virtual void perform() = 0;//redo
	virtual void rollback() = 0;//undo
};

