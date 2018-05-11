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
	TextElement->RenderPass();
}

VTextWidget::~VTextWidget()
{
}
