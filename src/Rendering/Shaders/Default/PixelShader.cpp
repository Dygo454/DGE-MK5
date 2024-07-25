#include"../DefaultShaders.h"

namespace Shaders {
    std::string getPixelShader(cl::CommandQueue* q) {
        return "";
    }
    void doPixelShader(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffer, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer** passingBuffer, cl::Buffer* outBuffer) {
    }
}
