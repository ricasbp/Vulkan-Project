#pragma once

#include "lve_window.hpp"

namespace lve{
    class FirstApp{
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;

        FirstApp(); // Constructor declaration
        
            void run();

        //Automatically creates and destroys window. 
        //Note from yt: Doesnt create in dinamic memory;
        private: 
            LveWindow lveWindow; // Declare LveWindow as a member variable
    };
}