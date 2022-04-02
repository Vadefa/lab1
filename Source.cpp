#include <iostream>
#include <GL/freeglut.h>			// добавили библиотеку

int main(int argc, char** argv) {
	
	glutInit(&argc, argv);			// инициализировали glut

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);		// настрили опции: двойную буферизацию и буфер цвета


}