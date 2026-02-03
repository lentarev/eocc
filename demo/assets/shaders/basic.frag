#version 410 core

in vec3 Normal;
in vec4 FragPosLightSpace; // ← новое

uniform vec4 u_BaseColor;
uniform vec3 u_LightDir;
uniform vec3 u_LightColor;
uniform sampler2D u_ShadowMap; // ← новое

out vec4 FragColor;

// // PCF kernel size
const float bias = 0.05; // ← можно регулировать

float ShadowCalculation(vec4 fragPosLightSpace) {
    // Переводим в [0,1] диапазон
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;

    // Получаем ближайшую глубину из карты
	float closestDepth = texture(u_ShadowMap, projCoords.xy).r;

    // Текущая глубина фрагмента
	float currentDepth = projCoords.z;

    // Сравнение с поправкой на bias
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

	return shadow;
}

void main() {
	float ambient = 0.2;
	vec3 lightDir = normalize(u_LightDir);
	float diff = max(dot(Normal, -lightDir), 0.0);

    // Расчёт тени
	float shadow = ShadowCalculation(FragPosLightSpace);

    // Применяем тень: только к диффузному компоненту
	vec3 result = (ambient + (1.0 - shadow) * diff) * u_LightColor * u_BaseColor.rgb;
	FragColor = vec4(result, u_BaseColor.a);
}

//void main() {
// 	vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w;
// 	projCoords = projCoords * 0.5 + 0.5;
// 	float depth = texture(u_ShadowMap, projCoords.xy).r;
// 	FragColor = vec4(vec3(depth), 1.0);
//}

//void main() {
//	vec2 uv = gl_FragCoord.xy / vec2(2048.0);
//   float depth = texture(u_ShadowMap, uv).r;
//    FragColor = vec4(vec3(depth), 1.0);
//}