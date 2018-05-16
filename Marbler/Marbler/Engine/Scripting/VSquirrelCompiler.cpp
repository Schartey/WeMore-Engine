#include "VSquirrelCompiler.h"

#include <iostream>
#include <stdio.h>
#include <errno.h>


VSquirrelCompiler::VSquirrelCompiler()
{
}

SQInteger fileLexfeedASCII(SQUserPointer file)
{
	int ret;
	char c;
	if ((ret = fread(&c, sizeof(c), 1, (FILE *)file)>0))
		return c;
	return 0;
}

int VSquirrelCompiler::CompileFile(HSQUIRRELVM v, const char *filename)
{
	FILE *f;
	if (errno_t err = fopen_s(&f, filename, "r") == 0)
	{
		sq_compile(v, fileLexfeedASCII, f, filename, 1);
		fclose(f);
		return 1;
	}
	else {
		std::cout << err;
	}
	return 0;
}

VSquirrelCompiler::~VSquirrelCompiler()
{
}
