#version 120

attribute  vec3 position;
varying vec4 f_color;

void main(){
	gl_Position = vec4(position.x, position.y, 0, 1.0);
	// S
	if(position.z == 83){
		f_color = vec4(0.0, 1.0, 0.0, 1.0);
	} 
	// I
	else if(position.z == 73){
		//f_color = vec4(1.0, 0.0, 0.0, 1.0);
	}
	// E
	else if(position.z == 69){
		f_color = vec4(1.0, 1.0, 1.0, 1.0);
	}
	// R
	else {
		f_color = vec4(0.0, 0.0, 1.0, 1.0);
	}
}