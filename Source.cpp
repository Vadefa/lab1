#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
using namespace std;
void init(GLFWwindow* window) { }
void display(GLFWwindow* window, double currentTime) {
	glClearColor(1.0, 0.0, 0.0, 1.0);													//9) we specify the value that will be put in the elemenets of a color buffer when it'll be cleared
	glClear(GL_COLOR_BUFFER_BIT);														//8) calling OpenGL function that clears by set color (applies set color to) all buffers 
}
int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }											//1) initializing the GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);										//3) machine must be compatible with OpenGL version 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", NULL, NULL);	//2) initializing the GLFW Window and associated OpenGL context; width&height, title, fullscreen mode and resource shading
	glfwMakeContextCurrent(window);														//5) we need to make the created associated OpenGL context as the current
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }									//1) initializing the GLEW
	glfwSwapInterval(1);																//4) enabling Vectical synchronization (VSync)
	init(window);
	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());													//7) returns elapsed time since GLFW was initialized
		glfwSwapBuffers(window);														//4) enabling Vectical synchronization (VSync); 6) paints the screen
		glfwPollEvents();																//6) handles window-related events (such as a key being pressed)
	}
	glfwDestroyWindow(window);															//11) destrying the window
	glfwTerminate();																	//12) terminate the work with the GLFW, destroying all associated elements
	exit(EXIT_SUCCESS);
}