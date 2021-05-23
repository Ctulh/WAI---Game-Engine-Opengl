#pragma once
#include "VertexBuffer.h"
//#include "VertexBufferLayout.h" 

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
	unsigned int m_Size;
public:
	VertexArray();
	VertexArray(VertexBuffer vb,VertexBufferLayout la);
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind()	const;
	void UnBind() const;
	unsigned int GetSize() const;
};