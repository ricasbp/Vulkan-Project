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
            drawFrame();
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
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        //Primary command buffer can ask for seondary command buffers.
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        // Initialized in Device
        // Initializes and frees command buffers.
        allocInfo.commandPool = lveDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if(vkAllocateCommandBuffers(lveDevice.device(), &allocInfo, commandBuffers.data()) 
            != VK_SUCCESS){
                throw std::runtime_error("Failed to allocate command buffes!");
        }

        for(int i = 0; i < commandBuffers.size(); i++){
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            
            if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS){
                throw std::runtime_error("Failed to begin recording command buffer");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = lveSwapChain.getRenderPass();
            renderPassInfo.framebuffer = lveSwapChain.getFrameBuffer(i);

            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = lveSwapChain.getSwapChainExtent();

            // in Frame Buffer, 0 is the color buffer, 1 is the depth buffer;
            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0}; // 0 Close, 1 far

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            // (08m00s, 05_p2) 
            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            lvePipeline->bind(commandBuffers[i]);
            // 3 vertices, in only 1 instance.
            // Instance can be used to draw multiple copies of the same vertex data.
            // Sometimes used in particle systems.
            // 0,0 because no offsets.
            vkCmdDraw(commandBuffers[i], 3, 1, 0, 0); 


            vkCmdEndRenderPass(commandBuffers[i]);
            if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS){
                throw std::runtime_error("Failed to record command buffer");
            }




        }

    }
    
    void FirstApp::drawFrame(){
        uint32_t imageIndex;
        // This function fetches the index of the frame we should render to next.
        // it also automaticcaly handles all the cpu and gpu synchronization
        //   surrounding double and triple buffering
        // return tell us if it was successful or not
        auto result = lveSwapChain.acquireNextImage(&imageIndex);

        if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
            throw std::runtime_error("Failed to aquire swap chain image!");
        }

        result = lveSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
        if(result != VK_SUCCESS){
            throw std::runtime_error("Failed to present swap chain image!");
        }
    }
    
} // Closing namespace lve
