#include <gl/glew.h>
#include <string>
//#include "VertexArray.h"

enum types
{
	CUBE
};


class object
{
private:
	types type;
	unsigned int LineCount;
	int ColumnCount;
public:
	GLfloat* vertexArray;
public:
	object();
	~object();
	void loadVerticies(std::string path);
	void loadUV(std::string path);
	void unLoadUV();
	void show(int layout);
	int sizeGLfloat();
	int count();
	//bool test(float x, float y,object &obj,const glm::mat4 *value);
};

