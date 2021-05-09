#include <iostream>
#include <fstream>
#include <sstream>
#include "GL/glew.h"
#include "Structures.h"
#pragma once


int count = 0;
GLfloat* lineTodigigtss(std::string str) {
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

returned loadVerticiess(const std::string path)
{
	std::cout << std::endl << "Loader:: loading verticies coords. Path: " << path;
	count = 0;
	std::ifstream file(path);
	std::string line;
	if (file.is_open())
	{
		getline(file, line);
	}
	int i = 2;
	while (line[i] != ' ') {
		count = count * 10 + ((int)line[i] - 48);
		i++;
	}
	GLfloat* vertexArray = new GLfloat[count * 3];
	GLfloat* temparr = new GLfloat[3];
	int counter = 0;
	while (getline(file, line)) {
		temparr = lineTodigigtss(line);
		for (i = 0; i < 3; i++) {
			vertexArray[counter] = temparr[i];
			counter++;
		}
	}
	file.close();
	returned temp;
	temp.Lines = count;
	temp.Columns = counter / count;
	temp.data = vertexArray;
	return temp;
}




void unLoadUV(GLfloat* vertexArray)
{
	std::cout << std::endl << "Loader:: unloading UV coords.";
	GLfloat* temparray = new GLfloat[count * 5];
	temparray = vertexArray;
	vertexArray = new GLfloat[count * 3];
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < 3; j++) {
			vertexArray[i * 3 + j] = temparray[i * 5 + j];
		}
	}
}

returned loadVerticiesAndUVs(const std::string& pathVerticies, const std::string& pathUV)
{
	std::cout << std::endl << "Loader:: loading UV coords. Path: " << pathUV;
	std::ifstream file(pathUV);
	std::string line;
	GLfloat* vertexArray = loadVerticiess(pathVerticies).data;


	GLfloat* temparray = new GLfloat[count * 3];
	temparray = vertexArray;
	vertexArray = new GLfloat[count * 5];

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
	//vertexArray[0] = count; vertexArray[1] = 3;
//	vertexArray[2] = 2; vertexArray[3] = 0; vertexArray[4] = 0;
	returned temp;
	temp.Lines = count;
	temp.Columns = counter / count;
	temp.data = vertexArray;
	return temp;
}


void show(int layout, GLfloat* vertexArray) {
	std::cout << std::endl;
	for (int i = 0; i < count * layout; i++)
	{
		std::cout << vertexArray[i] << ",";
		if ((i + 1) % layout == 0)
			std::cout << std::endl;
	}
}




