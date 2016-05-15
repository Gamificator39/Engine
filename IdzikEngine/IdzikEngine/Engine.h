#pragma once
#include "ShaderManager.h" //ShaderManager header
#include "Object.h" //Object header
#include "Camera.h" //Camera header
#include "Model.h" //Model header
#include <GL/glew.h> //GLEW
#include <GLFW/glfw3.h> //GLFW
#include <glm/glm.hpp> //GLM
#include <glm/gtx/transform.hpp> //Transform
#include <glm/gtx/euler_angles.hpp> //Euler angles
#include <FreeImage.h> //FreeImage
#include <vector> //Vectors
#include <map> //Map

using std::vector; //Vectors
using std::map; //Map
using std::pair; //Pair
using std::string; //String
using glm::vec2; //2D vectors
using glm::vec3; //3D vectors
using glm::mat4; //4x4 matrix
using glm::translate; //Translation
using glm::scale; //Scaling
using glm::yawPitchRoll; //Yaw, pitch, and roll

class Engine //Engine class
{
public:
	Engine(); //Constructor
	~Engine(); //Destructor

	bool initialize(); //Initialize the engine
	bool bufferModels(); //Loads and buffers a model
	bool gameLoop(); //Game loop
	bool useShaders(); //Shaders

private:
	ShaderManager shader = ShaderManager(); //Shader object
	Camera cam = Camera(); //Camera object
	Model modl = Model(); //Model object

	GLFWwindow *GLFWwindowPointer; //Creates a window, returns the address of the GLFWwindow struct, returns nullptr if it fails to create the window
	map<char*, unsigned int> textureData; //Texture data
	vector<Object> objects; //A vector containing object data
	vector<string> modelFileNames; //A vector containing the model file names
	float previousTime; //Time in the previous frame
	float currentTime; //Time in the current frame
	float deltaTime; //Change in time
};