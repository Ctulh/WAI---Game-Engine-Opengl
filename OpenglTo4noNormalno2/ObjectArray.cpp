#include "ObjectArray.h"
#include "Object.h"


ObjectArray::ObjectArray() :size() {}

void ObjectArray::Add(Object* obj){
	size++;
	Array.push_back(obj);
}

void ObjectArray::Add(returned& RreturnedStruct, std::string& path){
	Array.push_back(new Object(RreturnedStruct, path));
	size++;
}

void ObjectArray::Draw(Renderer &renderer) {
	for (int i = 0; i < Array.size(); i++) {
		Array[i]->Draw(renderer,i);
	}
}