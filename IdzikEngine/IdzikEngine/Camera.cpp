#include "Camera.h" //Camera header

Camera::Camera() //Constructor
{
	#pragma region Struct Data
	transformObject.transformLocation = { 0, -2, 1 }; //Set the camera location
	transformObject.transformRotation = { 0, 0, 0 }; //Set the camera rotation

	rigidbodyObject.mass = 1; //Set the camera mass
	rigidbodyObject.velocity = { 0, 0, 0 }; //Set the camera velocity
	rigidbodyObject.force = { .5, .5, .5 }; //Set the camera force
	#pragma endregion

	#pragma region Movement and Rotation
	mat3 rotationMatrix = (mat3)yawPitchRoll(transformObject.transformRotation.y, transformObject.transformRotation.x, transformObject.transformRotation.z); //Calculate the rotation matrix

	vec3 center = transformObject.transformLocation + rotationMatrix * vec3(0, 0, -1); //Calculate the center of the camera
	vec3 up = rotationMatrix * vec3(0, 1, 0); //Calculate the camera's up vector

	lookAtMatrix = lookAt(transformObject.transformLocation, center, up); //Calculate what the camera should look at (cameraLocation is eye)
	#pragma endregion

	#pragma region Zoom and Aspect Ratio
	float zoom = 1.f; //Zoom
	int width = 600; //Window width
	int height = 600; //Window height

	fovy = 3.14159f * .3f / zoom; //Calculate the field of view in the Y direction
	aspectRatio = (float)width / (float)height; //Calculate the aspect ratio
	zNear = .01f; //Calculate the near clipping plane
	zFar = 1000.f; //Calculate the far clipping plane

	perspectiveMatrix = perspective(fovy, aspectRatio, zNear, zFar); //Calculate the perspective matrix
	#pragma endregion
}

Camera::~Camera() //Destructor
{
}

void Camera::update(Object &focusObject) //Update the camera
{
	#pragma region Movement and Rotation
	mat3 rotationMatrix = (mat3)yawPitchRoll(transformObject.transformRotation.y, transformObject.transformRotation.x, transformObject.transformRotation.z); //Calculate the rotation matrix

	vec3 up = rotationMatrix * vec3(0, 1, 0); //Calculate the camera's up vector

	lookAtMatrix = lookAt(transformObject.transformLocation, focusObject.transformObject.transformLocation, up); //Calculate what the camera should look at (cameraLocation is eye)
	#pragma endregion

	#pragma region Zoom and Aspect Ratio
	float zoom = 1.f; //Zoom
	int width = 600; //Window width
	int height = 600; //Window height

	fovy = 3.14159f * .3f / zoom; //Calculate the field of view in the Y direction
	aspectRatio = (float)width / (float)height; //Calculate the aspect ratio
	zNear = .01f; //Calculate the near clipping plane
	zFar = 1000.f; //Calculate the far clipping plane

	perspectiveMatrix = perspective(fovy, aspectRatio, zNear, zFar); //Calculate the perspective matrix
	#pragma endregion

	//vec3 distance = vec3(transformObject.transformLocation.x - focusObject.transformObject.transformLocation.x, transformObject.transformLocation.y - focusObject.transformObject.transformLocation.y, transformObject.transformLocation.z - focusObject.transformObject.transformLocation.z); //Difference in location between the camera and focus object

	cameraMatrix = perspectiveMatrix * lookAtMatrix; //Calculate the camera matrix
	glUniformMatrix4fv(4, 1, GL_FALSE, &cameraMatrix[0][0]); //Upload the matrices to the graphics card
}