#include "Object.h"
#include <string>
#include "Structures.h"
#include "Renderer.h"

Object::Object(char* in_name, returned& ReturnedStruct, int _index)
	:VB(ReturnedStruct.data, ReturnedStruct.Lines* ReturnedStruct.Columns * sizeof(GLfloat)),
	TextureIndex(_index),
	MVP(glm::mat4(1.0f))
{
	strcpy_s(Name, in_name);
	properties.Visible = true;
	properties.Texture = true;
	if (ReturnedStruct.Columns == 3)
	{
		Layout.Push<float>(3);
	}
	else if (ReturnedStruct.Columns == 5) {
		Layout.Push<float>(3);
		Layout.Push<float>(2);
	}
	VA.AddBuffer(VB, Layout);
	Matrix.Projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
}


void Object::Draw(Renderer& renderer, Shader &shader, const int color, const glm::mat4& View) {
	Bind(View,shader);
	renderer.DrawVB(VA, shader, color);
}


void Object::Translate(const glm::vec3& translation) {
	Matrix.Model = glm::translate(Matrix.Model, translation);
}

void Object::Rotate(glm::quat& quatX, glm::quat& quatY) {
	glm::vec4 temp;
	for (int i = 0; i < 4; i++) {
		temp[i] = Matrix.Model[3][i];
	}
	Matrix.Model = glm::toMat4(quatX * quatY) * Matrix.Model;
	for (int i = 0; i < 4; i++) {
		Matrix.Model[3][i] = temp[i];
	}
}

void Object::Bind(const glm::mat4& View, Shader &shader) {
	if (properties.Texture){
		shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f); 
		shader.SetUniform1i("u_Texture", TextureIndex);
	}
	else {
		shader.SetUniform4f("u_Color", 1.0f, 0.0f, 1.0f, 1.0f);
		shader.SetUniform1i("u_Texture", 0);
	}
	VA.Bind();
	MVP = Matrix.Projection * View * Matrix.Model;
	shader.SetUniformMatrix4fv("MVP", &MVP[0][0]);
}