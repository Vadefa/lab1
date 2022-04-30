#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint createShaderProgram() {
	const char* vshaderSource =
		"#version 430 \n"
		"void main(void) \n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
	const char* fshaderSource =
		"#version 430 \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ color = vec4(0.0, 0.0, 1.0, 1.0); }";
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
	glCompileShader(vShader);
	glCompileShader(fShader);
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
	return vfProgram;
}
void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}
void display(GLFWwindow* window, double currentTime) {
	glUseProgram(renderingProgram);
	glDrawArrays(GL_POINTS, 0, 1);
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