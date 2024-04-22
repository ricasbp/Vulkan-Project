#include "lve_pipeline.hpp"

//std
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace lve{
    LvePipeline::LvePipeline(const std::string& vertFilepath, const std::string& fragFilepath){
        createGraphicsPipeline(vertFilepath, fragFilepath);
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
        
    void LvePipeline::
      createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath){
        auto vertCode = readFile(vertFilepath);
        auto fragCode = readFile(fragFilepath);

        std::cout << "Vertex Shader Code Size:" << vertCode.size() << '\n';
        std::cout << "Fragment Shader Code Size:" << vertCode.size() << '\n';
    }

}