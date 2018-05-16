#include "VSquirrelEmbedder.h"

#include <stdarg.h> 
#include <string>
#include <iostream>
#include <filesystem>

#include "squirrel/squirrel.h"
#include <squirrel/sqstdio.h> 
#include <squirrel/sqstdaux.h> 

#include "VSquirrelCompiler.h"

#ifdef SQUNICODE 
#define scvprintf vwprintf 
#else 
#define scvprintf vprintf 
#endif 

VSquirrelEmbedder::VSquirrelEmbedder()
{
}

void call_scriptLoaded(HSQUIRRELVM v, const SQChar *s)
{
	int top = sq_gettop(v); //saves the stack size before the call
	sq_pushroottable(v); //pushes the global table
	sq_pushstring(v, _SC("scriptLoaded"), -1);
	if (SQ_SUCCEEDED(sq_get(v, -2))) { //gets the field 'foo' from the global table
		sq_pushroottable(v); //push the 'this' (in this case is the global table)
		sq_pushstring(v, s, -1);
		sq_call(v, 2, 0, 0); //calls the function 
	}
	sq_settop(v, top); //restores the original stack size
}

void printfunc(HSQUIRRELVM v, const SQChar *s, ...)
{
	va_list arglist;
	va_start(arglist, s);
	scvprintf(s, arglist);
	va_end(arglist);
}

VSquirrelGame* VSquirrelEmbedder::Setup(VGame* Game)
{
	v = sq_open(1024); //creates a VM with initial stack size 1024

	sqstd_seterrorhandlers(v);

	sq_setprintfunc(v, printfunc, NULL); //sets the print function

	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "Setting Up Squirrel";

	sq_pushroottable(v); //push the root table(were the globals of the script will be stored)

	VSquirrelGame * SquirrelGame = new VSquirrelGame(v, Game);

	std::string path = "Scripts";

	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "Loading Scripts:" << std::endl;
	
	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		std::string path_string = p.path().u8string();

		if (SQ_SUCCEEDED(sqstd_dofile(v, _SC(path_string.c_str()), 0, 1))) // also prints syntax errors if any 
		{
			call_scriptLoaded(v, _SC(path_string.c_str()));
			std::cout << "Loaded: " << path_string << std::endl;
		}
	}

	std::cout << "----------------------------------------------------" << std::endl;

	return SquirrelGame;
}

void VSquirrelEmbedder::Close()
{
	sq_pop(v, 1); //pops the root table
	sq_close(v);
}

VSquirrelEmbedder::~VSquirrelEmbedder()
{
}
