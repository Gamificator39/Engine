#pragma once
#include "Physics.h" //Physics header
#include "Model.h" //Model header
#include <string> //Strings

using std::string; //Strings

enum Colliders //Colliders
{
	COLLIDERLESS,
	AABB,
	SPHERE
};

class Object:public Physics
{
public:
	Object(); //Constructor
	~Object(); //Deconstructor

	char *textureFilename; //Texture filename
	Colliders colliderObject; //Collider data
	Model objModel = Model(); //Model object

	bool collidesWith(const Object &thatObject); //Check for collisions
	void resolveCollision(Object &thatObject); //Collision resolution
};