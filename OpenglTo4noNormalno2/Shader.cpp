#include "Shader.h"
#include "Renderer.h"


Shader::Shader(const std::string& VertexShaderFilePath, const std::string& FragmentShaderFilePath)
	:Vertex_FilePath(VertexShaderFilePath),Fragment_FilePath(FragmentShaderFilePath)
{
	m_RendererID = CreateShader(VertexShaderFilePath, FragmentShaderFilePath);
}

Shader::~Shader()
{
	GLCall(glDeleteShader(m_RendererID));
}


unsigned int Shader::CompileShader(unsigned int type,const std::string& source)
{

	std::string ShaderCode;
	std::ifstream ShaderStream(source, std::ios::in);
	if (ShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << ShaderStream.rdbuf();
		ShaderCode = sstr.str();
		ShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", source);
		getchar();
		return 0;
	}
	char const* SourcePointer = ShaderCode.c_str();

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	//glShaderSource(id, 1, &src, nullptr);
	//glCompileShader(id);
	printf("Compiling shader : %s\n", source.c_str());
	GLCall(glShaderSource(id, 1, &SourcePointer, NULL));
	GLCall(glCompileShader(id));
	

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader";
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}



unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int VS = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int FS = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	printf("Linking program\n");
	GLCall(glAttachShader(program, VS));
	GLCall(glAttachShader(program, FS));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));
	GLCall(glDeleteShader(VS));
	GLCall(glDeleteShader(FS));
	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::unBind() const
{
	GLCall(glUseProgram(0));
}

 int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
  GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "uniform " << name << " doesn't exist";
	else
		m_UniformLocationCache[name] = location;
	return location;
}

 void Shader::SetUniform1i(const std::string& name, const int value) 
 { 
	 GLCall(glUniform1i(GetUniformLocation(name), value));
 }

 void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) 
 {
	 GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
 }

void Shader::SetUniformMatrix4fv(const std::string& name,const GLfloat* value) 
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,value));
}



