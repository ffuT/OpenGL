#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

out vec2 v_TexCoords;

uniform float u_Time;
uniform mat4 u_MVP;
uniform int u_RotSpeed;

vec2 Rotate2D(vec2 pos, int speed){

	return vec2(pos.x * cos(u_Time/10*speed) - pos.y * sin(u_Time/10*speed),
				pos.x * sin(u_Time/10*speed) + pos.y * cos(u_Time/10*speed));
}

void main(){
	v_TexCoords = texCoords;
	gl_Position = (u_MVP * vec4(Rotate2D(position.xy, u_RotSpeed), 1.0 , 1.0));
};

#shader fragment
#version 330 core

in vec2 v_TexCoords;
uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform float u_Time;
out vec4 Color;


void main(){
	vec4 texColor = texture(u_Texture, v_TexCoords);
	
	Color = mix(texColor,u_Color, (sin(u_Time)+1)/2);
};