#version 410 core
layout (location = 0) in vec2 v_position;
layout (location = 1) in vec4 v_color;

out vec4 a_color;

void main(){
	a_color = v_color;
	gl_Position = vec4(v_position, 0.0, 1.0);
}