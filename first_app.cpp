#include "first_app.hpp"

namespace lve {
    FirstApp::FirstApp() : lveWindow(WIDTH, HEIGHT, "Hello Vulkan") {
        // Constructor initializer list initializes lveWindow
    }
    
    void FirstApp::run(){
        while(!lveWindow.shouldClose()){ // If it doesnt want to close
            glfwPollEvents(); // While window doesnt want to close, pull window events
                              // keystrokes, a user click to X button to dismiss window
        }
    }
}