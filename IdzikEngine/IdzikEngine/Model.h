#pragma once
#include <GL/glew.h> //GLEW
#include <GLFW/glfw3.h> //GLFW
#include <glm/glm.hpp> //GLM
#include <glm/gtx/transform.hpp> //Transform
#include <glm/gtx/euler_angles.hpp> //Euler angles
#include <FreeImage.h> //FreeImage
#include <vector> //Vectors
#include <string> //Strings
#include <fstream> //File IO
#include <sstream> //String streams

using std::vector; //Vectors
using std::string; //Strings
using std::ifstream; //File input
using std::istringstream; //Input string stream
using glm::vec2; //2D vectors
using glm::vec3; //3D vectors

#include <iostream> //IO
using std::cout; //Output
using std::endl; //Endlines

struct Vertex //Vertex data
{
	vec3 locationData; //Location data
	vec2 uvData; //UV data
	vec3 normalData; //Normal data
};

struct VertexIndex //Vertex index data
{
	unsigned int locationIndex; //Location index data
	unsigned int uvIndex; //UV index data
	unsigned int normalIndex; //Normal index data
};


class Model
{
public:
	Model(); //Constructor
	~Model(); //Destructor

	bool buffer(); //Buffer models
	void render(); //Render models

	string objFileName; //Model file name
private:
	GLuint vertexArray; //Vertex array object
	unsigned int vertexCount; //Keep track of the number of connections
};

