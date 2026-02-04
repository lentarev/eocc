#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;

out vec3 Normal;
out vec4 FragPosLightSpace;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;
uniform mat4 u_LightSpaceMatrix;

void main() {
	mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
	Normal = normalize(normalMatrix * aNormal);

	vec4 worldPos = u_Model * vec4(aPos, 1.0);
	FragPosLightSpace = u_LightSpaceMatrix * worldPos; // transform into a space of light

	gl_Position = u_Proj * u_View * worldPos;

}