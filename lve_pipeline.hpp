#pragma once

#include "lve_device.hpp"
#include <string>
#include <vector>

namespace lve{

    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class LvePipeline{
      public:
        LvePipeline(LveDevice &device, 
                    const std::string& vertFilepath, 
                    const std::string& fragFilepath, 
                    const PipelineConfigInfo& configInfo);

        // Since our pipeline is responsible for manigin the lifetime of
        // this resources, we need this destroyer (He's talking about Global variables (?))
        ~LvePipeline(); //IMPLEMENTED IN .CPP


        // We dont want to duplicate our pointers to the vulkan objects
        LvePipeline(const LvePipeline&) = delete;
        void operator=(const LvePipeline&) = delete;

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

        
      private:
        static std::vector<char> readFile(const std::string& filePath);
        
        void createGraphicsPipeline(
            const std::string& vertFilepath,
            const std::string& fragFilepath,
            const PipelineConfigInfo& configInfo);

        void createShaderModule(const std::vector<char>& code, 
        VkShaderModule* shaderModule);

        LveDevice& lveDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;

    };
}