#include "lve_window.hpp"

namespace lve {
    
    //Here is the constructor for our class variables.
    //e.g: We receive w, and construct width variable;
    
    LveWindow::LveWindow(int w, int h, std::string name) : width(w), height(w), windowName(name){
        initWindow();
    }

    LveWindow::~LveWindow(){ //Destroyer
        glfwDestroyWindow(window); //Destroy glfw in specific Window Pointer
        glfwTerminate();
    }

    void LveWindow::initWindow(){
        glfwInit(); //Initialize the glfw livrary;
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // We want to use Vulkan;
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //Tutorial 20 explains it. REsize window

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    }


}// namespace lve