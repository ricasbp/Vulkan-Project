#include "lve_pipeline.hpp"

//std
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace lve{
    LvePipeline::LvePipeline(LveDevice &device, 
                    const std::string& vertFilepath, 
                    const std::string& fragFilepath, 
                    const PipelineConfigInfo& configInfo)
                    : lveDevice{device}{ 
                    //Initialize our device in a member incializer list (??)
        createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
    }

    // Implementation of "lve_pipeline.hpp"
    // static std::vector<char> readFile(const std::string& filePath);
    std::vector<char> LvePipeline::readFile(const std::string& filePath){
        // Std::ios flags
        std::ifstream file{filePath, std::ios::ate | std::ios::binary};
        
        if(!file.is_open()){
            throw std::runtime_error("Failed to open file: (Wrong Permissions or wrong path)" + filePath);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize); //Characther buffer w/size of file. Vector of characthers
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }
        
    void LvePipeline::createGraphicsPipeline(
            const std::string& vertFilepath,
            const std::string& fragFilepath,
            const PipelineConfigInfo& configInfo){

        auto vertCode = readFile(vertFilepath);
        auto fragCode = readFile(fragFilepath);

        std::cout << "Vertex Shader Code Size:" << vertCode.size() << '\n';
        std::cout << "Fragment Shader Code Size:" << vertCode.size() << '\n';
    }

    void LvePipeline::createShaderModule(const std::vector<char>& code, 
        VkShaderModule* shaderModule){
            VkShaderModuleCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            createInfo.codeSize = code.size();
            createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

            // lveDevice.device() -> a getter to the VUlkan Device Handler.

            if(vkCreateShaderModule(lveDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS){
                throw std::runtime_error("Failed tocreate shader module");
            }
        }

    PipelineConfigInfo LvePipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height){
        //ConfigInfo local variable
        PipelineConfigInfo configInfo{};

        return configInfo;
    }


}