#include "Engine.h" //Engine header

namespace //Input namespace
{
	#pragma region Input Management
	map<int, int> keyIsDown; //When the key is down
	map<int, int> keyWasDown; //When the key was down

	void input(GLFWwindow * GLFWwindowPointer, int key, int scancode, int action, int mods) //Keyboard input
	{
		keyIsDown[key] = action; //Map the key to an action
	}

	void input(GLFWwindow * GLFWwindowPointer, int button, int action, int mods) //Mouse input
	{
		keyIsDown[button] = action; //Map the key to an action
	}
	#pragma endregion
}

Engine::Engine() //Constructor
{
}

Engine::~Engine() //Destructor
{
}

bool Engine::initialize() //Initialize the engine
{
	#pragma region GLFW
	if (glfwInit() == GL_FALSE) //Initialize GLFW, GL_TRUE is 1, GL_FALSE is 0
	{
		return false; //Return
	}

	GLFWwindowPointer = glfwCreateWindow(600, 600, "Kevin Idzik's DSA1 Engine", NULL, NULL); //Creates a window, returns the address of the GLFWwindow struct, returns nullptr if it fails to create the window

	if (GLFWwindowPointer != nullptr) //If the window initialized
	{
		glfwMakeContextCurrent(GLFWwindowPointer); //Focus on this window
	}
	else //If the window is not initialized
	{
		glfwTerminate(); //Terminate GLFW
		return false; //Return
	}

	glfwSetKeyCallback(GLFWwindowPointer, input); //Set the keyboard function
	glfwSetMouseButtonCallback(GLFWwindowPointer, input); //Set the mouse function
	#pragma endregion

	#pragma region GLEW
	if (glewInit() != GLEW_OK) //Initialize GLEW or quit
	{
		glfwTerminate(); //Terminate GLFW
		return false; //Return
	}
	#pragma endregion

	#pragma region Transparency, Backface Culling and Hidden Cursor
	glEnable(GL_BLEND); //Blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Transparency

	glEnable(GL_DEPTH_TEST); //Enable depth test to correct object positioning
	glEnable(GL_CULL_FACE); //Enable backface culling

	glfwSetInputMode(GLFWwindowPointer, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); //Hide the cursor
	#pragma endregion

	#pragma region Create Objects
	for (int i = 0; i < 12; i++) //For each item in the texture file map
	{
		objects.push_back(Object()); //Add an object to the vector
	}

	objects[11].textureFilename = "Textures/wood.png"; //Assign a texture filename for the first object
	objects[0].objModel.objFileName = "models/quad.obj"; //Assign a model filename for the first object
	objects[0].transformObject.transformLocation = vec3(0, 0, -.1); //Assign a location to the first object
	objects[0].transformObject.transformRotation = vec3(0, 0, 0); //Assign a rotation to the first object
	objects[0].transformObject.transformSize = vec3(5, 5, 1); //Assign a size to the first object
	objects[0].rigidbodyObject.mass = 0; //Assign a force value to the first object
	objects[0].rigidbodyObject.velocity = vec3(0, 0, 0); //Assign a velocity value to the first object
	objects[0].rigidbodyObject.force = vec3(0, 0, 0); //Assign a force value to the first object
	objects[0].colliderObject = COLLIDERLESS; //Assign a collider type to the first object

	objects[0].textureFilename = "Textures/bowlingBall.png"; //Assign a texture filename for the second object
	objects[1].objModel.objFileName = "models/sphere.obj"; //Assign a model filename for the second object
	objects[1].transformObject.transformLocation = vec3(0, -.7, 0); //Assign a location to the second object
	objects[1].transformObject.transformRotation = vec3(0, 0, 0); //Assign a rotation to the second object
	objects[1].transformObject.transformSize = vec3(.1, .1, .1); //Assign a size to the second object
	objects[1].rigidbodyObject.mass = 10; //Assign a force value to the second object
	objects[1].rigidbodyObject.velocity = vec3(0, 0, 0); //Assign a velocity value to the second object
	objects[1].rigidbodyObject.force = vec3(0, 0, 0); //Assign a force value to the second object
	objects[1].colliderObject = SPHERE; //Assign a collider type to the second object

	for (unsigned int i = 2; i < objects.size(); i++) //Loop to quickly assign similar attributes
	{
		objects[i - 1].textureFilename = "Textures/pin.png"; //Assign a texture filename for the object
		objects[i].objModel.objFileName = "models/sphere.obj"; //Assign a model filename for the object
		objects[i].transformObject.transformRotation = vec3(0, 0, 0); //Assign a rotation to the object
		objects[i].transformObject.transformSize = vec3(.1, .1, .1); //Assign a size to the object
		objects[i].rigidbodyObject.mass = 3; //Assign a force value to the object
		objects[i].rigidbodyObject.velocity = vec3(0, 0, 0); //Assign a velocity value to the object
		objects[i].rigidbodyObject.force = vec3(0, 0, 0); //Assign a force value to the object
		objects[i].colliderObject = SPHERE; //Assign a collider type to the object
	}

	objects[2].transformObject.transformLocation = vec3(0, .5, 0); //Assign a location to the third object
	objects[3].transformObject.transformLocation = vec3(.15, .7, 0); //Assign a location to the fourth object
	objects[4].transformObject.transformLocation = vec3(-.15, .7, 0); //Assign a location to the fifth object
	objects[5].transformObject.transformLocation = vec3(0, .9, 0); //Assign a location to the sixth object
	objects[6].transformObject.transformLocation = vec3(.3, .9, 0); //Assign a location to the seventh object
	objects[7].transformObject.transformLocation = vec3(-.3, .9, 0); //Assign a location to the eighth object
	objects[8].transformObject.transformLocation = vec3(.15, 1.1, 0); //Assign a location to the ninth object
	objects[9].transformObject.transformLocation = vec3(-.15, 1.1, 0); //Assign a location to the tenth object
	objects[10].transformObject.transformLocation = vec3(.45, 1.1, 0); //Assign a location to the eleventh object
	objects[11].transformObject.transformLocation = vec3(-.45, 1.1, 0); //Assign a location to the twelfth object
	#pragma endregion

	#pragma region Prepare Model Vector
	modelFileNames.push_back("models/quad.obj"); //Add the quad to the vector
	modelFileNames.push_back("models/sphere.obj"); //Add the sphere to the vector
	#pragma endregion

	return true; //Return
}

