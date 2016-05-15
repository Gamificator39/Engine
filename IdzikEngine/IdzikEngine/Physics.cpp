#include "Physics.h" //Physics header

Physics::Physics() //Constructor
{
}

Physics::~Physics() //Destructor
{
}

void Physics::calculateForces(vec3 incomingForce, float incomingDeltaTime) //Calculate the forces on the object
{
	rigidbodyObject.force = incomingForce; //Save the force to the object

	vec3 acceleration = rigidbodyObject.force / rigidbodyObject.mass; //Calculate acceleration

	vec3 deltaVelocity = acceleration * incomingDeltaTime; //Calculate the change in velocity

	rigidbodyObject.velocity += deltaVelocity; //Update the object's velocity

	if (rigidbodyObject.velocity.x > 5) //If the ball is going too fast
	{
		rigidbodyObject.velocity.x = 5; //Stop it
	}
	else if (rigidbodyObject.velocity.x < -5) //If the ball is going too fast
	{
		rigidbodyObject.velocity.x = -5; //Stop it
	}

	if (rigidbodyObject.velocity.y > 5) //If the ball is going too fast
	{
		rigidbodyObject.velocity.y = 5; //Stop it
	}
	else if (rigidbodyObject.velocity.y < -5) //If the ball is going too fast
	{
		rigidbodyObject.velocity.y = -5; //Stop it
	}

	if (rigidbodyObject.velocity.z > 5) //If the ball is going too fast
	{
		rigidbodyObject.velocity.z = 5; //Stop it
	}
	else if (rigidbodyObject.velocity.z < -5) //If the ball is going too fast
	{
		rigidbodyObject.velocity.z = -5; //Stop it
	}
}

void Physics::move(float incomingDeltaTime) //Move the object
{
	vec3 deltaLocation = rigidbodyObject.velocity * incomingDeltaTime; //Calculate the change in location

	transformObject.transformLocation += deltaLocation; //Update the position of the object
}

void Physics::friction(float incomingDeltaTime) //Friction
{
	if (rigidbodyObject.velocity.y != 0) //Y direction friction
	{
		calculateForces(vec3(0, -rigidbodyObject.velocity.y * 10, 0), incomingDeltaTime); //Calculate the forces on the object
	}
	if (rigidbodyObject.velocity.x != 0) //X direction friction
	{
		calculateForces(vec3(-rigidbodyObject.velocity.x * 10, 0, 0), incomingDeltaTime); //Calculate the forces on the object
	}
	if (rigidbodyObject.velocity.z != 0) //Z direction friction
	{
		calculateForces(vec3(0, 0, -rigidbodyObject.velocity.z * 10), incomingDeltaTime); //Calculate the forces on the object
	}

	if (abs(rigidbodyObject.force.y) <= .01) //Y direction stopping
	{
		rigidbodyObject.force.y = 0; //Stop the object
	}
	if (abs(rigidbodyObject.force.x) <= .01) //X direction stopping
	{
		rigidbodyObject.force.x = 0; //Stop the object
	}
	if (abs(rigidbodyObject.force.z) <= .01) //Z direction stopping
	{
		rigidbodyObject.force.z = 0; //Stop the object
	}
}