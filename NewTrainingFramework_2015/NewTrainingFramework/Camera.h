#pragma once
#include "../Utilities/utilities.h"

#define PI 3.14

class Camera
{
public:
//proprietati
	Vector3 position;
	Vector3 target;
	Vector3 up;
	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat nearPlane;
	GLfloat farPlane;
	GLfloat fov;
	GLfloat deltaTime;
	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;
	Matrix viewMatrix;
	Matrix worldMatrix;
	Matrix perspectiveMatrix;

//Metode
	void moveOx(int sens);
	void moveOy(int sens);
	void moveOz(int sens);
	void rotateOx(int sens);
	void rotateOy(int sens);
	void rotateOz(int sens);
	void updateAxes();
	void updateWorldView();
	void setDeltaTime();

//constructori
	Camera();
	Camera(Vector3 position, Vector3 target, Vector3 up, GLfloat moveSpeed, GLfloat rotateSpeed, GLfloat nearPlane, GLfloat farPlane, GLfloat fov);
};
extern Camera camera;