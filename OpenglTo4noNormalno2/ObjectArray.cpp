#include "ObjectArray.h"
#include "Object.h"


ObjectArray::ObjectArray() :size() {}

void ObjectArray::Add(Object* obj) {
	size++;
	Array.push_back(obj);
}


void ObjectArray::Add(returned& RreturnedStruct, std::string& path) {
	std::string tempStringName = "Object # " + std::to_string(Array.size());
	char* c = &tempStringName[0];
	Array.push_back(new Object(c, RreturnedStruct, path));
	size++;
}

void ObjectArray::Draw(Renderer& renderer) {
	for (int i = 0; i < Array.size(); i++) {
		if (Array[i]->propirties.Visible)
			Array[i]->Draw(renderer, i);
	}
}