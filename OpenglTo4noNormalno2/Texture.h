#pragma once
#include <string>

class Texture
{
private:
	unsigned int m_RedererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width,m_Height, m_BPP;
public:
	Texture(std::string &path);
	~Texture();

	void Bind(unsigned int slot = 0 ) const;
	void UnBind() const;
	 
	inline int GetWIdth() const { return m_Width; }
	inline int GetHeight() const { return m_Height;  }

};