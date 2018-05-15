#pragma once

#include "../VTextEngine.h"
#include "../VWidgetElement.h"

class VTextElement : public VWidgetElement
{
public:
	VTextElement();

	Text* GetText();
	void SetText(Text text);
	void RenderPass() override;

	~VTextElement();

private:
	Text text;
};

