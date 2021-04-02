#include "Texture.h"
#include <vector>
#include <string>
#include "Structures.h"

class TextureArray {
public:
	std::vector<TextureObj*> TextureArr;
	TextureArray();
	~TextureArray();
	int Add(const std::string& path);
	//void Delete(const int index);

};



