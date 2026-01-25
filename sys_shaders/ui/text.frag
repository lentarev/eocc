#version 410 core

in vec2 TexCoord;
in vec3 Color;
out vec4 FragColor;

uniform sampler2D u_Texture;

void main() {
    float alpha = texture(u_Texture, TexCoord).r;
    if (alpha < 0.5) discard;
    FragColor = vec4(Color, 1.0);
}
