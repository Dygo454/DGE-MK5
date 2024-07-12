#include<CL/cl.hpp>
#include"../../Camera/CameraSettings.h"

namespace Shaders {
    cl::Kernel* getAlphaBlending(cl::CommandQueue* q) {
        return 0;
    }
    void doAlphaBlending(cl::Kernel* k, cl::Buffer*& buffer, cl::CommandQueue* q, const Rendering::CameraSettings& settings) {
    }
}
