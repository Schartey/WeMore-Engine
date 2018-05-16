#include "VSquirrelGame.h"



SQInteger func_createActor(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v); //number of arguments
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
	printf("Loaded actor");
	printf("\n");
	sq_pushinteger(v, nargs); //push the number of arguments as return value
	return 1; //1 because 1 value is returned
}

SQInteger register_global_func(HSQUIRRELVM v, SQFUNCTION f, const char *fname)
{
	sq_pushroottable(v);
	sq_pushstring(v, fname, -1);
	sq_newclosure(v, f, 0); //create a new function
	sq_newslot(v, -3, SQFalse);
	sq_pop(v, 1); //pops the root table

	return 1;
}

VSquirrelGame::VSquirrelGame(HSQUIRRELVM v, VGame* Game)
{
	this->v = v;
	this->Game = Game;

	register_global_func(this->v, func_createActor, "createActor");
}

void VSquirrelGame::OnInitialize()
{
	Game->OnInitialize();

	sq_pushroottable(v);
	sq_pushstring(v, "onInitialize", -1);
	sq_get(v, -2); //get the function from the root table
	sq_pushroottable(v); //'this' (function environment object)
	sq_call(v, 1, SQFalse,SQFalse);
	sq_pop(v, 2); //pops the roottable and the function
}

VSquirrelGame::~VSquirrelGame()
{
}
