#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"

namespace lve{
    class FirstApp{
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;
            FirstApp();   // Constructor declaration
            void run();

        // Automatically creates and destroys window.
        // That's why we don't need a destroyer in this class (?)
        // Note from Youtube: Doesnt create in dinamic memory;
        private: 
            LveWindow lveWindow; // Declare LveWindow as a member variable
            LvePipeline lvePipeline;
    };
}