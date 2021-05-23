#include <GL/glew.h>
#pragma once


class VertexBuffer
{
private: 
	unsigned int m_Size;
	unsigned int m_RendererID;
public:
	VertexBuffer(const GLfloat* data,unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
	unsigned int GetSize() const;

};
