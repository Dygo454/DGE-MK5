#ifndef DEFAULT_SHADERS_H
#define DEFAULT_SHADERS_H

#include<string>

namespace Shaders {
    double* projectionMatrixOrtho;
    double* projectionMatrixPersp;

    const std::string& getVertexShader();
    const std::string& getPrimitiveAssembly();
    const std::string& getRasterization();
    const std::string& getGBufferShader();
    const std::string& getLightingShader();
    const std::string& getDepthShader();
    const std::string& getCompositionShader();
}

#endif
