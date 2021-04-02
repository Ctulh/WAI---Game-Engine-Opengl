#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <time.h>

#include "Structures.h"
#include "Loader.h"
//#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Object.h"
#include "src/imgui/imgui.h"
#include "src/imgui/imgui_impl_glfw_gl3.h"
#include "stb_image.h"
#include "Renderer.h"
#include "ObjectArray.h"
#define fps 60

enum MyItemColumnID
{
	MyItemColumnID_ID,
	MyItemColumnID_Name,
	MyItemColumnID_Action,
	MyItemColumnID_Quantity,
	MyItemColumnID_Description
};

glm::vec3 cameraPos(0.0f, 0.0f, 4.0f);
bool rotation = false;

int initial_time = time(NULL), final_time;

static void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);

bool mouse = false;
int previousXpos;
int previousYpos;

int width = 1600;
int height = 900;

GLuint index;
Object* selected;

glm::mat4 MVP;
glm::mat4 Model;
glm::mat4 View;
glm::mat4 Projection;

bool isobject = false;

std::size_t objects_size = 0;
int SelectedObjectIndex = 0;


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



	window = glfwCreateWindow(1600, 900, "Test", NULL, NULL);
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
	std::string pathArrow = ("C:/Users/pilni/Desktop/OpenglTo4noNormalno2/OpenglTo4noNormalno2/res/objects/coords_shape/square.wai");


	returned temp = loadVerticiesAndUVs(pathvert, pathuv);
	returned tempArrow = loadVerticiess(pathArrow);

	Shader shader("vertex.shader", "fragment.shader");
	shader.Bind();


	Renderer renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);



	Model = glm::mat4(1.0f);

	glm::vec3 scale = glm::vec3(1.0f);

	std::string path = "res/picture1.png";
	std::string path2 = "res/clear.png";

	Texture text(path2);
	double lasttime = glfwGetTime();
	glm::vec3 prevscale;
	glm::mat4 ModelNew = Model;
	
	ObjectArray objects;
	objects.Add(temp, path);
	objects_size++;
	bool visible = true;

	Model = glm::mat4(1.0f);
	View = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	Projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	MVP = Projection * View * Model;


	glm::mat4 Model_N = glm::mat4(1.0f);
	glm::mat4 View_N = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 Projection_N = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	glm::mat4 MVP_N = Projection_N * View_N * Model_N;


	do {
		glClearStencil(0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);


		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		selected = objects.Array[SelectedObjectIndex];
		objects.Draw(renderer);

		static int selected_row = 0;
		glStencilFunc(GL_ALWAYS, 255, 0);
		{
			ImGui_ImplGlfwGL3_NewFrame();
			ImGui::Begin("Objects", NULL);
			if (ImGui::BeginTable("##table1", 3))
			{
				ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoHide, 0.0f, MyItemColumnID_ID);
				ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Name);
				ImGui::TableSetupColumn("Visible", ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Action);
				ImGui::TableHeadersRow();
				for (int i = 0; i < objects_size; i++) {
					ImGui::PushID(i);
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text(&std::to_string(i)[0]);
					if (ImGui::TableSetColumnIndex(2))
					{
						if (ImGui::RadioButton("", objects.Array[i]->properties.Visible)) {
							objects.Array[i]->properties.Visible = !objects.Array[i]->properties.Visible;
						}
					}
					ImGui::TableSetColumnIndex(1);
					if (ImGui::Selectable(objects.Array[i]->Name, selected_row == i))
					{
						SelectedObjectIndex = i;
						selected_row = i;
					}
					ImGui::SetItemAllowOverlap();
					ImGui::PopID();
				}


				ImGui::EndTable();
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
			ImGui::Begin("Functions", NULL);
			ImGui::Button("Add Cube");
			if (ImGui::IsItemDeactivated()) {
				objects.Add(temp, path);
				objects_size++;
			}
			ImGui::End();
			
			ImGui::Begin("Properties", NULL);
			ImGui::Checkbox("Texture", &selected->properties.Texture);
			
			ImGui::End();


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

static void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
	if (!mouse) {
		previousXpos = xPos;
		previousYpos = yPos;
		unsigned int index;
		glReadPixels(previousXpos, height - previousYpos - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		if (index != 0)
			isobject = true;
		else
			isobject = false;
	}
	else if (mouse) {
		if (index != 255) {
			glm::quat myquatX;
			myquatX = glm::angleAxis(glm::radians(((float)(previousXpos - xPos)) / 10), glm::vec3(0.0f, -1.0f, 0.0f));
			glm::quat myquatY;
			myquatY = glm::angleAxis(glm::radians(((float)(previousYpos - yPos)) / 10), glm::vec3(-1.0f, 0.0f, 0.0f));
			selected->Rotate(myquatX, myquatY);
			previousXpos = xPos;
			previousYpos = yPos;
		}
	}
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mouse = true;

		GLbyte color[4];
		GLfloat depth;
		//GLuint index;

		glReadPixels(previousXpos, height - previousYpos - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(previousXpos, height - previousYpos - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(previousXpos, height - previousYpos - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
			previousXpos, previousYpos, color[0], color[1], color[2], color[3], depth, index);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		std::cout << "Left button released" << std::endl;
		mouse = false;
	}
}