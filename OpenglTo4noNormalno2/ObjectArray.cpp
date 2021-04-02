#include "ObjectArray.h"
#include "Object.h"



ObjectArray::ObjectArray() 
	:size(), 
	 shader("vertex.shader", "fragment.shader"),
	 textureArray()
{
 Camera =glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}




void ObjectArray::Add(returned& RreturnedStruct, std::string& path) {
	std::string tempStringName = "Object # " + std::to_string(Array.size());
	char* c = &tempStringName[0];
	Array.push_back(new Object(c, RreturnedStruct, textureArray.Add(path)));
	size++;
}

void ObjectArray::Draw(Renderer& renderer) {
	shader.Bind();
	for (int i = 0; i < Array.size(); i++) {
		if (Array[i]->properties.Visible)
			Array[i]->Draw(renderer, shader, i, Camera);
	}
}

void ObjectArray::SetView(const glm::mat4& view) {
	Camera = view;
}