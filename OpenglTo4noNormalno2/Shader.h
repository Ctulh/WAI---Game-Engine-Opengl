#pragma once

#include <glm/glm.hpp>
#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

class Shader
{
private:
	std::string Vertex_FilePath;
	std::string Fragment_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string,  int> m_UniformLocationCache;
public:
	Shader(const std::string& VertexShaderFilePath, const std::string& FragmentShaderFilePath);
	~Shader();
	void Bind() const;
	void unBind() const;

	void SetUniformMatrix4fv(const std::string& name, const GLfloat* value);
	void SetUniform1i(const std::string& name, const int value);
	void SetUniform4f(const std::string& name,float v0, float v1, float v2, float v3 );
private:
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	 int GetUniformLocation(const std::string& name);
};