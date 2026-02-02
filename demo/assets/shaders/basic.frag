#version 410 core

in vec3 Normal;

uniform vec4 u_BaseColor;
uniform vec3 u_LightDir;
uniform vec3 u_LightColor;

out vec4 FragColor;

void main() {
	float ambient = 0.2;
	vec3 lightDir = normalize(u_LightDir);
	float diff = max(dot(Normal, -lightDir), 0.0);
	vec3 result = (ambient + diff) * u_LightColor * u_BaseColor.rgb;
	FragColor = vec4(result, u_BaseColor.a);
}