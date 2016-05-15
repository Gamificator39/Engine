#pragma once
#include <GL/glew.h> //GLEW
#include <GLFW/glfw3.h> //GLFW
#include <glm/glm.hpp> //GLM
#include <glm/gtx/transform.hpp> //Transform
#include <glm/gtx/euler_angles.hpp> //Euler angles
#include <FreeImage.h> //FreeImage
#include <vector> //Vectors

using glm::vec3; //3D vectors
using glm::mat3; //3x3 matrix
using glm::mat4; //4x4 matrix
using glm::yawPitchRoll; //Yaw, pitch, and roll
using glm::lookAt; //Focus of the camera
using glm::perspective; //Perspective

struct Transform //Transform data
{
	vec3 transformLocation; //Location
	vec3 transformRotation; //Rotation
	vec3 transformSize; //Size
	mat4 transformMatrix; //Object world transform matrix
};

struct Rigidbody //Rigidbody data
{
	float mass; //Mass
	vec3 velocity; //Velocity
	vec3 force; //Force
};

class Physics
{
public:
	Physics(); //Constructor
	virtual ~Physics(); //Destructor

	Transform transformObject; //Transformation data
	Rigidbody rigidbodyObject; //Rigidbody data

	void calculateForces(vec3 incomingForce, float incomingDeltaTime); //Calculate the forces on the object
	void move(float incomingDeltaTime); //Move the object
	void friction(float incomingDeltaTime); //Friction
};