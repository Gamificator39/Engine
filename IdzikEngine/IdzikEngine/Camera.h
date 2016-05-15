#pragma once
#include "Physics.h" //Physics header
#include "Object.h" //Object header

class Camera:public Physics
{
public:
	Camera(); //Constructor
	~Camera(); //Destructor

	mat4 lookAtMatrix; //What the camera should look at
	mat4 perspectiveMatrix; //Perspective matrix
	mat4 cameraMatrix; //Camera matrix
	float fovy; //Field of view Y
	float aspectRatio; //Aspect ratio
	float zNear; //Near clipping plane
	float zFar; //Far clipping plane

	void update(Object &focusObject); //Update the camera
};