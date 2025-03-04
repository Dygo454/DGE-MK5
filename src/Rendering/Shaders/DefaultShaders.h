#ifndef DEFAULT_SHADERS_H
#define DEFAULT_SHADERS_H

#include<string>

namespace Shaders {
    double* projectionMatrixOrtho;
    double* projectionMatrixPersp;

    std::string getVertexShader();
    std::string getPrimitiveAssembly();
    std::string getClippingShader();
    std::string getRasterization();
    std::string getGBufferShader();
    std::string getLightingShader();
    std::string getDepthShader();
    std::string getCompositionShader();
}

#endif
