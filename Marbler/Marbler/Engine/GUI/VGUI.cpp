#include "VGUI.h"                                                                                

VGUI::VGUI()
{
}

void VGUI::AddWidget(VUserWidget* UserWidget)
{
	Widgets.push_back(UserWidget);
}

void VGUI::RenderPass()
{
	for (VUserWidget* UserWidget : Widgets)
	{
		UserWidget->RenderPass();
	}
}

VGUI::~VGUI()
{
}
