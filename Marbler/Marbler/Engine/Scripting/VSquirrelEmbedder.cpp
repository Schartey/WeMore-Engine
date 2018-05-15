#include "VSquirrelEmbedder.h"

#include "squirrel/squirrel.h"


VSquirrelEmbedder::VSquirrelEmbedder()
{
}

void VSquirrelEmbedder::Setup(VGame* Game)
{
	HSQUIRRELVM v;
	v = sq_open(1024); //creates a VM with initial stack size 1024

					   //do some stuff with squirrel here

	sq_close(v);
}

VSquirrelEmbedder::~VSquirrelEmbedder()
{
}