bool Engine::bufferModels() //Loads and buffers a model
{
	for (unsigned int i = 0; i < modelFileNames.size(); i++) //For each object
	{
		modl.objFileName = modelFileNames[i]; //Assign the model's file name from the modelFileNames vector
		
		if (!modl.buffer()) //If the model does not buffer
		{
			cout << "The model " << modl.objFileName << " did not buffer correctly."; //Print out an error message
			return false; //Return false
		}
		else //If the model does buffer
		{
			for (unsigned int i = 0; i < objects.size(); i++) //For each object
			{
				if (objects[i].objModel.objFileName == modl.objFileName) //If the object's model has the same filename as the currently buffered model
				{
					objects[i].objModel = modl; //Set the object's model to the currently buffered model
				}
			}
		}
	}

	return true; //Return true
}

bool Engine::gameLoop() //Game loop
{
	#pragma region Load Textures
	textureData["Textures/wood.png"]; //Add the third file to the map
	textureData["Textures/bowlingBall.png"]; //Add the first file to the map
	textureData["Textures/pin.png"]; //Add the second file to the map

	for each (pair<char*, unsigned int> texData in textureData) //For each item in the texture file map
	{
		FIBITMAP *texture = FreeImage_Load(FreeImage_GetFileType(texData.first, 0), texData.first); //Load the texture
	
		if (texture == nullptr) //If the load failed
		{
			return false; //Close the window
		}
	
		FIBITMAP *texture32Bit = FreeImage_ConvertTo32Bits(texture); //Convert the texture to 32 bits
		FreeImage_Unload(texture); //Unload the original image from memory
	
		GLuint texID; //Initialize a temporary GLuint
		glGenTextures(1, &texID); //Generate a new texture
		glBindTexture(GL_TEXTURE_2D, texID); //Bind the new texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(texture32Bit), FreeImage_GetHeight(texture32Bit), 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(texture32Bit)); //Upload texture bytes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Set the minimum filter to linear instead of mipmap linear
	
		FreeImage_Unload(texture32Bit); //Unload the 32 bit texture from system RAM
		glBindTexture(GL_TEXTURE_2D, 0); //Unbind the texture when it is finished uploading
	
		textureData[texData.first] = texID; //Assign the temporary texture ID to texture map
	}
	#pragma endregion

	#pragma region Debug
	//for (unsigned int i = 0; i < objects.size(); i++) //For each number
	//{
	//	objects[i].transformObject.transformMatrix = translate(objects[i].transformObject.transformLocation) * yawPitchRoll(objects[i].transformObject.transformRotation.y, objects[i].transformObject.transformRotation.x, objects[i].transformObject.transformRotation.z) * scale(objects[i].transformObject.transformSize); //Vertex location in the world
	//	cout << "Matrix: " << objects[i].transformObject.transformMatrix[0][0] << " " << objects[i].transformObject.transformMatrix[0][1] << " " << objects[i].transformObject.transformMatrix[0][2] << " " << objects[i].transformObject.transformMatrix[0][3] << endl; //Matrix row one
	//	cout << "        " << objects[i].transformObject.transformMatrix[1][0] << " " << objects[i].transformObject.transformMatrix[1][1] << " " << objects[i].transformObject.transformMatrix[1][2] << " " << objects[i].transformObject.transformMatrix[1][3] << endl; //Matrix row two
	//	cout << "        " << objects[i].transformObject.transformMatrix[2][0] << " " << objects[i].transformObject.transformMatrix[2][1] << " " << objects[i].transformObject.transformMatrix[2][2] << " " << objects[i].transformObject.transformMatrix[2][3] << endl; //Matrix row three
	//	cout << "        " << objects[i].transformObject.transformMatrix[3][0] << " " << objects[i].transformObject.transformMatrix[3][1] << " " << objects[i].transformObject.transformMatrix[3][2] << " " << objects[i].transformObject.transformMatrix[3][3] << endl; //Matrix row four
	//	cout << "Texture Number: " << textureData[objects[i].textureFilename] << endl; //Texture number
	//	cout << "Texture Name: " << objects[i].textureFilename << endl << endl; //Texture name
	//}
	#pragma endregion

	#pragma region Game Loop
	while (!glfwWindowShouldClose(GLFWwindowPointer)) //Loop until the user closes the window
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the canvas and enable backface culling

		previousTime = currentTime; //Calculate the time in the previous frame
		currentTime = (float)glfwGetTime(); //Get the current time
		deltaTime = currentTime - previousTime; //Calculate the change in time

		for (unsigned int i = 0; i < objects.size(); i++) //Loop to create matrices, bind textures and upload them
		{
			objects[i].transformObject.transformMatrix = translate(objects[i].transformObject.transformLocation) * yawPitchRoll(objects[i].transformObject.transformRotation.y, objects[i].transformObject.transformRotation.x, objects[i].transformObject.transformRotation.z) * scale(objects[i].transformObject.transformSize); //Vertex location in the world
			glUniformMatrix4fv(3, 1, GL_FALSE, &objects[i].transformObject.transformMatrix[0][0]); //Upload the matrices to the graphics card
			objects[i].objModel.render(); //Render the model
			glBindTexture(GL_TEXTURE_2D, textureData[objects[i].textureFilename]); //Bind the texture
			glBindVertexArray(0); //Unbind
		}

		#pragma region Lighting
		vec3 lightLocation = vec3(2, 0, 7); //Light location to pass into the shader
		glUniform3f(5, lightLocation.x, lightLocation.y, lightLocation.z); //Pass the light location to the shader
		glUniform3f(6, cam.transformObject.transformLocation.x, cam.transformObject.transformLocation.y, cam.transformObject.transformLocation.z); //Pass the camera location to the shader
		#pragma endregion

		glfwSwapBuffers(GLFWwindowPointer); //Swap the front and back buffers (Front is screen, back is OpenGL)

		keyWasDown = keyIsDown; //Set keyWasDown equal to keyIsDown
		glfwPollEvents(); //Process queued window, mouse, and keyboard callback events

		#pragma region Keyboard Input
		if (keyIsDown[GLFW_KEY_ESCAPE]) //If the escape key has been pressed
		{
			glfwSetWindowShouldClose(GLFWwindowPointer, GL_TRUE); //Close the window
		}

		if (keyIsDown[GLFW_KEY_W] || keyIsDown[GLFW_KEY_UP]) //If W has been pressed
		{
			objects[1].calculateForces(vec3(0, 20, 0), deltaTime); //Calculate the forces on the object
			cam.calculateForces(vec3(0, 20, 0), deltaTime); //Calculate the forces on the camera
		}
		if (keyIsDown[GLFW_KEY_S] || keyIsDown[GLFW_KEY_DOWN]) //If S has been pressed
		{
			objects[1].calculateForces(vec3(0, -20, 0), deltaTime); //Calculate the forces on the object
			cam.calculateForces(vec3(0, -20, 0), deltaTime); //Calculate the forces on the camera
		}
		if (keyIsDown[GLFW_KEY_D] || keyIsDown[GLFW_KEY_RIGHT]) //If D has been pressed
		{
			objects[1].calculateForces(vec3(20, 0, 0), deltaTime); //Calculate the forces on the object
			cam.calculateForces(vec3(20, 0, 0), deltaTime); //Calculate the forces on the camera
		}
		if (keyIsDown[GLFW_KEY_A] || keyIsDown[GLFW_KEY_LEFT]) //If A has been pressed
		{
			objects[1].calculateForces(vec3(-20, 0, 0), deltaTime); //Calculate the forces on the object
			cam.calculateForces(vec3(-20, 0, 0), deltaTime); //Calculate the forces on the camera
		}

		if (keyIsDown[GLFW_KEY_SPACE]) //If the spacebar has been pressed
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframes
		}
		else //When spacebar is released
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //Solid faces
		}
		#pragma endregion

		#pragma region Mouse Input
		if ((keyIsDown[GLFW_MOUSE_BUTTON_RIGHT] || keyIsDown[GLFW_MOUSE_BUTTON_LEFT] || keyIsDown[GLFW_MOUSE_BUTTON_MIDDLE]) && (!keyWasDown[GLFW_MOUSE_BUTTON_RIGHT] && !keyWasDown[GLFW_MOUSE_BUTTON_LEFT] && !keyWasDown[GLFW_MOUSE_BUTTON_MIDDLE])) //If any mouse button has been pressed
		{
		}
		#pragma endregion

		#pragma region Collisions
		for (unsigned int i = 1; i < objects.size(); i++) //For each object, not the background
		{
			for (unsigned int j = i + 1; j < objects.size(); j++) //For each object, not the background
			{
				if (objects[i].collidesWith(objects[j]) == true) //If the object is colliding with another object
				{
					if (!keyIsDown[GLFW_KEY_LEFT_SHIFT]) //If the left shift key is not pressed
					{
						objects[i].resolveCollision(objects[j]); //Collide
					}
					else //When left shift is pressed
					{
						objects[j].resolveCollision(objects[i]); //Wacky physics
					}
				}
			}
		}
		#pragma endregion

		#pragma region Update Movement and Friction
		for (unsigned int i = 1; i < objects.size(); i++) //For each object, not the background
		{
			objects[i].move(deltaTime); //Move the object
		}
		cam.move(deltaTime); //Move the camera

		cam.update(objects[1]); //Update the camera

		for (unsigned int i = 1; i < objects.size(); i++) //For each object, not the background
		{
			objects[i].friction(deltaTime); //Friction for the first object
		}
		cam.friction(deltaTime); //Friction for the camera
		#pragma endregion
	}
	#pragma endregion

	#pragma region Cleanup
	for each (pair<char*, unsigned int> texData in textureData) //For each item in the texture file map
	{
		glDeleteTextures(1, &texData.second); //Delete the textures before the program terminates
	}

	glfwTerminate(); //Terminate GLFW

	return true; //Return
	#pragma endregion
}

bool Engine::useShaders() //Shaders
{
	if (shader.loadShaders("Shaders/vShader.glsl", "Shaders/fShader.glsl") == true) //If the shaders were loaded
	{
		glUseProgram(shader.getProgram()); //Run the shader program
		return true; //Return
	}
	else //If the shaders were not loaded
	{
		return false; //Return
	}
}