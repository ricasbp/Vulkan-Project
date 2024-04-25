#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"

#include <memory>
#include <vector>

namespace lve{
    class FirstApp{
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;
            
            FirstApp();   // Constructor declaration
            ~FirstApp();

            // Copy Constructor
            FirstApp(const FirstApp &) = delete;
            FirstApp &operator = (const FirstApp &) = delete;

            void run();

        // Automatically creates and destroys window.
        // That's why we don't need a destroyer in this class (?)
        // Note from Youtube: Doesnt create in dinamic memory;
        private: 
            void createPipeLineLayout();
            void createPipeline();
            void createCommandBuffers();
            void drawFrame();

            LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
            LveDevice lveDevice{lveWindow};
            LveSwapChain lveSwapChain{lveDevice, lveWindow.getExtent()};
            std::unique_ptr<LvePipeline> lvePipeline;
            VkPipelineLayout pipelineLayout;
            std::vector<VkCommandBuffer> commandBuffers;

    };
}