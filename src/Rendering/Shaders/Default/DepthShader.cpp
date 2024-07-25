#include"../DefaultShaders.h"

namespace Shaders {
    std::string getDepthShader(cl::CommandQueue* q) {
        return "";
    }
    void doDepthShader(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffer, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer** passingBuffer, cl::Buffer* outBuffer) {
    }
}
