#include "ShaderManager.h" //ShaderManager header

ShaderManager::ShaderManager() //Constructor
{
	program = 0; //Set program to 0
}

ShaderManager::~ShaderManager() //Destructor
{
}

GLuint ShaderManager::getProgram() const //Accessor for program
{
	return program; //Return program
}

bool ShaderManager::loadShaders(const char * vertexFile, const char * fragmentFile) //Access shaders
{
	#pragma region Load Vertex and Fragment Shaders
	GLuint vertexShader = loadShader(vertexFile, GL_VERTEX_SHADER); //Load the vertex shader file
	if (vertexShader == 0) //If there was an error
	{
		return 0; //Return 0
	}

	GLuint fragmentShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER); //Load the fragment shader file
	if (fragmentShader == 0) //If there was an error
	{
		return 0; //Return 0
	}
	#pragma endregion

	#pragma region Link Shaders
	program = glCreateProgram(); //Create and save a linked shader program
	glAttachShader(program, vertexShader); //Attach the vertex shader
	glAttachShader(program, fragmentShader); //Attach the fragment shader
	glLinkProgram(program); //Link the shaders
	#pragma endregion

	#pragma region Check Linking
	GLint result = 0; //Stores the result of the shader compilation
	glGetProgramiv(program, GL_LINK_STATUS, &result); //Check that the shader has linked, store the result

	if (result == 0) //If the program did not link
	{
		GLint logLength = 0; //Length of the log
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength); //Get the length of the log, store the result

		GLchar *logContents = new GLchar[logLength]; //Array to hold the log contents
		glGetProgramInfoLog(program, logLength, 0, logContents); //Get the log contents
		cout << logContents << endl; //Print the log contents
		glDeleteProgram(program); //Delete the program
		delete[] logContents; //Delete logContents from the heap

		return false; //Return
	}
	else //If the program linked correctly
	{
		return true; //Return
	}
	#pragma endregion
}

GLuint ShaderManager::loadShader(const char * file, GLenum shaderType) //Used by loadShaders to read and compile a shader file and return the index where it is stored
{
	#pragma region Binary File Input
	ifstream inFileBinary(file, ios::binary); //Create a binary input object
	char *fileContents; //Array to store file data on the heap

	if (inFileBinary.is_open()) //If the file is open
	{
		inFileBinary.seekg(0, ios::end); //Seek to find the end of the file
		unsigned int length = (unsigned int)inFileBinary.tellg(); //Save the length of the file
		inFileBinary.seekg(0, ios::beg); //Seek back to the beginning of the file

		fileContents = new char[length + 1]; //Create an array on the heap to store the file contents

		inFileBinary.read(fileContents, length); //Read in the file
		fileContents[length] = '\0'; //Add a null charactrer to the end of the array

		inFileBinary.close(); //Close the file
	}
	else
	{
		cout << "There was a problem opening the file" << endl; //Error message
		return 0; //Return
	}
	#pragma endregion

	#pragma region Compile Shader
	GLuint shaderIndex = glCreateShader(shaderType); //Index of the shader object

	glShaderSource(shaderIndex, 1, &fileContents, 0); //Set the source code
	glCompileShader(shaderIndex); //Compile the shader based on the shader object index

	delete[] fileContents; //Delete fileContents from the heap

	GLint result = 0; //Stores the result of the shader compilation
	glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, &result); //Check that the shader has compiled, store the result

	if (result == 0) //If the compilation was unsuccessful
	{
		GLint logLength = 0; //Length of the log
		glGetShaderiv(shaderIndex, GL_INFO_LOG_LENGTH, &logLength); //Get the length of the log, store the result

		GLchar *logContents = new GLchar[logLength]; //Array to hold the log contents
		glGetShaderInfoLog(shaderIndex, logLength, 0, logContents); //Get the log contents
		cout << logContents << endl; //Print the log contents
		glDeleteShader(shaderIndex); //Delete the shader
		delete[] logContents; //Delete logContents from the heap

		return 0; //Return
	}
	else //If the compilation was successful
	{
		return shaderIndex; //Return the shader index
	}

	return GLuint(); //Return
	#pragma endregion
}