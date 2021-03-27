
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>
#include "returned.h"
#include "Texture.h"

struct Matricies
{
	glm::mat4 Model;
	glm::mat4 View;
	glm::mat4 Projection;
	Matricies()
		:Model(1.0f),
		 View(1.0f),
		 Projection(1.0f)
	{}
};

struct Properties {
	bool Visible;
};


class Object
{
public:
	char Name[16];
	Texture texture;
	VertexBuffer VB;
	VertexBufferLayout Layout;
	VertexArray VA;
	Shader shader;
	Matricies Matrix;
	glm::mat4 MVP;
	Properties propirties;

	Object(char* in_name, returned& RreturnedStruct, std::string& path);
	void Draw(Renderer& renderer, const int color);
	void Rotate(glm::quat& quatX, glm::quat& quatY);
	void Translate(const glm::vec3& translation);
	void Bind();
};