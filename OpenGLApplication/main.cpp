#include <GL/glew.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stdio.h>
#include "player.cpp"
#include "LoadShaders.h"

using namespace std;
using namespace glm;

void initilizeWindow();
void initializeDependencies(void);
void drawRectangle(float* vertArray);
void redrawScreen(GLFWwindow* window);
void updateGameState();
int getCurrentTime();
void windowResizeCallback(GLFWwindow* window, int width, int height);
void handleKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mode);

GLfloat test[] = {
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f
};

enum VAO_IDs { Triangles = 0, VAOSize = 1 };
enum Buffer_IDs { ArrayBuffer = 0, VBOSize = 1};
enum Attrib_IDs { vPosition = 0 };
enum Game_Loop { MS_PER_UPDATE = 16 };

Player* player;

unsigned int vaoID[VAOSize];
unsigned int vboID[VBOSize];

float xOrigin = 0;
float yOrigin = 0;

GLFWwindow* window;

GLuint vertexArrays[VAOSize];
GLuint buffers[VBOSize];
bool isFullscreen = false;

float aspectRatio = 16.0f / 9.0f;
float windowHeight = 400;
float windowWidth = windowHeight * aspectRatio;

int main() {

	initilizeWindow();
	initializeDependencies();
	player = new Player(-1, -1, 1, 1);

	bool runGame = true;
	double previous = getCurrentTime();
	double lag = 0.0;
	double current = 0;
	double elapsed = 0;

	int secondCounter = 0;
	int fps = 0;


	while (runGame)
	{
		current = getCurrentTime();
		elapsed = current - previous;
		secondCounter += elapsed;
		previous = current;
		lag += elapsed;

		glfwPollEvents();

		while (lag >= MS_PER_UPDATE)
		{
			updateGameState();
			lag -= MS_PER_UPDATE;
		}

		redrawScreen(window);
		fps++;

		if (secondCounter > 1000)
		{
			secondCounter = 0;
			char title[256];
			title[255] = '\0';
			snprintf(title, 255, "%s %s - [FPS: %d]", "Name", "Version", fps);
			glfwSetWindowTitle(window, title);
			fps = 0;
		}
	}

	glfwTerminate();
	return 0;
}

void initializeDependencies(void) {

	glClearColor(0, 1, 0, 1);

	glGenVertexArrays(VAOSize, &vaoID[Triangles]);
	glBindVertexArray(vaoID[Triangles]);

	glGenBuffers(VBOSize, &vboID[ArrayBuffer]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[ArrayBuffer]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "C:\\Users\\Christopher\\Documents\\visual studio 2015\\Projects\\OpenGLApplication\\OpenGLApplication\\triangles.vert" },
		{ GL_FRAGMENT_SHADER, "C:\\Users\\Christopher\\Documents\\visual studio 2015\\Projects\\OpenGLApplication\\OpenGLApplication\\triangles.frag" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
}

void initilizeWindow()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(-1);
	}

	window = glfwCreateWindow(windowWidth, windowHeight, "Shark Week", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewervoid 
	gluPerspective(120, 16, 1.0f, 100.0f);

	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glfwSetKeyCallback(window, handleKeyboardInput);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
}

void redrawScreen(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	//gluLookAt(6.0f, 6.0f, 6.0f,
	//		  0.0f, 1.0f, 0.0f,
	//          0.0f, 1.0f, 0.0f);

	glLoadIdentity();
	drawRectangle(test);


	//gluLookAt(10.0, 10.0, 10.0, 1.5, -1.0, 1.5, 0.0, 0.0, 1.0);
	//drawRectangle(player->getVertexArray());

	glfwSwapBuffers(window);
	glTranslatef(0.0, 0.0, -10.5);
	glFlush();
}

void updateGameState()
{
}

int getCurrentTime()
{
	return glfwGetTime();
}

void drawRectangle(float* vertArray)
{
	glBufferData(GL_ARRAY_BUFFER, 12 * 3 * sizeof(GLfloat), vertArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[ArrayBuffer]);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
}

void handleKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key) 
	{
	case GLFW_KEY_D:
		break;
	case GLFW_KEY_A:
		break;
	case GLFW_KEY_SPACE:
		if (action == GLFW_PRESS)
		break;
	}
}

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	glfwSetWindowSize(window, width, height);
	glViewport(0, 0, width, height);
}