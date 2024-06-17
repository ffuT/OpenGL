#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 u_projection;
uniform mat4 u_view;

void main() {
    vec4 pos = u_projection * u_view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
    TexCoords = vec3(aPos.x, aPos.y, aPos.z);
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube u_skybox;

void main() {
    FragColor =  vec4(1.0, 0.0, 0.0, 1.0);//texture(u_skybox, TexCoords);
}
