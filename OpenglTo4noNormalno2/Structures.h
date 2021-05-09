#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Texture.h"
#include <vector>
#include <string>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#pragma once


struct TextureObj
{
	Texture texture;
	int texture_ID;
	std::string texture_Path;
	TextureObj(int _index, std::string _path)
		:texture(_path),
		texture_ID(_index),
		texture_Path(_path)
	{}
};

struct returned
{
	int Lines;
	int Columns;
	GLfloat* data;
};

enum types {
	SPHERE, CUBE
};

struct ModelConstituent
{
	glm::vec3 Translation;
	glm::vec3 Scale;
	ModelConstituent()
		:Translation(0.0f),
		 Scale(1.0f)
	{
	}
};

