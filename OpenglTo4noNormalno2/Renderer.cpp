#include "Renderer.h"
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__, __LINE__))

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[Opengl Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	shader.Bind();
	ib.Bind();
	va.Bind();
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}
void Renderer::DrawVB(const VertexArray& va, const Shader& shader,const int color) const
{
	shader.Bind();
	va.Bind();
	//std::cout << "Renderer set " << color + 1 << std::endl;
	glStencilFunc(GL_ALWAYS, color + 1, 0);
	GLCall(glDrawArrays(GL_TRIANGLES, 0, va.GetSize()/sizeof(GLfloat)));
}

// void Renderer::DrawObjectArray(const ObjectArray& obj) const {
// 	for (int i = 0; i < obj.size; i++){
// 		obj.Array[i].Bind();
// 		glStencilFunc(GL_ALWAYS, i + 1, -1);
// 		GLCall(glDrawArrays(GL_TRIANGLES, 0, obj.Array[i].VA.GetSize() / sizeof(GLfloat)));
// 	}
// }
