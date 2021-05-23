 #include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"


VertexArray::VertexArray(VertexBuffer vb,VertexBufferLayout la)
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	std::cout << "VertexArray created"<<std::endl;
	std::cout << "VertexArray take m_RendererID::"<<m_RendererID<<std::endl;
	Bind();
	AddBuffer(vb, la);
}


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	std::cout << std::endl << "VertexArray created";
	std::cout<<std::endl << "VertexArray take m_RendererID::" << m_RendererID;
}


VertexArray::~VertexArray()
{
	std::cout << std::endl << "VertexArray removed";
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	m_Size = vb.GetSize();
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	unsigned int stride;
	for (unsigned int i=0;i<elements.size();i++)
	{
		stride = layout.GetStride();
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),(const void*)offset));
		offset += element.count* VertexBufferElement::GetSizeOfType(element.type); 
	}
	//vb.UnBind();
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}

unsigned int VertexArray::GetSize() const { return m_Size; }