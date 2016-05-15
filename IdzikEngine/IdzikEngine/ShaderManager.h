#pragma once
#include <GL/glew.h> //GLEW
#include <GLFW/glfw3.h> //GLFW
#include <glm/glm.hpp> //GLM
#include <glm/gtx/transform.hpp> //GLM
#include <FreeImage.h> //FreeImage
#include <fstream> //File IO
#include <iostream> //IO

using std::ifstream; //File input
using std::ios; //Binary IO
using std::cout; //Output
using std::endl; //Endlines

class ShaderManager
{
public:
	ShaderManager(); //Constructor
	~ShaderManager(); //Destructor

	GLuint getProgram() const; //Accessor for program

	bool loadShaders(const char* vertexFile, const char* fragmentFile); //Access shaders

private:
	GLuint program; //Index of the loaded shaders on the graphics card

	GLuint loadShader(const char* file, GLenum shaderType); //Used by loadShaders to read and compile a shader file and return the index where it is stored
};