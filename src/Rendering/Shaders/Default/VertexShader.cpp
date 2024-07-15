#include"../DefaultShaders.h"

namespace Shaders {
    std::string getVertexShader(cl::CommandQueue* q) {
        return "";
    }
    void doVertexShader(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffers, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer* assembledBuffer, cl::Buffer* outBuffer) {
    }
}
