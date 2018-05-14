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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (VUserWidget* UserWidget : Widgets)
	{
		UserWidget->RenderPass();
	}
}

VGUI::~VGUI()
{
}
