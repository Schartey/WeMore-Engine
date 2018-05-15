#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../VWidgetElement.h"
#include "../../Core/Asset/VTexture.h"

class VImageElement : public VWidgetElement
{
public:
	VImageElement();

	void SetImage(VTexture* Texture);
	void SetColor(glm::vec4 Color);
	void SetPosition(glm::vec2 Position);
	void SetSize(glm::vec2 Size);
	void RenderPass() override;

	~VImageElement();

private:
	VTexture* Texture;
	glm::vec4 Color = glm::vec4(1.0f);
	glm::vec2 Position = glm::vec2(0.0f);
	glm::vec2 Size = glm::vec2(20.0f);

	GLuint VAO;
	GLuint VBO;

	glm::mat4 projection;
	const VShader* Shader;
};

