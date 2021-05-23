#include "Shape.h"
//#include "Loader.h"
#include <iostream>

returned loadVerticiess(const std::string path);

GLfloat* DivideTriangle(const glm::vec3 Top, const glm::vec3 Left, const glm::vec3 Right) {
	GLfloat* _returnedArr = new GLfloat[36];
	_returnedArr[0] = Top.x;
	_returnedArr[1] = Top.y;
	_returnedArr[2] = Top.z;
	_returnedArr[3] = (Left.x + Top.x) / 2;
	_returnedArr[4] = (Left.y + Top.y) / 2;
	_returnedArr[5] = (Left.z + Top.z) / 2;
	_returnedArr[6] = (Right.x + Top.x) / 2;
	_returnedArr[7] = (Right.y + Top.y) / 2;
	_returnedArr[8] = (Right.z + Top.z) / 2;//_________________Top triangle
	_returnedArr[9] = _returnedArr[3];
	_returnedArr[10] = _returnedArr[4];
	_returnedArr[11] = _returnedArr[5];
	_returnedArr[12] = Left.x;
	_returnedArr[13] = Left.y;
	_returnedArr[14] = Left.z;
	_returnedArr[15] = (Left.x + Right.x) / 2;
	_returnedArr[16] = (Left.y + Right.y) / 2;
	_returnedArr[17] = (Left.z + Right.z) / 2;//_________________Left triangle
	_returnedArr[18] = _returnedArr[6];
	_returnedArr[19] = _returnedArr[7];
	_returnedArr[20] = _returnedArr[8];
	_returnedArr[21] = _returnedArr[15];
	_returnedArr[22] = _returnedArr[16];
	_returnedArr[23] = _returnedArr[17];
	_returnedArr[24] = Right.x;
	_returnedArr[25] = Right.y;
	_returnedArr[26] = Right.z;//_________________Right triangle
	_returnedArr[27] = _returnedArr[15];
	_returnedArr[28] = _returnedArr[16];
	_returnedArr[29] = _returnedArr[17];
	_returnedArr[30] = _returnedArr[3];
	_returnedArr[31] = _returnedArr[4];
	_returnedArr[32] = _returnedArr[5];
	_returnedArr[33] = _returnedArr[6];
	_returnedArr[34] = _returnedArr[7];
	_returnedArr[35] = _returnedArr[8];//_________________Middle triangle
	return _returnedArr;
}

GLfloat* DivideTriangleFromReturned(const returned ReturnedStruct) {
	GLfloat* Array = new GLfloat[1152];
	for (int i = 0; i < 8; i++) {
		GLfloat* temp = DivideTriangle(
			glm::vec3(ReturnedStruct.data[i * 9], ReturnedStruct.data[i * 9 + 1], ReturnedStruct.data[i * 9 + 2]),
			glm::vec3(ReturnedStruct.data[i * 9 + 3], ReturnedStruct.data[i * 9 + 4], ReturnedStruct.data[i * 9 + 5]),
			glm::vec3(ReturnedStruct.data[i * 9 + 6], ReturnedStruct.data[i * 9 + 7], ReturnedStruct.data[i * 9 + 8])
		);
		for (int j = 0; j < 36; j++) {
			Array[i * 36 + j] = temp[j];
		}
	}
	return Array;
}


GLfloat* Normalize(GLfloat* _inArray, int count, double radius) {
	for (int i = 0; i < count / 3; i++) {
		GLfloat dx = _inArray[i * 3];
		GLfloat dy = _inArray[i * 3 + 1];
		GLfloat dz = _inArray[i * 3 + 2];
		GLfloat radiusDivDistance = radius / glm::distance(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(dx, dy, dz));
		dx = dx * radiusDivDistance;
		dy = dy * radiusDivDistance;
		dz = dz * radiusDivDistance;
		_inArray[i * 3] = dx;
		_inArray[i * 3 + 1] = dy;
		_inArray[i * 3 + 2] = dz;
	}
	return _inArray;
}



Shape::Shape(GLfloat* _data, std::size_t _vertex_count)
	:data(_data),
	vertex_count(_vertex_count)
{
	std::cout << std::endl << vertex_count;
}
Shape::~Shape() { delete[] data; }


Sphere::Sphere(returned ReturnedStruct)
	:Shape(Normalize(DivideTriangleFromReturned(ReturnedStruct), ReturnedStruct.Lines* ReturnedStruct.Columns * 4, 1), ReturnedStruct.Lines* ReturnedStruct.Columns * 4),
	//Shape(DivideTriangleFromReturned((ReturnedStruct)),72),
	detail_Level(1),
	Center(0.0, 0.0f, 0.0f)
{};


Sphere::Sphere()
	:Sphere(loadVerticiess("res/objects/coords_shape/ball.wai"))
{};