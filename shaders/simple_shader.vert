// (Ricas:) This is our GLSL file, based on C-style syntax.
// Got this working by putting glslc in the current directory. 
// No need for VulkanSDK on Linux.

#version 450


vec2 positions[3] = vec2[](
    vec2(0.0, -0.5),
    vec2(0.5, -0.5),
    vec2(-0.5, -0.5)
);

// 2 float points. length 3. all sides of traingle.
void main(){ 
    gl_Position  = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    
    // 4 dimensional vetor. ( X and y Swapped)
    // 1arg: gl_VertexIndex contains index of the current vortex for each time this 
    // function is run.
    // 2arg: Z component. Closest plane is going to be 0.
    // 3arg: Divides the whole "vectorless" of points (?).
}