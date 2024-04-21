#pragma once //Ensures that header files are included only once per compilation unit. 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace lve{  //Lve meaning?
    class LveWindow{
        public: 
            LveWindow(int w, int h, std::string name); //Constructor Definition
            ~LveWindow(); //Destructer to destroy window when we are not using it

            bool shouldClose(){ return glfwWindowShouldClose(window);} //Trying to see if user tried to close window
        private:

            void initWindow();

            const int width;
            const int height;

            std::string windowName; //#include <string> need this to make sure i 
                                    // can import the strin class?
            GLFWwindow *window;
    };
}