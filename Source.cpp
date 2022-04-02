#include <iostream>
#include <GL/glew.h>									// подключили заголовок CLEW - раньше других заголовков OpenGL
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void RenderSceneCB() {
	
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_ARRAY);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 01");
	
	glutDisplayFunc(RenderSceneCB);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();

	//////////LESSON 2

	GLenum res = glewInit();						// инициализирование GLEW
	if (res != GLEW_OK)								// проверка на ошибки
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	
	glm::vec3 vec = glm::vec3(0.0f, 0.0f, 0.0f);
	
	//Vector3f Vertices[1];
	//Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
}