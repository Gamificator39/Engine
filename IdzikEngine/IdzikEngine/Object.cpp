#include "Object.h" //Object header

Object::Object() //Constructor
{
}

Object::~Object() //Deconstructor
{
}

bool Object::collidesWith(const Object & thatObject) //Check for collisions
{
	#pragma region Colliderless
	if (colliderObject == COLLIDERLESS || thatObject.colliderObject == COLLIDERLESS) //If both objects are COLLIDERLESS
	{
		return false; //Return false
	}
	#pragma endregion

	#pragma region Sphere
	if (colliderObject == SPHERE && thatObject.colliderObject == SPHERE) //If both objects are SPHERE
	{
		vec3 distance = transformObject.transformLocation - thatObject.transformObject.transformLocation; //Get the distance between the objects
		float magnitude = sqrt(pow(distance.x, 2) + pow(distance.y, 2) + pow(distance.z, 2)); //Calculate the magnitude between the objects
		float combinedRadii = transformObject.transformSize.x + thatObject.transformObject.transformSize.x; //Get the combined radii of the two objects
		
		if (magnitude > combinedRadii) //If the magnitude is greater than the combined radii of the objects
		{
			return false; //Return false
		}
	}
	#pragma endregion

	#pragma region AABB
	if (colliderObject == AABB && thatObject.colliderObject == AABB) //If both objects are AABB
	{
		if ((transformObject.transformLocation.x + transformObject.transformSize.x) > (thatObject.transformObject.transformLocation.x - thatObject.transformObject.transformSize.x)) //If the right side of box A collides with the left side of box B
		{
			return false; //Return false
		}
		if ((transformObject.transformLocation.x - transformObject.transformSize.x) < (thatObject.transformObject.transformLocation.x + thatObject.transformObject.transformSize.x)) //If the left side of box A collides with the right side of box B
		{
			return false; //Return false
		}

		if ((transformObject.transformLocation.y + transformObject.transformSize.y) > (thatObject.transformObject.transformLocation.y - thatObject.transformObject.transformSize.y)) //If the top side of box A collides with the bottom side of box B
		{
			return false; //Return false
		}
		if ((transformObject.transformLocation.y - transformObject.transformSize.y) < (thatObject.transformObject.transformLocation.y + thatObject.transformObject.transformSize.y)) //If the bottom side of box A collides with the top side of box B
		{
			return false; //Return false
		}

		if ((transformObject.transformLocation.z + transformObject.transformSize.z) > (thatObject.transformObject.transformLocation.z - thatObject.transformObject.transformSize.z)) //If the front side of box A collides with the back side of box B
		{
			return false; //Return false
		}
		if ((transformObject.transformLocation.z - transformObject.transformSize.z) < (thatObject.transformObject.transformLocation.z + thatObject.transformObject.transformSize.z)) //If the back side of box A collides with the front side of box B
		{
			return false; //Return false
		}
	}
	#pragma endregion

	#pragma region AABB and Sphere
	if (colliderObject == AABB && thatObject.colliderObject == SPHERE) //If one object is AABB and the other is SPHERE
	{
		float distanceSquared = 0; //Set the distance squared to 0

		if ((thatObject.transformObject.transformLocation.x - thatObject.transformObject.transformSize.x) > (transformObject.transformLocation.x + transformObject.transformSize.x)) //If the sphere collides from the right of the box
		{
			distanceSquared += pow(thatObject.transformObject.transformLocation.x - (transformObject.transformLocation.x + transformObject.transformSize.x), 2); //Add to the distance squared
		}
		if ((thatObject.transformObject.transformLocation.x + thatObject.transformObject.transformSize.x) < (transformObject.transformLocation.x - transformObject.transformSize.x)) //If the sphere collides from the left of the box
		{
			distanceSquared += pow((transformObject.transformLocation.x + transformObject.transformSize.x) - thatObject.transformObject.transformLocation.x, 2); //Add to the distance squared
		}

		if ((thatObject.transformObject.transformLocation.y - thatObject.transformObject.transformSize.y) > (transformObject.transformLocation.y + transformObject.transformSize.y)) //If the sphere collides from the top of the box
		{
			distanceSquared += pow(thatObject.transformObject.transformLocation.y - (transformObject.transformLocation.y + transformObject.transformSize.y), 2); //Add to the distance squared
		}
		if ((thatObject.transformObject.transformLocation.y + thatObject.transformObject.transformSize.y) < (transformObject.transformLocation.y - transformObject.transformSize.y)) //If the sphere collides from the bottom of the box
		{
			distanceSquared += pow((transformObject.transformLocation.y + transformObject.transformSize.y) - thatObject.transformObject.transformLocation.y, 2); //Add to the distance squared
		}

		if ((thatObject.transformObject.transformLocation.z - thatObject.transformObject.transformSize.z) > (transformObject.transformLocation.z + transformObject.transformSize.z)) //If the sphere collides from the front of the box
		{
			distanceSquared += pow(thatObject.transformObject.transformLocation.z - (transformObject.transformLocation.z + transformObject.transformSize.z), 2); //Add to the distance squared
		}
		if ((thatObject.transformObject.transformLocation.z + thatObject.transformObject.transformSize.z) < (transformObject.transformLocation.z - transformObject.transformSize.z)) //If the sphere collides from the back of the box
		{
			distanceSquared += pow((transformObject.transformLocation.z + transformObject.transformSize.z) - thatObject.transformObject.transformLocation.z, 2); //Add to the distance squared
		}

		if (distanceSquared > (thatObject.transformObject.transformSize.x * thatObject.transformObject.transformSize.x)) //If the distance squared is greater than the sphere's radius squared
		{
			return false; //Return false
		}
	}

	if (colliderObject == SPHERE && thatObject.colliderObject == AABB) //If one object is SPHERE and the other is AABB
	{
		float distanceSquared = 0; //Set the distance squared to 0

		if ((transformObject.transformLocation.x - transformObject.transformSize.x) > (thatObject.transformObject.transformLocation.x + thatObject.transformObject.transformSize.x)) //If the sphere collides from the right of the box
		{
			distanceSquared += pow(transformObject.transformLocation.x - (thatObject.transformObject.transformLocation.x + thatObject.transformObject.transformSize.x), 2); //Add to the distance squared
		}
		if ((transformObject.transformLocation.x + transformObject.transformSize.x) < (thatObject.transformObject.transformLocation.x - thatObject.transformObject.transformSize.x)) //If the sphere collides from the left of the box
		{
			distanceSquared += pow((thatObject.transformObject.transformLocation.x + thatObject.transformObject.transformSize.x) - transformObject.transformLocation.x, 2); //Add to the distance squared
		}

		if ((transformObject.transformLocation.y - transformObject.transformSize.y) > (thatObject.transformObject.transformLocation.y + thatObject.transformObject.transformSize.y)) //If the sphere collides from the top of the box
		{
			distanceSquared += pow(transformObject.transformLocation.y - (thatObject.transformObject.transformLocation.y + thatObject.transformObject.transformSize.y), 2); //Add to the distance squared
		}
		if ((transformObject.transformLocation.y + transformObject.transformSize.y) < (thatObject.transformObject.transformLocation.y - thatObject.transformObject.transformSize.y)) //If the sphere collides from the bottom of the box
		{
			distanceSquared += pow((thatObject.transformObject.transformLocation.y + thatObject.transformObject.transformSize.y) - transformObject.transformLocation.y, 2); //Add to the distance squared
		}

		if ((transformObject.transformLocation.z - transformObject.transformSize.z) > (thatObject.transformObject.transformLocation.z + thatObject.transformObject.transformSize.z)) //If the sphere collides from the front of the box
		{
			distanceSquared += pow(transformObject.transformLocation.z - (thatObject.transformObject.transformLocation.z + thatObject.transformObject.transformSize.z), 2); //Add to the distance squared
		}
		if ((transformObject.transformLocation.z + transformObject.transformSize.z) < (thatObject.transformObject.transformLocation.z - thatObject.transformObject.transformSize.z)) //If the sphere collides from the back of the box
		{
			distanceSquared += pow((thatObject.transformObject.transformLocation.z + thatObject.transformObject.transformSize.z) - transformObject.transformLocation.z, 2); //Add to the distance squared
		}

		if (distanceSquared > (transformObject.transformSize.x * transformObject.transformSize.x)) //If the distance squared is greater than the sphere's radius squared
		{
			return false; //Return false
		}
	}
	#pragma endregion

	return true; //Return true
}

void Object::resolveCollision(Object & thatObject) //Collision resolution
{
	float sumMagnitude = transformObject.transformSize.x + thatObject.transformObject.transformSize.x; //Get the sum of the magnitudes of both objects
	vec3 distance = vec3(transformObject.transformLocation.x - thatObject.transformObject.transformLocation.x, transformObject.transformLocation.y - thatObject.transformObject.transformLocation.y, transformObject.transformLocation.z - thatObject.transformObject.transformLocation.z); //Difference in location between the two objects
	vec3 unitVector = (distance / sumMagnitude); //Unit vector

	rigidbodyObject.velocity += unitVector * ((rigidbodyObject.mass - thatObject.rigidbodyObject.mass) / (rigidbodyObject.mass * thatObject.rigidbodyObject.mass)); //Add the unit vector to the velocity of thisObject
	thatObject.rigidbodyObject.velocity -= unitVector * ((2 * rigidbodyObject.mass) / (rigidbodyObject.mass * thatObject.rigidbodyObject.mass)); //Add the unit vector to the velocity of thatObject
}