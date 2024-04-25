#pragma once //Ensures that header files are included only once per compilation unit. 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace lve{  //Lve meaning?
    class LveWindow{
        public:
            LveWindow(int w, int h, std::string name); // Constructor Definition
            ~LveWindow(); // Destructer to destroy window when we are not using it

            // (01, 10h34m Openining a window)
            // Ricas: Clone Method (?)
            // We write this code to make sure that, when this object LveWindow 
            // is duplicated, the pointer in the new object is not pointing to
            // a GLfwWindow instance that can be deleted by the old LveWindow.
            LveWindow(const LveWindow &) = delete;
            LveWindow &operator = (const LveWindow &) = delete;

            bool shouldClose(){ return glfwWindowShouldClose(window);} //Trying to see if user tried to close window
            VkExtent2D getExtent() {return{ static_cast<uint32_t>(width), static_cast<uint32_t> (height)}; }

            void createWindowSurface(VkInstance instace, VkSurfaceKHR *surface);
        
        private:
            void initWindow();

            const int width;
            const int height;

            std::string windowName;
            GLFWwindow *window;
    };
}