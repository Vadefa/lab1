#include <iostream>
#include <GL/freeglut.h>								// �������� ����������

int main(int argc, char** argv) {
	
	glutInit(&argc, argv);								// ���������������� glut


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);		// �������� �����: ������� ����������� � ����� �����


	glutInitWindowSize(1024, 768);						// ���������� ������ ���� 1024 �� 768 ��������
	glutInitWindowPosition(100, 100);					// ���������� ������� �� ������
	glutCreateWindow("Tutorial 01");					// ��������� ����
	
}