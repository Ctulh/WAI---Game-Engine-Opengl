#pragma once
#include <vector>
#include "Renderer.h"
//#include "GL/glew.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:return 4;
		case GL_UNSIGNED_INT:return 4;
		case GL_UNSIGNED_BYTE:return 1;
		}
		//ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:

	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		:m_Stride(0) {
		std::cout << std::endl << "Creating VertexBufferLayout";}
	
	VertexBufferLayout(unsigned int stride):m_Stride(stride){}

	int size() {
		return m_Elements.size();
	}

	template<typename T>
	void Pop()
	{
		static_assert(false);
	}
	template<>
	void Pop<float>()
	{
		m_Stride -= VertexBufferElement::GetSizeOfType(GL_FLOAT) * m_Elements[m_Elements.size()-1].count;
		m_Elements.pop_back();
	}

	template<>
	void Pop<unsigned int>()
	{
		m_Stride -= VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * m_Elements[m_Elements.size() - 1].count;
		m_Elements.pop_back();
	}

	template<>
	void Pop<unsigned char>()
	{
		m_Stride -= VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * m_Elements[m_Elements.size() - 1].count;
		m_Elements.pop_back();
	}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({GL_FLOAT,count,GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT)*count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}


	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};