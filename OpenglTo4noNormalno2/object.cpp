#include <iostream>
#include <fstream>
#include <sstream>
#include "object.h"
#include <glm/gtx/transform.hpp>


int object::count() {
	return ColumnCount * LineCount;
}

int object::sizeGLfloat() {
	return ColumnCount * LineCount*sizeof(GLfloat);
}

void object::unLoadUV()
{
	GLfloat* temparray = new GLfloat[LineCount * 5];
	temparray = vertexArray;
	vertexArray = new GLfloat[LineCount * 3];
	for (int i = 0; i < LineCount; i++)
	{
		for (int j = 0; j < 3; j++) {
			vertexArray[i * 3 + j] = temparray[i * 5 + j];
		}
	}
	ColumnCount -= 2;
}

void object::loadUV(std::string path)
{
	std::ifstream file(path);
	std::string line;

	GLfloat* temparray = new GLfloat[LineCount * 3];
	temparray = vertexArray;
	vertexArray = new GLfloat[LineCount * 5];

	size_t counter = 0;
	size_t counterForTemp = 0;

	if (file.is_open()) {
		while (getline(file, line)) {
			for (int i = 0; i < 3; i++) {
				vertexArray[counter + i] = temparray[counterForTemp + i];
			}
			counter += 3; counterForTemp += 3;

			std::string tempstr;
			for (int i = 0; i < line.length(); i++) {
				if (line[i] != 'f' && line[i] != ',')
					tempstr += line[i];
				else if (line[i] == 'f') {
					vertexArray[counter] = stof(tempstr);
					float tempf = stof(tempstr);
					counter++;
					tempstr = "";
				}
			}
		}
	}
	file.close();
	ColumnCount += 2;
}

object::~object() {
	delete[] vertexArray;
}

void object::show(int layout) {
	std::cout << std::endl;
	for (int i = 0; i < LineCount * layout; i++)
	{
		std::cout << vertexArray[i] << ",";
		if ((i + 1) % layout == 0)
			std::cout << std::endl;
	}
}

GLfloat* lineTodigigts(std::string str) {
	bool minus = false;
	int counter = 0;
	GLfloat* returned = new GLfloat[3];
	for (int i = 0; str[i]; i++) {
		if (str[i] == '-') {
			minus = true;
		}
		else if (isdigit(str[i])) {
			int numb = (int)str[i] - 48;
			if (minus) {
				numb = -numb;
				minus = false;
			}
			returned[counter] = numb;
			counter++;
		}
	}
	return returned;
}


object::object()
	:type(CUBE)
{
	vertexArray = {};
	LineCount = 0;
	ColumnCount = 0;
}


void object::loadVerticies(std::string path)
{
	LineCount = 0;
	std::ifstream file(path);
	std::string line;
	if (file.is_open())
	{
		getline(file, line);
	}
	int i = 2;
	while (line[i] != ' ') {
		LineCount = LineCount * 10 + ((int)line[i] - 48);
		i++;
	}
	vertexArray = new GLfloat[LineCount * 3];
	GLfloat* temparr = new GLfloat[3];
	int counter = 0;
	while (getline(file, line)) {
		temparr = lineTodigigts(line);
		for (i = 0; i < 3; i++) {
			vertexArray[counter] = temparr[i];
			counter++;
		}
	}
	ColumnCount += 3;
	file.close();
}
