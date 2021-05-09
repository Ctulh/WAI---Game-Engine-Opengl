#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Structures.h"
#pragma once

GLfloat* DivideTriangle(const glm::vec3 Top, const glm::vec3 Left, const glm::vec3 Right);
GLfloat* Normalize(GLfloat* _inArray, int count, double radius);
GLfloat* DivideTriangleFromReturned(const returned ReturnedStruct);

class Shape {
public:
	GLfloat* data;
	std::size_t vertex_count;
public: Shape(GLfloat* _data, std::size_t _vertex_count);
	  ~Shape();
};


class Sphere : public Shape {
public:	int detail_Level;
	glm::vec3 Center;
	Sphere();
	Sphere(returned ReturnedStruct);
    
	
};
