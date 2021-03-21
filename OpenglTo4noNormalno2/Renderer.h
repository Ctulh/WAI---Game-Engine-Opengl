#pragma once

#include <string> 
#include <gl/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"




#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__, __LINE__))

 void GLClearError(); 
 bool GLLogCall(const char* function, const char* file, int line);

 class Renderer
 {
 public:
	 void Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader) const;
	 void DrawVB(const VertexArray& va, const Shader& shader,const int color) const;
	 //void DrawObjectArray(const ObjectArray& obj) const;
 };