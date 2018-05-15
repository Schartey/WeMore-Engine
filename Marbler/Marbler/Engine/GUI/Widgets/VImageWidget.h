#pragma once

#include "../VUserWidget.h"
#include "../WidgetElements/VImageElement.h"

class VImageWidget : public VUserWidget
{
public:
	VImageWidget();

	VImageElement* GetImageElement();
	void RenderPass() override;

	~VImageWidget();

private:
	VImageElement * ImageElement;
};

