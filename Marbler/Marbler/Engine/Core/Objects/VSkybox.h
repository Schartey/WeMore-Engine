#pragma once

#include "VSceneObject.h"

class VSkybox : public VSceneObject
{
public:
	VSkybox(VScene* Scene, std::string Name);

	~VSkybox();
};

