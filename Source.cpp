#include <iostream>
#include <GL/glew.h>									// подключили заголовок CLEW - раньше других заголовков OpenGL
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VBO;

void RenderSceneCB() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	/////lesson 2
	glEnableVertexAttribArray(0);					// задали нулевую св€зь между координатами вершин и параметрами шейдера

	glBindBuffer(GL_ARRAY_BUFFER, VBO);				// обратно прив€зали буфер дл€ отрисовки

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);	// сообщили конвейеру, как он будет воспринимать данные буфера:
	/* индекс атрибута, количество компонентов в нЄм (у нас 3 - X, Y и Z), тип компонентов, параметр нормализации атрибута,
	*  число байт между 2 экземпл€рами атрибута, смещение в структуре
	*/

	glDrawArrays(GL_POINTS, 0, 1);					// (пор€дкова€) функци€ дл€ отрисовки: точки, индекс первой вершины	и их количество

	glDisableVertexAttribArray(0);					// отключили каждый атрибут вершины

	glutSwapBuffers();								// и помен€ли фоновый буфер и буфер кадра местами
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

	GLenum res = glewInit();						// инициализирование GLEW
	if (res != GLEW_OK)								// проверка на ошибки
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	

	glm::vec3 vec = glm::vec3(0.0f, 0.0f, 0.0f);	// инициализировали вектор
	glm::vec3 vecArr[]{ vec };						// и массив векторов
	//Vector3f Vertices[1];
	//Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);


	glGenBuffers(1, &VBO);							// определили функцию дл€ генерации объектов-переменных
	// кол-во объектов дл€ создани€ и ссылка на массив GLuints дл€ хранени€ указател€ на данные 


	glBindBuffer(GL_ARRAY_BUFFER, VBO);				// задали, что буфер будет хранить массив вершин

	glBufferData(GL_ARRAY_BUFFER, sizeof(vecArr), vecArr, GL_STATIC_DRAW);	/* наполнили объект данными:
	название цели, размер данных(байт), адрес массива, флаг использовани€ паттернов: без изменений значений буфера */
	glutMainLoop();

}