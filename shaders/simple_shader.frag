// (Ricas:) This is our GLSL file, based on C-style syntax.

#version 450

//for now we only want to color the layer 0.
layout (location = 0) out vec4 outColor; 

void main(){
    outColor = vec4(1.0,0.0,0.0, 1.0); // RGBA. 
}