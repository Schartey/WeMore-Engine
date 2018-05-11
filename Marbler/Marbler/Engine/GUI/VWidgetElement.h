#pragma once

#include "GL/glew.h"

#include "../Core/VShader.h"

class VWidgetElement
{
public:
	VWidgetElement();

	virtual void RenderPass();
	virtual void SetVisibility(bool visibility);

	~VWidgetElement();

protected:
	bool visibility;
};

