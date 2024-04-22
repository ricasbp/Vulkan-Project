#pragma once

#include "lve_device.hpp"
#include <string>
#include <vector>

namespace lve{

    struct PipelineConfigInfo{};

    class LvePipeline{
      public:
        LvePipeline(LveDevice &device, 
                    const std::string& vertFilepath, 
                    const std::string& fragFilepath, 
                    const PipelineConfigInfo& configInfo);

        // Since our pipeline is responsible for manigin the lifetime of
        // this resources. (He's talking about Global variables (?))
        ~LvePipeline(){}

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
        VkPipeline graphicPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;

    };
}