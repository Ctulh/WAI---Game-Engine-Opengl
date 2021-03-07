#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <time.h>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "object.h"
#include "src/imgui/imgui.h"
#include "src/imgui/imgui_impl_glfw_gl3.h"
#include "stb_image.h"
#include "Renderer.h"

#define fps 60

struct Vertex
{
	glm::vec3 position;
};

glm::vec3 cameraPos(0.0f, 0.0f, 4.0f);
bool rotation = false;

int initial_time = time(NULL), final_time;

static void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);

bool mouse = false;
int previousXpos;
int previousYpos;

object obj;

glm::mat4 MVP;
glm::mat4 Model;
glm::mat4 View;

int main()
{
	glewExperimental = true;
	if (!glfwInit())
	{
		fprintf(stderr, "something goes wrong");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	GLFWwindow* window;



	window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "something goes wrong");
		return -1;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;

	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f);





	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);





	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));



	obj.loadVerticies("C:/Users/pilni/Desktop/OpenglTo4noNormalno2/OpenglTo4noNormalno2/res/objects/coords_shape/cube.wai");
	obj.loadUV("C:/Users/pilni/source/repos/OpenGLTo4noNormalno/OpenGLTo4noNormalno/res/objects/coords_uv/cubeUV.wai");


	VertexBuffer vb_square(obj.vertexArray, obj.sizeGLfloat());
	//V/ertexBuffer vb_square(obj);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	/*unsigned int indicies[6] =
	{
		0,1,2,
		2,0,3,
	};*/

	//IndexBuffer ib(indicies, 6);
	//ib.Bind();
	VertexArray va;
	va.AddBuffer(vb_square, layout);

	va.Bind();

	Shader shader("vertex.shader", "fragment.shader");
	shader.Bind();


	Renderer renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);


	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	View = glm::lookAt(cameraPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	Model = glm::mat4(1.0f);

	glm::vec3 scale = glm::vec3(1.0f);

	std::string path = "res/picture.png";
	Texture texture(path);
	texture.Bind();

	shader.SetUniform1i("u_Texture", 0);

	//shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	double lasttime = glfwGetTime();
	glm::vec3 prevscale;
	glm::mat4 ModelNew = Model;
	bool smth = false;







	//va.AddBuffer()
	Model = glm::scale(Model, glm::vec3(0.5f, 0.5f, 0.5f));
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);


		ImGui_ImplGlfwGL3_NewFrame();


		MVP = Projection * View * Model;

		shader.SetUniformMatrix4fv("MVP", &MVP[0][0]);




		renderer.DrawVB(va,shader);	
		//renderer.Draw(va, ib, shader);
		{
			ImGui::Checkbox("Rotation", &rotation);
			ImGui::SliderFloat3("Scale", &scale.x, 0.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f   
			if (ImGui::IsItemActive())
			{
				if (scale != prevscale)
				{
					Model = glm::scale(ModelNew, scale);
				}
			}
			ImGui::Button("UV");
			if (ImGui::IsItemClicked())
			{

			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}


		{	ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

		glfwPollEvents();

		while (glfwGetTime() < lasttime + 1.0 / fps) {

		}

		lasttime += 1.0 / fps;

		prevscale = scale; }

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

static void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (rotation) {
		if (!mouse)
		{
			previousXpos = xPos;
			previousYpos = yPos;
		}
		else if (mouse)
		{
			glm::quat myquat;
			myquat = glm::angleAxis(glm::radians(((float)(previousXpos - xPos)) / 10), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::quat myquatY;
			myquatY = glm::angleAxis(glm::radians(((float)(previousYpos - yPos)) / 10), glm::vec3(1.0f, 0.0f, 0.0f));

			glm::vec3 temp;
			for (int i = 0; i < 4; i++)
			{
				temp = glm::vec3(Model[i][0], Model[i][1], Model[i][2]) * myquat * myquatY;
				Model[i][0] = temp[0];
				Model[i][1] = temp[1];
				Model[i][2] = temp[2];
			}

			previousXpos = xPos;
			previousYpos = yPos;
		}
	}
}



void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		mouse = true;
		std::cout << "Left Button pressed";
		//std::cout << "Left button pressed" << std::endl;
		//mouse = true;
		//std::cout << "X: " << previousXpos << " " << "normalized x: " << (previousXpos - 400) * 1.0 / 400 << std::endl;
		//std::cout << "Y: " << previousYpos << " " << "normalized y: " << (previousYpos - 300) * 1.0 / -300 << std::endl;
		//if(obj.test((previousXpos-400)*1.0/400, (previousYpos-300)*1.0/300,obj,MVP))
			//std::cout<<std::endl<<"Collision succeed"<<std::endl;
		/*for (int i = 0; i < obj.count() / 3; i++)
		{
			glm::vec4 tmp = (MVP * glm::vec4(obj.vertexArray[i], obj.vertexArray[i+1], obj.vertexArray[i+2], 0));
			std::cout << i << ". " << tmp[0] << "," << tmp[1] << "," << tmp[2] <<  std::endl;
		}*/

	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		std::cout << "Left button released" << std::endl;
		mouse = false;
	}
}




