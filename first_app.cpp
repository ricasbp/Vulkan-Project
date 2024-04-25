#include "first_app.hpp"

#include <stdexcept>

namespace lve {
    
    // Constructor definition to initialize lveWindow, lvePipeline, etc...
    FirstApp::FirstApp() 
        : lveWindow(WIDTH, HEIGHT, "Hello Vulkan"),
          lveDevice(lveWindow),
          lveSwapChain(lveDevice, lveWindow.getExtent()) {
        // Constructor initializer, initializes lveWindow, lvePipeline,  etc...

        createPipeLineLayout();
        createPipeline();
        createCommandBuffers();

        // Initialize lvePipeline using std::make_unique
        auto pipelineConfig = LvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT);
        pipelineConfig.renderPass = lveSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;

        lvePipeline = std::make_unique<LvePipeline>(
            lveDevice,
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv",
            pipelineConfig);
    }

    FirstApp::~FirstApp(){
        vkDestroyPipelineLayout(lveDevice.device(), pipelineLayout, nullptr);
    }
    
    void FirstApp::run() {
        while (!lveWindow.shouldClose()) { // If it doesn't want to close
            glfwPollEvents(); // While window doesn't want to close -> poll window events
                              // like keystrokes of user or clicks to X button to dismiss window
        }
    }
    
    void FirstApp::createPipeLineLayout(){
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr; //Super effecint small info to shaders;
        if(vkCreatePipelineLayout(
            lveDevice.device(), 
            &pipelineLayoutInfo, 
            nullptr, 
            &pipelineLayout) != VK_SUCCESS){
                throw std::runtime_error("Failed to create pipeline layout!");
            }
    }
    
    void FirstApp::createPipeline(){
        auto pipelineConfig =  
            LvePipeline::defaultPipelineConfigInfo(lveSwapChain.width(), lveSwapChain.height());
        
        //Brief Explination to RenderPassing (15m10s, Swap Chain Overview)
        pipelineConfig.renderPass = lveSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        lvePipeline  = std::make_unique<LvePipeline>(
            lveDevice,
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv",
            pipelineConfig);
    }

    void FirstApp::createCommandBuffers(){
        
        commandBuffers.resize(lveSwapChain.imageCount());

        //allocate
        VkCommandBufferAllocateInfo allocInfo{}{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        //Primary command buffer can ask for seondary command buffers.
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;


    }
    
    void FirstApp::drawFrame(){

    }
    
} // Closing namespace lve
