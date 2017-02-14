#version 120

uniform float maxPossibleInfected;
attribute  vec3 position;
varying vec4 f_color;

void main(){
	gl_Position = vec4(position.xy, 0, 1.0);

	if(position.z == 0){
		f_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}else{
		f_color = vec4(1.0, 1.0f / position.z, 0.0, 1.0);
	}
}