#include"../DefaultShaders.h"

namespace Shaders {
    std::string getVertexShader() {
        return "kernel void VertexShader(global void* verticies, double* projectionMatrix, double *cameraTransform) {\n"
        "    unsigned int id = get_global_id(0);\n"
        "    unsigned int size = ((unsigned int*)verticies)[0];\n"
        "    if (id >= size) return;\n"
        "    id = (id * 3) + 1;\n" // TODO: Shouldn't vectors also get normalized????
        "    double* vertex = ((double*)verticies) + id;\n"
        "    double& x = vertex[0];\n"
        "    double& y = vertex[1];\n"
        "    double& z = vertex[2];\n"
        "    \n"
        "    x -= cameraTransform[0];\n" // translation
        "    y -= cameraTransform[1];\n"
        "    z -= cameraTransform[2];\n"
        "    \n"
        "    double tempX = vertex[0];\n"
        "    double tempY = vertex[1];\n"
        "    double tempZ = vertex[2];\n"
        "    cameraTransform[3] *= -1\n"
        "    cameraTransform[4] *= -1\n"
        "    cameraTransform[5] *= -1\n"
        "    double t2 = cameraTransform[6] * cameraTransform[3];\n" // rotation
        "    double t3 = cameraTransform[6] * cameraTransform[4];\n"
        "    double t4 = cameraTransform[6] * cameraTransform[5];\n"
        "    double t5 = -cameraTransform[3] * cameraTransform[3];\n"
        "    double t6 = cameraTransform[3] * cameraTransform[4];\n"
        "    double t7 = cameraTransform[3] * cameraTransform[5];\n"
        "    double t8 = -cameraTransform[4] * cameraTransform[4];\n"
        "    double t9 = cameraTransform[4] * cameraTransform[5];\n"
        "    double t10 = -cameraTransform[5] * cameraTransform[5];\n"
        "    x = 2 * ((t8 + t10) * tempX + (t6 - t4) * tempY + (t3 + t7) * tempZ) + tempX;\n"
        "    y = 2 * ((t4 + t6) * tempX + (t5 + t10) * tempY + (t9 - t2) * tempZ) + tempY;\n"
        "    z = 2 * ((t7 - t3) * tempX + (t2 + t9) * tempY + (t5 + t8) * tempZ) + tempZ;\n"
        "    \n"
        "    x /= cameraTransform[7];\n" // scale
        "    y /= cameraTransform[8];\n"
        "    z /= cameraTransform[9];\n"
        "    \n"
        "    tempX = x;\n"
        "    tempY = y;\n"
        "    tempZ = z;\n"
        "    \n"
        "    x = tempX*projectionMatrix[0] + tempY*projectionMatrix[4] + tempZ*projectionMatrix[8] + projectionMatrix[12];\n"
        "    y = tempX*projectionMatrix[1] + tempY*projectionMatrix[5] + tempZ*projectionMatrix[9] + projectionMatrix[13];\n"
        "    z = tempX*projectionMatrix[2] + tempY*projectionMatrix[6] + tempZ*projectionMatrix[10] + projectionMatrix[14];\n"
        "    double w = tempX*projectionMatrix[3] + tempY*projectionMatrix[7] + tempZ*projectionMatrix[11] + projectionMatrix[15];\n"
        "    \n"
        "    x /= w;\n"
        "    y /= w;\n"
        "    z /= w;\n"
        "}";
    }
}
