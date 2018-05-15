#include "VImageElement.h"

#include "../../Core/VGameStatics.h"
#include "../../Core/VGame.h"

VImageElement::VImageElement()
{
	projection = glm::ortho(0.0f, (float)VGameStatics::GetGame()->GetWindow()->GetWidth(), 0.0f, (float)VGameStatics::GetGame()->GetWindow()->GetHeight());
	Shader = new VShader("Engine/Shader/gui/image_element.vert", "Engine/Shader/gui/image_element.frag");
	//set up FreeType
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VImageElement::SetImage(VTexture* Texture)
{
	this->Texture = Texture;
}

void VImageElement::SetColor(glm::vec4 Color)
{
	this->Color = Color;
}

void VImageElement::SetPosition(glm::vec2 Position)
{
	this->Position = Position;
}

void VImageElement::SetSize(glm::vec2 Size)
{
	this->Size = Size;
}

void VImageElement::RenderPass()
{
	Shader->useShader();

	glBindVertexArray(VAO);

	Texture->Bind(GL_TEXTURE0);

	glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1i(glGetUniformLocation(Shader->programHandle, "textureSet"), this->Texture != nullptr);
	glUniform4f(glGetUniformLocation(Shader->programHandle, "diffuse"), this->Color.x, this->Color.y, this->Color.z, this->Color.w);
	glUniform1i(glGetUniformLocation(Shader->programHandle, "tex"), 0);

	GLfloat vertices[6][4] = {
		{ Position.x, Position.y + Size.y, 0.0, 0.0 },
		{ Position.x, Position.y, 0.0, 1.0 },
		{ Position.x + Size.x, Position.y, 1.0, 1.0 },

		{ Position.x, Position.y + Size.y, 0.0, 0.0 },
		{ Position.x + Size.x, Position.y, 1.0, 1.0 },
		{ Position.x + Size.x, Position.y + Size.y, 1.0, 0.0 }
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Render quad
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

VImageElement::~VImageElement()
{
}
