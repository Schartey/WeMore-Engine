#include "VGUI.h"    

VGUI::VGUI()
{
}

int VGUI::AddWidget(VUserWidget* UserWidget)
{
	Widgets.insert(std::pair<int, VUserWidget*>(++WidgetCount, UserWidget));

	return WidgetCount;
}

VUserWidget* VGUI::GetWidgetById(int id)
{
	return Widgets.at(id);
}

void VGUI::RenderPass()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (std::map<int, VUserWidget*>::iterator it = Widgets.begin(); it != Widgets.end(); ++it)
	{
		it->second->RenderPass();
	}
}

VGUI::~VGUI()
{
}
