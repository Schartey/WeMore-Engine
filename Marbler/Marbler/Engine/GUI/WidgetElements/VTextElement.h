#pragma once

#include "../VTextEngine.h"
#include "../VWidgetElement.h"

class VTextElement : public VWidgetElement
{
public:
	VTextElement();

	void SetText(Text text);
	void RenderPass() override;

	~VTextElement();

private:
	Text text;
};

