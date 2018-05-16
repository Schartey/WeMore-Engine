#pragma once

#include "squirrel/squirrel.h"

class VSquirrelCompiler
{
public:
	VSquirrelCompiler();

	static int CompileFile(HSQUIRRELVM v, const char *filename);

	~VSquirrelCompiler();

private:
};

