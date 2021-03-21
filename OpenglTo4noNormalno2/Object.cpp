#include "Object.h"
#include <string>
#include "returned.h"
#include "Renderer.h"

Object::Object(returned& ReturnedStruct, std::string& path)
	:VB(ReturnedStruct.data, ReturnedStruct.Lines* ReturnedStruct.Columns * sizeof(GLfloat)),
	shader("vertex.shader", "fragment.shader"),
	texture(path)
{
	//Name = name;
	if (ReturnedStruct.Columns == 3)
		Layout.Push<float>(3);
	else if (ReturnedStruct.Columns == 5) {
		Layout.Push<float>(3);
		Layout.Push<float>(2);
	}
	VA.AddBuffer(VB, Layout);

	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);

	Matrix.Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	Matrix.View = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	MVP = Matrix.Projection * Matrix.View * Matrix.Model;
	
}

void Object::Draw(Renderer &renderer,const int color) {
	//MVP = Matrix.Projection * Matrix.View * Matrix.Model;
	//shader.SetUniformMatrix4fv("MVP", &MVP[0][0]);
	Bind();
	renderer.DrawVB(VA, shader, color);
}


void Object::Translate(const glm::vec3& translation) {
	Matrix.Model = glm::translate(Matrix.Model, translation);
}

void Object::Rotate(glm::quat& quatX, glm::quat& quatY){
	glm::vec4 temp;
	for (int i = 0; i < 4; i++) {
		temp[i] = Matrix.Model[3][i];
	}
	Matrix.Model = glm::toMat4(quatX * quatY) * Matrix.Model;
	for (int i = 0; i < 4; i++) {
		Matrix.Model[3][i] = temp[i];
	}
}

void Object::Bind() {
	texture.Bind();
	VA.Bind();
	shader.Bind();
	MVP = Matrix.Projection * Matrix.View * Matrix.Model;
	shader.SetUniformMatrix4fv("MVP", &MVP[0][0]);
}