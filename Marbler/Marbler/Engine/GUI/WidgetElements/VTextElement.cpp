#include "VTextElement.h"



VTextElement::VTextElement()
{

}

Text* VTextElement::GetText()
{
	return &text;
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
