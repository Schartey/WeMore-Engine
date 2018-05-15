#include "VImageWidget.h"


VImageWidget::VImageWidget()
{
	ImageElement = new VImageElement();
}

VImageElement* VImageWidget::GetImageElement()
{
	return ImageElement;
}

void VImageWidget::RenderPass()
{
	ImageElement->RenderPass();
}
VImageWidget::~VImageWidget()
{
}
