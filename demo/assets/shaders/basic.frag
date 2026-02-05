#version 410 core

in vec3 Normal;
in vec4 FragPosLightSpace;

uniform vec4 u_BaseColor;
uniform vec3 u_LightDir;
uniform vec3 u_LightColor;
uniform sampler2D u_ShadowMap;

out vec4 FragColor;

// Simple 3x3 PCF filtering
float PCF_Simple(vec3 projCoords, float currentDepth, float bias) {
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(u_ShadowMap, 0);
    
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(u_ShadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    return shadow;
}


float ShadowCalculation(vec4 fragPosLightSpace) {

    // We translate into the [0,1] range
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;

    // Checking texture boundaries
    if(projCoords.z > 1.0 || projCoords.x < 0.0 || projCoords.x > 1.0 || 
       projCoords.y < 0.0 || projCoords.y > 1.0)
        return 0.0;
    
    float currentDepth = projCoords.z;
    
    // Dynamic bias based on surface tilt
    vec3 lightDir = normalize(-u_LightDir);
    float cosTheta = clamp(dot(normalize(Normal), lightDir), 0.0, 1.0);
    float bias = max(0.005 * (1.0 - cosTheta), 0.008);

	// 1. Simple 3x3
    float shadow = PCF_Simple(projCoords, currentDepth, bias);

	return shadow;
}

void main() {
	float ambient = 0.2;
	vec3 lightDir = normalize(u_LightDir);
	float diff = max(dot(Normal, -lightDir), 0.0);

     // Shadow calculation
	float shadow = ShadowCalculation(FragPosLightSpace);
	shadow = shadow * 0.5;
	shadow = max(shadow - 0.2, 0.0);

     // Apply shadow: only to the diffuse component
	vec3 result = (ambient + (1.0 - shadow) * diff) * u_LightColor * u_BaseColor.rgb;
	FragColor = vec4(result, u_BaseColor.a);
}


// Testing shadow map
// void main() {
// 	vec2 uv = gl_FragCoord.xy / vec2(2048.0);
// 	float depth = texture(u_ShadowMap, uv).r;
// 	FragColor = vec4(vec3(depth), 1.0);
// }
