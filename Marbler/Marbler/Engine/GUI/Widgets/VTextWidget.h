#pragma once

#include "../VUserWidget.h"
#include "../WidgetElements/VTextElement.h"

class VTextWidget : public VUserWidget
{
public:
	VTextWidget();

	VTextElement* GetTextElement();
	void RenderPass() override;

	~VTextWidget();

private:
	VTextElement * TextElement;
};

