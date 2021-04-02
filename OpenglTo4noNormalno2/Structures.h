#include <GL/glew.h>
#include "Texture.h"
#include <vector>
#include <string>
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