#include "Camera.h"

#include <cmath>
#include <glut.h>
#include <iostream>

int Camera::map[20][20] = { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
							{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
							{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
							{ 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
							{ 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
							{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
							{ 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
							{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
							{ 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
							{ 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
							{ 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
							{ 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
							{ 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
							{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
							{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };

void Camera::render() {
	//						   | cos(90) -sin(90) |   
	//fProjectionPlaneVector = |				  | * fCameraVector
	//						   | sin(90) cos(90)  |
	fProjectionPlaneDirX = -fCameraDirY;
	fProjectionPlaneDirY = fCameraDirX;

	glClear(GL_COLOR_BUFFER_BIT);

	for (int x = 0; x < projectionPlaneWidth; x++)
	{
		float fProjectionPlaneOffset = 2 * x * fProjectionPlaneLength / 
			(projectionPlaneWidth - 1) - fProjectionPlaneLength;

		float fRayPosX, fRayPosY;

		float fRayDirX = fCameraDirX + fProjectionPlaneDirX * fProjectionPlaneOffset;
		float fRayDirY = fCameraDirY + fProjectionPlaneDirY * fProjectionPlaneOffset;

		float fHorRayDirX, fHorRayDirY;
		float fHorRayPosX, fHorRayPosY;

		float fVerRayDirX, fVerRayDirY;
		float fVerRayPosX, fVerRayPosY;

		char stepX, stepY;

		if (fRayDirX > 0) {
			//facing right
			stepX = 1;
			fVerRayDirX = 1;
			fVerRayPosX = (int(fCameraPosX + 1.5f)) - (fCameraPosX + 0.5f);
		} else {
			//facing left
			stepX = 0;
			fVerRayDirX = -1;
			fVerRayPosX = -((fCameraPosX - 0.5f) - (int(fCameraPosX - 0.5f)));
		}

		if (fRayDirY > 0) {
			//facing down
			stepY = 1;
			fHorRayDirY = 1;
			fHorRayPosY = ((int(fCameraPosY + 1.5f)) - (fCameraPosY + 0.5f));
		} else {
			//facing up
			stepY = 0;
			fHorRayDirY = -1;
			fHorRayPosY = -((fCameraPosY - 0.5f) - (int(fCameraPosY - 0.5f)));
		}

		fHorRayDirX = fRayDirX / abs(fRayDirY);
		fVerRayDirY = fRayDirY / abs(fRayDirX);

		//calculate start ray's positions
		fHorRayPosX = ((fRayDirX * fHorRayPosY) / fRayDirY) + fCameraPosX;
		fHorRayPosY += fCameraPosY;
		fVerRayPosY = ((fRayDirY * fVerRayPosX) / fRayDirX) + fCameraPosY;
		fVerRayPosX += fCameraPosX;

		//calculate start ray's distanes
		float fHorRayDist = sqrt(powf((fCameraPosX - fHorRayPosX), 2) + powf((fCameraPosY - fHorRayPosY), 2));
		float fVerRayDist = sqrt(powf((fCameraPosX - fVerRayPosX), 2) + powf((fCameraPosY - fVerRayPosY), 2));
		//ray's distanes to the next wall
		float fNextHorRayDist = sqrt(powf(fHorRayDirX, 2) + powf(fHorRayDirY, 2));
		float fNextVerRayDist = sqrt(powf(fVerRayDirX, 2) + powf(fVerRayDirY, 2));
		//distance to projection plane
		float fRayDist = sqrt(powf(fRayDirX, 2) + powf(fRayDirY, 2));

		float fRayLength;
		float fShade;

		do {
			if (fHorRayDist < fVerRayDist) {
				fRayPosX = roundf(fHorRayPosX);
				fRayPosY = fHorRayPosY + stepY;

				//next horizontal ray's vector
				fHorRayPosX += fHorRayDirX;
				fHorRayPosY += fHorRayDirY;

				fRayLength = fHorRayDist;
				fHorRayDist += fNextHorRayDist;
				
				fShade = 0.0f;
			} else {
				fRayPosX = fVerRayPosX + stepX;
				fRayPosY = roundf(fVerRayPosY);

				//next vertical ray's vector
				fVerRayPosX += fVerRayDirX;
				fVerRayPosY += fVerRayDirY;

				fRayLength = fVerRayDist;
				fVerRayDist += fNextVerRayDist;

				fShade = 0.3f;
			}
		} while (map[int(fRayPosY)][int(fRayPosX)] == 0);

		float fCollumnHight = (fRayDist * 1.0f) / fRayLength * projectionPlaneHigth;

		glBegin(GL_LINES);
			glColor3f(1.0f - fShade, 1.0f - fShade, 1.0f - fShade);
			glVertex2f((-projectionPlaneWidth / 2) + x, fCollumnHight / 2);
			glVertex2f((-projectionPlaneWidth / 2) + x, -fCollumnHight / 2);
		glEnd();
	}

	glFlush();
}

void Camera::collision() {
	if (collider) {
		int boxPosX = roundf(fCameraPosX);
		int boxPosY = roundf(fCameraPosY);

		int lastBoxPosX = roundf(fLastCameraPosX);
		int lastBoxPosY = roundf(fLastCameraPosY);

		if (map[boxPosY][lastBoxPosX] != 0){
			fCameraPosY = fLastCameraPosY;
		}
		if (map[lastBoxPosY][boxPosX] != 0){
			fCameraPosX = fLastCameraPosX;
		}
	}
}

void Camera::rotate(float angle) {
	float radAngle = angle * 3.14f / 180.0f;
	float fNewCameraDirX = (fCameraDirX * cosf(radAngle)) - (fCameraDirY * sinf(radAngle));
	float fNewCameraDirY = (fCameraDirX * sinf(radAngle)) + (fCameraDirY * cosf(radAngle));

	fCameraDirX = fNewCameraDirX;
	fCameraDirY = fNewCameraDirY;
}

void Camera::translate(float x, float y) {
	fLastCameraPosX = fCameraPosX;
	fLastCameraPosY = fCameraPosY;

	fCameraPosX += x * fCameraDirX;
	fCameraPosY += y * fCameraDirY;
}