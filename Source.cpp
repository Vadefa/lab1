#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

using namespace std;

#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];

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
	const char* vshaderSource =									//2.1) declaring character string vshaderSource: the vertex shader
		"#version 430 \n"										//2.9) indicating OpenGL version
		"void main(void) \n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";			//2.10) this variable sets vertex's coordinate position in 3D space (to the origin location); and it being sent next to the pipeline
	const char* fshaderSource =									//2.1) declaring character string fshaderSource: the fragment shader
		"#version 430 \n"
		"out vec4 color; \n"									//2.11) the "out" tag indicates that the variable color is an output
		"void main(void) \n"
		"{  if (gl_FragCoord.x < 200) color = vec4(1.0, 0.0, 0.0, 1.0); else color = vec4(0.0, 0.0, 1.0, 1.0); }";
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);			//2.2) generating a shader of type GL_VERTEX_SHADER, initially empty, and returning its id to vShader
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);		//2.2) generating a shader of type GL_FRAGMENT_SHADER, initially empty, and returning its id to fShader
	glShaderSource(vShader, 1, &vshaderSource, NULL);			//2.3) loading the GLSL code from strings vshaderSource and fshaderSource into the empty shader objects
	glShaderSource(fShader, 1, &fshaderSource, NULL);			/* parameters of the function: 
																a) shader object in which to store the shader
																b) the number of strings in the shader source code
																c) an array of pointers to strings containing the source code
																d) an additional parameter we aren't using now
																*/
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	glCompileShader(vShader);									//2.4) compiling both shaders
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) {
		cout << "vertex compilation failed" << endl;
		printShaderLog(vShader);
	}

	glCompileShader(fShader);
	checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) {
		cout << "fragment compilation failed" << endl;
		printShaderLog(fShader);
	}

	GLuint vfProgram = glCreateProgram();						//2.5) creating a program obect and saving the integer ID that points to it in the vfProgram
	glAttachShader(vfProgram, vShader);							//2.6) attaching shaders to the program object
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);									//2.7) requesting that the GLSL compiler ensure that shaders are compatible
	checkOpenGLError();
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
	glUseProgram(renderingProgram);														//2.8) the function loads the program containing the two complied shaders into the OpenGL pipeline stages (onto the GPU)
	glPointSize(30.0f);																	//2.13) in the rasterizer default points size is 1 pixel. Here we set it to 30 pixels.
	glDrawArrays(GL_POINTS, 0, 1);														//2.9) initiating pipline processing - displaying a single point
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