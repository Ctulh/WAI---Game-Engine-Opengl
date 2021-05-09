
#include <vector>
//#include "TextureArray.h"
#include "Renderer.h"
#include "Structures.h"
#include "TextureArray.h"
#include <glm/glm.hpp>
#include "Shader.h"
#include "Shape.h"
#pragma once

class Object;

class ObjectArray
{
public:
	std::vector<Object*> Array;
	TextureArray textureArray;
	Shader shader;
	std::size_t size;
	glm::mat4 Camera;

	ObjectArray();
	//void Add(Object *obj);
	void Add(returned& RreturnedStruct, std::string& path);
	void Add(Shape *shapeStruct,std::string& path);
	void Add(types type,std::string& path);
	void Draw(Renderer& renderer);
	void SetView(const glm::mat4& view);
};