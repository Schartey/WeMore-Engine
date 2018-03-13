#pragma once

#include "../VShader.h"

class VMaterial
{
public:
	VMaterial();

	bool SetShader(VShader* Shader);

	void Use();
	void Release();

	~VMaterial();

private:
	VShader* Shader;
};

