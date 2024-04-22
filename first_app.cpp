#include "first_app.hpp"

namespace lve {
    // Constructor definition to initialize lveWindow and lvePipeline
    FirstApp::FirstApp() 
        : lveWindow(WIDTH, HEIGHT, "Hello Vulkan"),
          lvePipeline("shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv") {
        // Constructor initializer list initializes lveWindow and lvePipeline
    }
    
    void FirstApp::run(){
        while(!lveWindow.shouldClose()){ // If it doesnt want to close
            glfwPollEvents(); // While window doesnt want to close -> pull window events
                              // loike keystrokes of user or clicks to X button to dismiss window
        }
    }
}