#include "VTextWidget.h"



VTextWidget::VTextWidget()
{
	TextElement = new VTextElement();
}

VTextElement* VTextWidget::GetTextElement()
{
	return TextElement;
}

void VTextWidget::RenderPass()
{
	if (!this->visibility) return;
	TextElement->RenderPass();
}

VTextWidget::~VTextWidget()
{
}
