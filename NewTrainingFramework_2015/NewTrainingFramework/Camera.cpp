#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
#include "Math.h"

#define PI 3.14

Camera camera;
Camera::Camera()
	: position(Vector3(0, 0, -1)),
	target(Vector3(0,0,0)),
	up(Vector3(0,1,0)),
	fov(PI/4),
	nearPlane(0.2f),
	farPlane(10.0f),
	moveSpeed(1.5f),
	rotateSpeed(1.0f)
{
	updateWorldView();
	GLfloat aspectRatio = (GLfloat)Globals::screenWidth / Globals::screenHeight;
	perspectiveMatrix.SetPerspective(fov, aspectRatio, nearPlane, farPlane);
}

void Camera::updateWorldView() {
	updateAxes();
	Matrix T; T.SetTranslation(position);
	Matrix R; R.SetZero();
	Matrix Rt; 
	Matrix Tinv; Tinv.SetTranslation(-position);
	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z;
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z;
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z;
	R.m[3][3] = 1.0f;
	worldMatrix = R * T;
	Rt = R.Transpose();
	viewMatrix =  Tinv*Rt;
}

void Camera::updateAxes() {
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
}

void Camera::moveOx(int sens) {
	Vector3 forward;
	Vector3 vectorDeplasare;
	forward = xAxis * sens;
	vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOy(int sens) {
	Vector3 forward;
	Vector3 vectorDeplasare;
	forward = yAxis * sens;
	vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOz(int sens) {
	Vector3 forward;
	Vector3 vectorDeplasare;
	forward = zAxis * sens;
	vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::rotateOx(int sens) {
	Matrix mRotateOX;
	mRotateOX.SetRotationX(rotateSpeed * deltaTime * sens);
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	Vector4 localUp(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedLocalUp = localUp * mRotateOX;
	up = (rotatedLocalUp * worldMatrix).toVector3();
	up = up.Normalize();
	target = (rotatedTarget * worldMatrix).toVector3();
	updateWorldView();
}

void Camera::rotateOy(int sens) {
	Matrix mRotateOY;
	mRotateOY.SetRotationY(rotateSpeed * deltaTime * sens);
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOY;
	target = (rotatedTarget * worldMatrix).toVector3();
	updateWorldView();
}

void Camera::rotateOz(int sens) {
	Matrix mRotateOZ;
	mRotateOZ.SetRotationZ(rotateSpeed* deltaTime* sens);
	Vector4 localUp = Vector4(up, 0.0f);
	Vector4 rotatedLocalUp = localUp * mRotateOZ;
	up = rotatedLocalUp.toVector3().Normalize();
	updateWorldView();
}
void Camera::setDeltaTime(GLfloat dt) {
	deltaTime = dt;
}