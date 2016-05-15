#include "Engine.h" //Engine header

int main() //Main method
{
	Engine idzikEngine = Engine(); //Create an engine object

	if (!idzikEngine.initialize()) //If the engine does not initialize
	{
		return 0001; //Return error code
	}

	if (!idzikEngine.bufferModels()) //If the model does not load and buffer
	{
		return 0002; //Return error code
	}

	if (idzikEngine.useShaders() == true) //If the shaders were initialized
	{
		idzikEngine.gameLoop(); //Run the game loop
	}

	return 0; //Return
}