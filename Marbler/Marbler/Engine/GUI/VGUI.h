#pragma once

#include <vector>

#include "VTextEngine.h"

#include "VUserWidget.h"

class VGUI
{
public:
	VGUI();

	//TODO: Make this callable like VUserWidget* CreateWidget<WidgetType : VUserWidget>()
	void AddWidget(VUserWidget* UserWidget);

	void RenderPass();

	~VGUI();

private:
	std::vector<VUserWidget*> Widgets;
};

