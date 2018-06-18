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
	VSquirrelGame::Logger->Info("Squirrel", "Print: ");
	va_list arglist;
	va_start(arglist, s);
	scvprintf(s, arglist);
	va_end(arglist);
	VSquirrelGame::Logger->Info("", "");
}

SQInteger error_handler(HSQUIRRELVM v)
{
	printf("Error");
	SQInteger nargs = sq_gettop(v); //number of arguments

	if (sq_gettype(v, 2) == OT_STRING)
	{
		const SQChar* name = "";

		if (sq_getstring(v, 2, &name) == 0)
		{
			VSquirrelGame::Game->GetActiveScene()->CreateActor(std::string(name));
		}
	}

	for (SQInteger n = 1; n <= nargs; n++)
	{
		printf("arg %d is ", n);
		switch (sq_gettype(v, n))
		{
		case OT_NULL:
			printf("null");
			break;
		case OT_INTEGER:
			printf("integer");
			break;
		case OT_FLOAT:
			printf("float");
			break;
		case OT_STRING:
			printf("string");
			break;
		case OT_TABLE:
			printf("table");
			break;
		case OT_ARRAY:
			printf("array");
			break;
		case OT_USERDATA:
			printf("userdata");
			break;
		case OT_CLOSURE:
			printf("closure(function)");
			break;
		case OT_NATIVECLOSURE:
			printf("native closure(C function)");
			break;
		case OT_GENERATOR:
			printf("generator");
			break;
		case OT_USERPOINTER:
			printf("userpointer");
			break;
		case OT_CLASS:
			printf("class");
			break;
		case OT_INSTANCE:
			printf("instance");
			break;
		case OT_WEAKREF:
			printf("weak reference");
			break;
		default:
			return sq_throwerror(v, "invalid param"); //throws an exception
		}
	}
	printf("\n");
	sq_pushinteger(v, nargs); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

VSquirrelGame* VSquirrelEmbedder::Setup(VGame* Game)
{
	v = sq_open(1024); //creates a VM with initial stack size 1024

	sq_pushroottable(v);
	//sq_pushstring(v, "error_handler", -1);
	//sq_newclosure(v, error_handler, 0); //create a new function
	//sq_newslot(v, -3, SQFalse);
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
