#include"../DefaultShaders.h"

namespace Shaders {
    std::string getAlphaBlending(cl::CommandQueue* q) {
        return "";
    }
    void doAlphaBlending(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffers, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer** passingBuffer, cl::Buffer* outBuffer) {
    }
}
