#include"../DefaultShaders.h"

namespace Shaders {
    std::string getVertexShader(cl::CommandQueue* q) {
        return "struct CameraSettings {"
        "    unsigned int targetWidth;"
        "    unsigned int targetHeight;"
        "    double nearPlane;"
        "    double farPlane;"
        "    double fovY;"
        "    double sizeY;"
        "    unsigned char rasterStyle;"
        "    bool orthographic;"
        "};"
        "kernel void VertexShader(global void* verticies, global double* projectionMatrix, CameraSettings settings) {"
        "    unsigned int id = get_global_id(0);"
        "    unsigned int size = ((unsigned int*)verticies)[0];"
        "    if (id >= size) return;"
        "    id = (id * 12)+4;"
        "    double* vertex = (int*)(verticies + id);"
        "    double& x = vertex[0];"
        "    double& y = vertex[1];"
        "    double& z = vertex[2];"
        "    double outX = vertex[0];"
        "    double outY = vertex[1];"
        "    double outZ = vertex[2];"
        "    "
        "    // do camera transformations here"
        "    "
        "    outX = x*projectionMatrix[0] + y*projectionMatrix[4] + z*projectionMatrix[8] + projectionMatrix[12];"
        "    outY = x*projectionMatrix[1] + y*projectionMatrix[5] + z*projectionMatrix[9] + projectionMatrix[13];"
        "    outZ = x*projectionMatrix[2] + y*projectionMatrix[6] + z*projectionMatrix[10] + projectionMatrix[14];"
        "    double w = x*projectionMatrix[3] + y*projectionMatrix[7] + z*projectionMatrix[11] + projectionMatrix[15];"
        "    "
        "    x /= w;"
        "    y /= w;"
        "    z /= w;"
        "}";
    }
    void doVertexShader(cl::Kernel* k, cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffers, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer** passingBuffer, cl::Buffer* outBuffer) {
        cl::Buffer* projMat = projectionMatrixPersp;
        if (settings.orthographic) {
            projMat = projectionMatrixOrtho;
        }
        cl::KernelFunctor vertexShader(*k, *q, cl::NullRange, cl::NDRange((vertexBuffer->getInfo<CL_MEM_SIZE>() - 4)/12), cl::NullRange);
        vertexShader(*vertexBuffer, *projMat, settings);
    }
}
