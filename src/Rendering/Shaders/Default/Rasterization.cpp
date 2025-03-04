#include"../DefaultShaders.h"

namespace Shaders {
    std::string getRasterization() {
        return "kernel void Rasterization(void* assembled, void* fragmentsBuffer) {"
        "    unsigned int tri = get_global_id(0);"
        "    if (tri >= (unsigned long long)assembled[0]) return;"
        "    void* assembledOffset = assembled + ((tri*25*sizeof(unsigned long long)) + 1);"
        "    "
        "}";
    }
}
