#pragma once

class VUserWidget
{
public:
	VUserWidget();

	void SetVisibility(bool visibility);

	virtual void RenderPass();

	~VUserWidget();

protected:
	bool visibility;
};

