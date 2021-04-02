#include "Structures.h"
#include "TextureArray.h"

TextureArray::TextureArray()
{
	TextureArr.push_back(new TextureObj(0,"res/clear.png"));
}

TextureArray::~TextureArray() {
	TextureArr.~vector<TextureObj*>();
}

int SearchPath(const std::string& path, std::vector<TextureObj*>& Array) {
	for (int i = 0; i < Array.size(); i++) {
		if (Array[i]->texture_Path == path)
			return i;
	}
	return -1;
}

int TextureArray::Add(const std::string& _path) {
	if (SearchPath(_path, TextureArr) == -1) {
		TextureArr.push_back(new TextureObj(TextureArr.size(), _path));
		for (int i = 0; i < TextureArr.size(); i++)
			TextureArr[i]->texture.Bind(TextureArr[i]->texture_ID);
		return TextureArr.size() - 1;
	}
	else
		return SearchPath(_path, TextureArr);
}
