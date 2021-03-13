#include "VertexBuffer.h"
#include "Renderer.h"


/*VertexBuffer::VertexBuffer(object &obj)
:m_Size(obj.count())
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, obj.count(), obj.vertexArray, GL_STATIC_DRAW);
}*/



VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	:m_Size(size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
}
unsigned int VertexBuffer::GetSize() const { std::cout << std::endl << "size - " << m_Size; return m_Size; }

