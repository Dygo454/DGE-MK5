#include"../DefaultShaders.h"

namespace Shaders {
    std::string getPrimitiveAssembly() {
        return "kernel void PrimitiveAssembly(global void* verticies, global void* indecies, global void* assembled) {"
        "    unsigned int tri = get_global_id(0);"
        "    if (tri = 0) ((unsigned long long)assembled)[0] = (unsigned int)indecies[0];"
        "    if (tri >= (unsigned int)indecies[0]) return;"
        "    unsigned int* indeciesOffset = indecies + tri*3*sizeof(unsigned int) + 1;"
        "    void* assembledOffset = assembled + ((tri*25*sizeof(unsigned long long)) + 1);"
        "    for (int i = 0; i < 3; ++i) {"
        "        unsigned int currVert = indeciesOffset[i]*3 + 1;"
        "        for (int n = 0; n < 3; ++n) {"
        "            unsigned int currCord = currVert + n;"
        "            unsigned int currNorm = ((unsigned int)indecies[0])*3 + currCord;"
        "            unsigned int currUV = ((unsigned int)indecies[0])*6 + currCord;"
        "            ((double*)assembledOffset)[i*3 + n] = ((double*)verticies)[currCord];"
        "            ((double*)assembledOffset)[i*3 + n + 9] = ((double*)verticies)[currNorm];"
        "            if (n < 2)"
        "                ((double*)assembledOffset)[i*3 + n + 18] = ((double*)verticies)[currUV];"
        "        }"
        "    }"
        "}";
    }
}
