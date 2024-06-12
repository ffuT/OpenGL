#shader vertex
#version 330 core

layout(location = 0) in vec4 positions;

uniform vec4 u_sunPosition;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out float colorStr;

void main(){
	vec4 position = positions;
	vec4 u_sunPos = u_sunPosition;
	//calc Lambertian reflectance kinda - Lambertian is normal vector i use the vertex position, looks fine tho
	colorStr = (u_sunPos.x * position.x + u_sunPos.y * position.y + u_sunPos.z * position.z) 
	/ (sqrt(u_sunPos.x*u_sunPos.x+u_sunPos.y*u_sunPos.y+u_sunPos.z*u_sunPos.z)  
	* sqrt(position.x*position.x+position.y*position.y+position.z*position.z)); 

	gl_Position = u_projection * u_view * u_model * vec4(position.xyz , 1.0);
};

#shader fragment
#version 330 core

uniform vec4 u_sunCol;
uniform vec4 u_sphereCol;

in float colorStr;
out vec4 Color;

void main(){
	Color = u_sunCol * (max(colorStr,0.0)+0.1) * u_sphereCol;
};