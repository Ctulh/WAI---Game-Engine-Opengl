#include "Texture.h"
#include <vector>
#include <string>
#include "Structures.h"
#pragma once
class TextureArray {
public:
	std::vector<TextureObj*> TextureArr;
	TextureArray();
	~TextureArray();
	int Add(const std::string& path);
};



