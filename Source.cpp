#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];

float x = 0.0f;											//6.1 location of triangle on x axis
float inc = 0.01f;										//6.1 offset for moving the triangle

string readShaderSource(const char* filePath) {
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";

	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "Shader Info Log: " << log << endl;
		free(log);
	}
}
void printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
	}
}
bool checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

GLuint createShaderProgram() {
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);			//2.2) generating a shader of type GL_VERTEX_SHADER, initially empty, and returning its id to vShader
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);		//2.2) generating a shader of type GL_FRAGMENT_SHADER, initially empty, and returning its id to fShader

	string vertShaderStr = readShaderSource("vertShader.glsl");	//4.1) we can make glsl shaders files using txt files
	string fragShaderStr = readShaderSource("fragShader.glsl");
	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();




	glShaderSource(vShader, 1, &vertShaderSrc, NULL);			//4.2) changed files on files read from txt//2.3) loading the GLSL code from strings vshaderSource and fshaderSource into the empty shader objects
	glShaderSource(fShader, 1, &fragShaderSrc, NULL);			/* parameters of the function :
																a) shader object in which to store the shader
																b) the number of strings in the shader source code
																c) an array of pointers to strings containing the source code
																d) an additional parameter we aren't using now
																*/
	GLint vertCompiled;											//3.1) variables for following checking if shaders were compiled and linked
	GLint fragCompiled;
	GLint linked;

	glCompileShader(vShader);									//2.4) compiling both shaders
	checkOpenGLError();											//3.2) checking if the vertex shader was complied
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) {
		cout << "vertex compilation failed" << endl;
		printShaderLog(vShader);
	}

	glCompileShader(fShader);
	checkOpenGLError();											//3.3) checking if the fragment shader was compiled
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) {
		cout << "fragment compilation failed" << endl;
		printShaderLog(fShader);
	}

	GLuint vfProgram = glCreateProgram();						//2.5) creating a program obect and saving the integer ID that points to it in the vfProgram
	glAttachShader(vfProgram, vShader);							//2.6) attaching shaders to the program object
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);									//2.7) requesting that the GLSL compiler ensure that shaders are compatible
	checkOpenGLError();											//3.4) checking if shaders were linked
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		cout << "linking failed" << endl;
		printProgramLog(vfProgram);
	}
	
	return vfProgram;
}

void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);							//2.12) we will consider it later. Just to know, OpenGL requires that at least one vertex array object be created whenever...
	glBindVertexArray(vao[0]);									//.. shaders are being used, even if we need to display only one point that does not require any buffers.
}
void display(GLFWwindow* window, double currentTime) {

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);														//6.2) clear the background to black, each time
	glUseProgram(renderingProgram);														//2.8) the function loads the program containing the two complied shaders into the OpenGL pipeline stages (onto the GPU)												
	x += inc;																			//6.3) move the triangle along x axis
	if (x > 1.0f) 
		inc = -0.01f;																	//6.4) switch to moving the triangle to the left
	if (x < -1.0f)
		inc = 0.01f;																	//6.5) switch to moving the triangle to the right
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");				//6.6) get ptr to "offset"
	glProgramUniform1f(renderingProgram, offsetLoc, x);									//6.7) send value in "x" to "offset"
	glDrawArrays(GL_TRIANGLES, 0, 3);													//5.1) displaying a triangle \\2.9) initiating pipline processing - displaying a single point
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }											//1.1) initializing the GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);										//1.3) machine must be compatible with OpenGL version 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", NULL, NULL);	//1.2) initializing the GLFW Window and associated OpenGL context; width&height, title, fullscreen mode and resource shading
	glfwMakeContextCurrent(window);														//1.5) we need to make the created associated OpenGL context as the current
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }									//1.1) initializing the GLEW
	glfwSwapInterval(1);																//1.4) enabling Vectical synchronization (VSync)
	init(window);
	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());													//1.7) returns elapsed time since GLFW was initialized
		glfwSwapBuffers(window);														//1.4) enabling Vectical synchronization (VSync); 6) paints the screen
		glfwPollEvents();																//1.6) handles window-related events (such as a key being pressed)
	}
	glfwDestroyWindow(window);															//1.11) destrying the window
	glfwTerminate();																	//1.12) terminate the work with the GLFW, destroying all associated elements
	exit(EXIT_SUCCESS);
}