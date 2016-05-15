#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) uniform mat4 modelMatrix;
layout (location = 4) uniform mat4 cameraMatrix;
out vec2 fragUV;
out vec3 cameraLocation;
out vec3 fragmentLocation;
out vec3 fragmentNormal;

void main()
{
	gl_Position = cameraMatrix * modelMatrix * vec4(position, 1);
	fragmentLocation = gl_Position.xyz;
	fragUV = uv;
	fragmentNormal = normalize((modelMatrix * vec4(normal, 0)).xyz);
	cameraLocation = vec3(inverse(cameraMatrix)[3]);
}