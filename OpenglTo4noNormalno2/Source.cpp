#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <time.h>

#include "Loader.h"
//#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
//#include "object.h"
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

int width = 800;
int height = 600;


//object obj;

struct MVPS
{
	glm::mat4 Model;
	glm::mat4 View;
	glm::mat4 Projection;
};

MVPS mvpArray[2];

MVPS *selected;

glm::mat4 MVP;
glm::mat4 Model;
glm::mat4 View;
glm::mat4 Projection;

bool isobject = false;

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

	std::string pathvert = ("C:/Users/pilni/Desktop/OpenglTo4noNormalno2/OpenglTo4noNormalno2/res/objects/coords_shape/cube.wai");
	std::string pathuv = ("C:/Users/pilni/Desktop/OpenglTo4noNormalno2/OpenglTo4noNormalno2/res/objects/coords_uv/cubeUV.wai");

	returned temp = loadVerticiesAndUVs(pathvert, pathuv);

	VertexBuffer vb_square(temp.data,temp.Columns*temp.Lines*sizeof(GLfloat));
	//V/ertexBuffer vb_square(obj);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	unsigned int indicies[6] =
	{
		0,1,2,
		2,0,3,
	};

	IndexBuffer ib(indicies, 6);
	ib.Bind();
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


	Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	View = glm::lookAt(cameraPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	Model = glm::mat4(1.0f);

	glm::vec3 scale = glm::vec3(1.0f);

	std::string path = "res/picture1.png";
	std::string path2 = "res/picture1.png";
	

	//shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	double lasttime = glfwGetTime();
	glm::vec3 prevscale;
	glm::mat4 ModelNew = Model;
	bool smth = false;


	Texture texture(path);
	Texture texture2(path2);

	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);

	

	mvpArray[1].Model = glm::scale(Model, glm::vec3(0.2f, 0.2f, 0.2f));
	mvpArray[1].Model = glm::translate(Model, glm::vec3(-1.5f, 0.0f, 0.0f));
	mvpArray[1].Projection = Projection;
	mvpArray[1].View = View;

	mvpArray[0].Model = glm::scale(Model, glm::vec3(0.2f, 0.2f, 0.2f));
	mvpArray[0].Model = glm::translate(Model, glm::vec3(1.5f, 0.0f, 0.0f));
	mvpArray[0].Projection = Projection;
	mvpArray[0].View = View;

	selected = &mvpArray[0];

	do {
		glClearStencil(0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		ImGui_ImplGlfwGL3_NewFrame();

		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		
		for (int i = 0; i < 2; i++)
		{
			//selected->Model = glm::translate(Model, glm::vec3(-1.5f, 0.0f, 0.0f));
			MVP = mvpArray[i].Projection * mvpArray[i].View * mvpArray[i].Model;
			shader.SetUniformMatrix4fv("MVP", &MVP[0][0]);
			renderer.DrawVB(va, shader,i);
		}
		
		
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
			
			ImGui::Text((isobject) ? "some object" : "nothing");
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

static void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos){
	//if (!rotation) {
		if (!mouse){
			previousXpos = xPos;
			previousYpos = yPos;
			unsigned int index;
			glReadPixels(previousXpos, height - previousYpos - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
			if (index != 0)
				isobject = true;
			else
				isobject = false;
		}
		else if (mouse){
			glm::quat myquat;
			myquat = glm::angleAxis(glm::radians(((float)(previousXpos - xPos)) / 10), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::quat myquatY;
			myquatY = glm::angleAxis(glm::radians(((float)(previousYpos - yPos)) / 10), glm::vec3(1.0f, 0.0f, 0.0f));

			glm::vec3 temp;
			
			//selected->Model = glm::scale(Model, glm::vec3(0.2f, 0.2f, 0.2f));
	
			//
			for (int i = 0; i < 4; i++){
				temp = glm::vec3(selected->Model[i][0], selected->Model[i][1], selected->Model[i][2]) * myquat * myquatY;
				selected->Model[i][0] = temp[0];
				selected->Model[i][1] = temp[1];
				selected->Model[i][2] = temp[2];
			}
			

			//selected->Model = glm::translate(Model, glm::vec3(-1.5f, 0.0f, 0.0f));
			
			
			previousXpos = xPos;
			previousYpos = yPos;
		}
	}
//}



void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		mouse = true;
		
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		glReadPixels(previousXpos, height - previousYpos - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(previousXpos, height - previousYpos - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(previousXpos, height - previousYpos - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
			previousXpos, previousYpos, color[0], color[1], color[2], color[3], depth, index);
		selected = &mvpArray[index - 1];
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
		std::cout << "Left button released" << std::endl;
		mouse = false;
	}
}




