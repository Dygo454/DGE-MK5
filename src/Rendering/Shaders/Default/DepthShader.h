#include<CL/cl.hpp>
#include"../../Camera/CameraSettings.h"

namespace Shaders {
    cl::Kernel* getDepthShader(cl::CommandQueue* q) {
        return 0;
    }
    void doDepthShader(cl::Kernel* k, cl::Buffer*& buffer, cl::CommandQueue* q, const Rendering::CameraSettings& settings) {
    }
}
