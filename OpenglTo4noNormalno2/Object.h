#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>
#include "Structures.h"
#include "Texture.h"
#include <string>

struct Matricies
{
	glm::mat4 Model;
	glm::mat4 Projection;
	Matricies()
		:Model(1.0f),
		 Projection(1.0f)
	{}
};

struct Properties{
	bool Visible;
	bool Texture;
	int Texture_ID;
};


class Object
{
public:
	char Name[16];
	int TextureIndex;
	VertexBuffer VB;
	VertexBufferLayout Layout;
	VertexArray VA;
	Matricies Matrix;
	glm::mat4 MVP;
	glm::vec4 Color;
	Properties properties;
	ModelConstituent ModelComponents;
	glm::mat4 OriginalModel;
	bool Changes;

	Object(char* in_name, returned& RreturnedStruct, int _index);
	Object(char* in_name, GLfloat* data, int _index);
	void Draw(Renderer &renderer, Shader &shader,const int color, const glm::mat4& View);
	void Rotate(glm::quat& quatX, glm::quat& quatY);
	void Translate(const glm::vec3& translation);
	void Translate();
	void Scale(glm::vec3& newvec);
	void Bind(const glm::mat4& View, Shader &shader);

};