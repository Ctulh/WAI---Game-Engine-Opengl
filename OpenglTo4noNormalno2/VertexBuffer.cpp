#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const GLfloat* data, unsigned int size)
	:m_Size(size)
{
	std::cout << std::endl << "VertexBuffer Created" ;
	glGenBuffers(1, &m_RendererID);
	std::cout << std::endl << "VertexBuffer take m_RendererID::" << m_RendererID ;
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	//delete[] data;
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
	std::cout << std::endl << "VertexBuffer destructor"<<std::endl;
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
unsigned int VertexBuffer::GetSize() const { return m_Size; }