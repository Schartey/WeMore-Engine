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
	if (!this->visibility) return;
	ImageElement->RenderPass();
}
VImageWidget::~VImageWidget()
{
}
