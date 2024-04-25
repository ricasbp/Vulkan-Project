#Compile shaders code.

#Compile shaders: 
# chmod +x compile.sh
# ./compile.sh

/usr/local/bin/glslc shaders/simple_shader.vert -o shaders/simple_shader.vert.spv
/usr/local/bin/glslc shaders/simple_shader.frag -o shaders/simple_shader.frag.spv


#1arg: Shaders/... 