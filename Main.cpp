#include "Camera.h"

#include <glut.h>
#include <cmath>
#include <ctime>
#include <iostream>

#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut.lib")

#define _PROJECTIONPLANE_WIDTH_ 640
#define _PROJECTIONPLANE_HIGTH_ 480

Camera cam(1.0f, 1.0f, 1.0f, 0.0f);

//********************************//
//Drow image after render
//********************************//
void drow(){
	cam.collision();
	cam.render();
}

float kMoveX = 0, kMoveY = 0;
float kRotate = 0;

clock_t startTime = 0;
clock_t endTime = 0;

void timer(int value){
	startTime = clock();
	drow();
	endTime = clock();

	clock_t frameTime = endTime - startTime;
	float deltaTime = float(frameTime) / CLOCKS_PER_SEC;

	cam.rotate(180.0f * deltaTime * kRotate);
	cam.translate(5 * kMoveX * deltaTime, 5 * kMoveY * deltaTime);

	glutTimerFunc(frameTime, timer, 0);
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-_PROJECTIONPLANE_WIDTH_ / 2, _PROJECTIONPLANE_WIDTH_ / 2,
		-_PROJECTIONPLANE_HIGTH_ / 2, _PROJECTIONPLANE_HIGTH_ / 2);
}

void keyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		kMoveX = 1.0f;
		kMoveY = 1.0f;
		break;
	case 's':
		kMoveX = -1.0f;
		kMoveY = -1.0f;
		break;
	case 'a':
		kRotate = -1.5f;
		break;
	case 'd':
		kRotate = 1.5f;
		break;
	}
}

void keyBoardUp(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		kMoveX = 0.0f;
		kMoveY = 0.0f;
		break;
	case 's':
		kMoveX = 0.0f;
		kMoveY = 0.0f;
		break;
	case 'a':
		kRotate = 0.0f;
		break;
	case 'd':
		kRotate = 0.0f;
		break;
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(_PROJECTIONPLANE_WIDTH_, _PROJECTIONPLANE_HIGTH_);
	glutCreateWindow("Raycasting");

	init();

	glutDisplayFunc(drow);
	glutKeyboardFunc(keyBoard);
	glutKeyboardUpFunc(keyBoardUp);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
	return 0;
}