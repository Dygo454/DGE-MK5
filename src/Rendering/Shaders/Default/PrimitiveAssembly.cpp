#include"../DefaultShaders.h"

namespace Shaders {
    std::string getPrimitiveAssembly() {
        return "kernel void PrimitiveAssembly(global void* verticies, global void* indices, global void* assembled) {\n"
        "    unsigned int tri = get_global_id(0);\n"
        "    if (tri = 0) ((unsigned long long)assembled)[0] = (unsigned int)indices[0];\n"
        "    if (tri >= (unsigned int)indices[0]) return;\n"
        "    unsigned int* indicesOffset = indices + tri*3*sizeof(unsigned int) + 1;\n"
        "    void* assembledOffset = assembled + ((tri*24*sizeof(double)) + 1);\n"
        "    for (int i = 0; i < 3; ++i) {\n"
        "        unsigned int currVert = indicesOffset[i]*3 + 1;\n"
        "        for (int n = 0; n < 3; ++n) {\n"
        "            unsigned int currCord = currVert + n;\n"
        "            unsigned int currNorm = ((unsigned int)indices[0])*3 + currCord;\n"
        "            unsigned int currUV = ((unsigned int)indices[0])*6 + currCord;\n"
        "            ((double*)assembledOffset)[i*3 + n] = ((double*)verticies)[currCord];\n"
        "            ((double*)assembledOffset)[i*3 + n + 9] = ((double*)verticies)[currNorm];\n"
        "            if (n < 2)\n"
        "                ((double*)assembledOffset)[i*2 + n + 18] = ((double*)verticies)[currUV];\n"
        "        }\n"
        "    }\n"
        "}";
    }
}
