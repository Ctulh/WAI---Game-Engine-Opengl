#include "Object.h"
#include <string>
#include "Structures.h"
#include "Renderer.h"

Object::Object(char* in_name, returned& ReturnedStruct, int _index)
	:VB(ReturnedStruct.data, ReturnedStruct.Lines* ReturnedStruct.Columns * sizeof(GLfloat)),
	TextureIndex(_index),
	MVP(glm::mat4(1.0f)),
	Color(glm::vec4(1.0f)),
	Changes(true)
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


Object::Object(char* in_name, GLfloat* data, int _index)
	:VB(data, 1152 * sizeof(GLfloat)),
	TextureIndex(_index),
	MVP(glm::mat4(1.0f)),
	Color(glm::vec4(1.0f)),
	Changes(true)
{
	strcpy_s(Name, in_name);
	properties.Visible = true;
	properties.Texture = true;

	Layout.Push<float>(3);
	VA.AddBuffer(VB, Layout);
	Matrix.Projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
}

void Object::Draw(Renderer& renderer, Shader& shader, const int color, const glm::mat4& View) {
	Bind(View, shader);
	renderer.DrawVB(VA, shader, color);
}


void Object::Translate(const glm::vec3& translation) {
	for (int i = 0; i < 3; i++)
	{
		Matrix.Model[3][i] = translation[i];
	}
	Changes = true;
}

void Object::Translate() {
	for (int i = 0; i < 3; i++)
	{
		Matrix.Model[3][i] = ModelComponents.Translation[i];
	}
	Changes = true;
}


void Object::Scale(glm::vec3& newvec) {
	Matrix.Model = glm::scale(Matrix.Model, newvec / ModelComponents.Scale);
	ModelComponents.Scale = newvec;
	Changes = true;

}

void Object::Rotate(glm::quat& quatX, glm::quat& quatY) {
	Matrix.Model = glm::toMat4(quatX * quatY) * Matrix.Model;
	Translate();
	Changes = true;
}

void Object::Bind(const glm::mat4& View, Shader& shader) {
	if (properties.Texture) {
		shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		shader.SetUniform1i("u_Texture", TextureIndex);
	}
	else {
		shader.SetUniform4f("u_Color", Color[0], Color[1], Color[2], Color[3]);
		shader.SetUniform1i("u_Texture", 0);
	}
	VA.Bind();
	if (Changes) {
		MVP = Matrix.Projection * View * Matrix.Model;
		Changes = false;
	}
	shader.SetUniformMatrix4fv("MVP", &MVP[0][0]);
}