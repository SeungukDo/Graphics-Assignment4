#version 330

in vec2 TexCoord;
in vec4 color;
out vec4 FragColor;
uniform vec4 ourColor;
uniform sampler2D myTexture;

void main()
{
	FragColor = color * ourColor;
}