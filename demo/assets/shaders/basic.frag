#version 410 core

in vec3 Normal;
in vec4 FragPosLightSpace;

uniform vec4 u_BaseColor;
uniform vec3 u_LightDir;
uniform vec3 u_LightColor;
uniform sampler2D u_ShadowMap;

out vec4 FragColor;

// // PCF kernel size
const float bias = 0.01;
// float bias = max(0.04 * (1.0 - dot(Normal, u_LightDir)), 0.03);

float ShadowCalculation(vec4 fragPosLightSpace) {

    // We translate into the [0,1] range
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;

    // We get the nearest depth from the map
	float closestDepth = texture(u_ShadowMap, projCoords.xy).r;

    // Current fragment depth
	float currentDepth = projCoords.z;

    // Bias-adjusted comparison
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

	return shadow;
}

void main() {
	float ambient = 0.2;
	vec3 lightDir = normalize(u_LightDir);
	float diff = max(dot(Normal, -lightDir), 0.0);

     // Расчёт тени
	float shadow = ShadowCalculation(FragPosLightSpace);

     // Apply shadow: only to the diffuse component
	vec3 result = (ambient + (1.0 - shadow) * diff) * u_LightColor * u_BaseColor.rgb;
	FragColor = vec4(result, u_BaseColor.a);
}

//void main() {
// 	vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w;
// 	projCoords = projCoords * 0.5 + 0.5;
// 	float depth = texture(u_ShadowMap, projCoords.xy).r;
// 	FragColor = vec4(vec3(depth), 1.0);
//}

// void main() {
// 	vec2 uv = gl_FragCoord.xy / vec2(2048.0);
// 	float depth = texture(u_ShadowMap, uv).r;
// 	FragColor = vec4(vec3(depth), 1.0);
// }
