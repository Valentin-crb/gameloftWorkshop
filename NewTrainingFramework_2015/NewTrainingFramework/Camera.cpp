#include "Camera.h"
#include <stdfax.h>

Camera camera;
Camera::Camera()
	: position(Vector3(0, 0, -1)),
	target(Vector3(0,0,0)),
	up(Vector3(0,1,0)),
	fov(45.0f),
	nearPlane(0.2),
	farPlane(10),
	moveSpeed(0.1),
	rotateSpeed(0.1)
{
	updateWorldView();
}

void Camera::updateWorldView() {

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
	forward = xAxis * sens;
	vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOz(int sens) {
	Vector3 forward;
	Vector3 vectorDeplasare;
	forward = xAxis * sens;
	vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::rotateOy(int sens) {
	Matrix mRotateOY;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOY;
	target = (rotatedTarget * worldMatrix).toVector3();
	updateWorldView();
}

void Camera::rotateOx(int sens) {
	Matrix mRotateOX;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	Vector4 localUp;
	Vector4 rotatedLocalUp = localUp * mRotateOX;
	up = (rotatedLocalUp * worldMatrix).toVector3();
	up = up.Normalize();
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