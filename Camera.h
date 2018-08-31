#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <iostream>

class Camera
{
public:
	//camera's attribute
	float fCameraPosX, fCameraPosY;
	float fCameraDirX, fCameraDirY;

private:
	float fLastCameraPosX;
	float fLastCameraPosY;
	//plane's attrinute
	unsigned short projectionPlaneWidth;
	unsigned short projectionPlaneHigth;
	float fProjectionPlaneLength;
	float fProjectionPlaneDirX, fProjectionPlaneDirY;

	bool collider;

public:
	static int map[20][20];

public:
	Camera(float posX, float posY, float dirX, float dirY) :
		fCameraPosX(posX), fCameraPosY(posY), fCameraDirX(dirX), fCameraDirY(dirY)
	{
		fProjectionPlaneLength = 0.66f;
		projectionPlaneWidth = 640;
		projectionPlaneHigth = 480;

		fLastCameraPosX = fCameraPosX;
		fLastCameraPosY = fCameraDirY;

		collider = true;
	}

	void rotate(float angle);
	void translate(float x, float y);
	void render();
	void collision();
};

#endif _CAMERA_H_