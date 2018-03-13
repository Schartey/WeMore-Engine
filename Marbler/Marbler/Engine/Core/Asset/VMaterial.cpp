#include "VMaterial.h"



VMaterial::VMaterial()
{
	Shader = new VShader("Engine/Shader/basic.vert", "Engine/Shader/basic.frag");
}

void VMaterial::Use()
{
	Shader->useShader();
}

void VMaterial::Release()
{

}

VMaterial::~VMaterial()
{
}
