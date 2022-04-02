#include <iostream>
#include <GL/freeglut.h>								// добавили библиотеку

int main(int argc, char** argv) {
	
	glutInit(&argc, argv);								// инициализировали glut


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);		// настрили опции: двойную буферизацию и буфер цвета


	glutInitWindowSize(1024, 768);						// установили размер окна 1024 на 768 пикселей
	glutInitWindowPosition(100, 100);					// установили позицию на экране
	glutCreateWindow("Tutorial 01");					// заголовок окна
	
}