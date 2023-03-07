#version 330 core

out vec4 color;

in vec2 texCoord;
in vec4 pointPos;

uniform sampler2D texture0;

void main() {
	color = texture( texture0, texCoord );
	float intensity = 10.0f / ( pointPos.w * pointPos.w );
	
	if ( intensity > 1.0f ) { intensity = 1.0f; }
	
	vec4 tint = vec4( intensity, 0, 0, 1.0f );
	color *= tint;
}
