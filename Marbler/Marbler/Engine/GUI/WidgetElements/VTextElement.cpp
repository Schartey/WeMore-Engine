#include "VTextElement.h"



VTextElement::VTextElement()
{

}

void VTextElement::SetText(Text text)
{
	this->text = text;
}

void VTextElement::RenderPass()
{
	VTextEngine::GetInstance()->DrawText(this->text);
}

VTextElement::~VTextElement()
{
}
