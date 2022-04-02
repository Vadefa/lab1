#include <iostream>
#include <GL/glew.h>									// ���������� ��������� CLEW - ������ ������ ���������� OpenGL
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VBO;

void RenderSceneCB() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	/////lesson 2
	glEnableVertexAttribArray(0);					// ������ ������� ����� ����� ������������ ������ � ����������� �������

	glBindBuffer(GL_ARRAY_BUFFER, VBO);				// ������� ��������� ����� ��� ���������

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);	// �������� ���������, ��� �� ����� ������������ ������ ������:
	/* ������ ��������, ���������� ����������� � ��� (� ��� 3 - X, Y � Z), ��� �����������, �������� ������������ ��������,
	*  ����� ���� ����� 2 ������������ ��������, �������� � ���������
	*/

	glDrawArrays(GL_POINTS, 0, 1);					// (����������) ������� ��� ���������: �����, ������ ������ �������	� �� ����������

	glDisableVertexAttribArray(0);					// ��������� ������ ������� �������

	glutSwapBuffers();								// � �������� ������� ����� � ����� ����� �������
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 01");
	
	glutDisplayFunc(RenderSceneCB);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//glutMainLoop();

	/////////////////////////////////////////////////////LESSON 2////////////////////////////////////////////////////

	GLenum res = glewInit();						// ����������������� GLEW
	if (res != GLEW_OK)								// �������� �� ������
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	

	glm::vec3 vec = glm::vec3(0.0f, 0.0f, 0.0f);	// ���������������� ������
	glm::vec3 vecArr[]{ vec };						// � ������ ��������
	//Vector3f Vertices[1];
	//Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);


	glGenBuffers(1, &VBO);							// ���������� ������� ��� ��������� ��������-����������
	// ���-�� �������� ��� �������� � ������ �� ������ GLuints ��� �������� ��������� �� ������ 


	glBindBuffer(GL_ARRAY_BUFFER, VBO);				// ������, ��� ����� ����� ������� ������ ������

	glBufferData(GL_ARRAY_BUFFER, sizeof(vecArr), vecArr, GL_STATIC_DRAW);	/* ��������� ������ �������:
	�������� ����, ������ ������(����), ����� �������, ���� ������������� ���������: ��� ��������� �������� ������ */
	
	glutMainLoop();									// �������� �������� GLUT
}