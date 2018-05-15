#pragma once

#include "../Engine/Core/VGame.h"

#include "../Engine/GUI/Widgets/VTextWidget.h"

class Marbler : public VGame
{
public:
	Marbler();

	virtual void OnInitialize() override;
	virtual void RenderPass(VShader* Shader, RenderPassBufferType Type) override;

	~Marbler();

private:
	VTextWidget* FPSWidget;
};

