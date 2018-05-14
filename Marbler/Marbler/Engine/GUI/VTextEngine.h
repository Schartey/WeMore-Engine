#pragma once

#include <iostream>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ft2build.h"
#include FT_FREETYPE_H

#include "../Core/VShader.h"

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

struct Text {
	std::string text;
	GLfloat posX;
	GLfloat posY;
	GLfloat scale;
	glm::vec3 color;

	Text() : text("Text"), scale(1.0f) {}
	Text(std::string text, GLfloat posX, GLfloat posY, GLfloat scale, glm::vec3 color) : text(text), posX(posX), posY(posY), scale(scale), color(color) {}
};

class VTextEngine
{
public:
	static VTextEngine* GetInstance() {
		if (Instance == nullptr)
			Instance = new VTextEngine();

		return Instance;
	}

	bool Setup(int Width, int Height);
	void DrawText(Text text);

	~VTextEngine();

private:
	VTextEngine();

	int Width;
	int Height;

	glm::mat4 projection;

	static VTextEngine* Instance;

	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;
	GLuint texture;
	static VShader* Shader;
};

