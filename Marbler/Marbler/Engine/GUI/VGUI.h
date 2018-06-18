#pragma once

#include <vector>

#include "VTextEngine.h"

#include "VUserWidget.h"

class VGUI
{
public:
	VGUI();

	//TODO: Make this callable like VUserWidget* CreateWidget<WidgetType : VUserWidget>()
	int AddWidget(VUserWidget* UserWidget);

	VUserWidget* GetWidgetById(int id);

	void RenderPass();

	~VGUI();

private:
	int WidgetCount = 0;
	std::map<int, VUserWidget*> Widgets;
};

