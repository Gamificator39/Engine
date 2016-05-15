#include "Model.h" //Model header

Model::Model() //Constructor
{
	vertexArray = 0; //Set vertexArray to 0
	vertexCount = 0; //Set vertexCount to 0
}

Model::~Model() //Destructor
{
}

bool Model::buffer() //Buffer models
{
	#pragma region Model File Loading and Buffering
	vector<vec3> locations; //Object location
	vector<vec2> uvs; //Object UVs
	vector<vec3> normals; //Object normals
	vector<VertexIndex> vertexIndices; //Object vertex indexes

	ifstream inFile; //File input
	string line; //Line from the file

	inFile.open(objFileName); //Open the model file

	if (inFile.is_open()) //If the file was successfully opened
	{
		while (getline(inFile, line)) //Read in the contents of the file, one line at a time
		{
			istringstream iss(line); //Create an istringstream object from the line
			string lineLabel; //The line label for the current line

			iss >> lineLabel; //Read in the line label from the istringstream

			if (lineLabel == "v") //If the line label is v
			{
				float vIndices[3]; //Floats to store the location indexes

				iss >> vIndices[0] >> vIndices[1] >> vIndices[2]; //Read in the location indices
				locations.push_back(vec3(vIndices[0], vIndices[1], vIndices[2])); //Add the locations into the location vector
			}
			else if (lineLabel == "vt") //If the line label is vt
			{
				float vtIndices[3]; //Floats to store the UV indexes

				iss >> vtIndices[0] >> vtIndices[1]; //Read in the UV indices
				uvs.push_back(vec2(vtIndices[0], vtIndices[1])); //Add the UVs into the UV vector
			}
			else if (lineLabel == "vn") //If the line label is vn
			{
				float vnIndices[3]; //Floats to store the normal indexes

				iss >> vnIndices[0] >> vnIndices[1] >> vnIndices[2]; //Read in the normal indices
				normals.push_back(vec3(vnIndices[0], vnIndices[1], vnIndices[2])); //Add the normals into the normal vector
			}
			else if (lineLabel == "f") //If the line label is f
			{
				for (int i = 0; i < 3; i++) //Loop to get all three pieces of data from the line
				{
					unsigned int faceData[3]; //Unsigned ints to store the face data
					char fSlash; //Character to store the slash

					iss >> faceData[0] >> fSlash >> faceData[1] >> fSlash >> faceData[2]; //Read in the face data

					faceData[0]--; //Decrement the first face data
					faceData[1]--; //Decrement the second face data
					faceData[2]--; //Decrement the third face data

					VertexIndex vertIndex = { faceData[0], faceData[1], faceData[2] }; //Add the face data to a VertexIndex
					vertexIndices.push_back(vertIndex); //Add the face data into the VertexIndex vector
				}
			}
		}
		inFile.close(); //Close the file
	}

	vertexCount = vertexIndices.size(); //Keep track of the number of connections

	vector<Vertex> vertexBufferData(vertexCount); //Allocate a vertex buffer with enough space for the object
	for (unsigned int i = 0; i < vertexCount; i++) //For each connection
	{
		vertexBufferData[i] = { locations[vertexIndices[i].locationIndex], uvs[vertexIndices[i].uvIndex], normals[vertexIndices[i].normalIndex]}; //Add data to the vertex buffer
	}

	GLuint vertexBuffer; //Vertex buffer object

	glGenVertexArrays(1, &vertexArray); //Bind the vertex array
	glGenBuffers(1, &vertexBuffer); //Bind the vertex buffer

	glBindVertexArray(vertexArray); //Controls which array is active
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); //Control which buffer is active

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, &vertexBufferData[0], GL_STATIC_DRAW); //Copies specified data into the currently bound buffer (Where to copy to, number of bytes to copy, where to copy from, optimization)

	glEnableVertexAttribArray(0); //Attribute index is 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); //Location: attribute index, number of components, type of data, normalized or not, bytes per vertex, offset
	glEnableVertexAttribArray(1); //Attribute index is 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec3)); //UV: attribute index, number of components, type of data, normalized or not, bytes per vertex, offset
	glEnableVertexAttribArray(2); //Attribute index is 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec3)); //Normal: attribute index, number of components, type of data, normalized or not, bytes per vertex, offset
	glBindVertexArray(0); //Unbind the vertex array

	glClearColor(0.f, 0.f, 0.f, 1.0f); //Set the clear color

	return true; //Return
	#pragma endregion
}

void Model::render() //Render models
{
	glBindVertexArray(vertexArray); //Controls which array is active
	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Render game objects
}
