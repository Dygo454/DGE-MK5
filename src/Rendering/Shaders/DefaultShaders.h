#ifndef DEFAULT_SHADERS_H
#define DEFAULT_SHADERS_H

#include<string>
#include<CL/cl.hpp>
#include"../Camera/CameraSettings.h"

namespace Shaders {
    std::string getVertexShader(cl::CommandQueue* q);
    void doVertexShader(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffers, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer* assembledBuffer, cl::Buffer* outBuffer);
    std::string getPrimitiveAssembly(cl::CommandQueue* q);
    void doPrimitiveAssembly(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffers, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer* assembledBuffer, cl::Buffer* outBuffer);
    std::string getRasterization(cl::CommandQueue* q);
    void doRasterization(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffers, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer* assembledBuffer, cl::Buffer* outBuffer);
    std::string getPixelShader(cl::CommandQueue* q);
    void doPixelShader(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffers, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer* assembledBuffer, cl::Buffer* outBuffer);
    std::string getDepthShader(cl::CommandQueue* q);
    void doDepthShader(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffers, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer* assembledBuffer, cl::Buffer* outBuffer);
    std::string getAlphaBlending(cl::CommandQueue* q);
    void doAlphaBlending(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffers, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer* assembledBuffer, cl::Buffer* outBuffer);
}

#endif
