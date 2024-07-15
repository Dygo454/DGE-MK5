#include"CLManager.h"

Rendering::CLManager* Rendering::CLManager::instance = NULL;

Rendering::CLManager* Rendering::CLManager::GetInstance() {
    if (instance) {
        return instance;
    }
    Error::SendError("CL Manager has not been initialized!", ERR__NULL_CL__);
    return NULL;
}

void Rendering::CLManager::initCL() {
    if (instance) {
        Error::SendError("CL Manager has already been initialized!", ERR_DUPLICA_CL);
    }
    instance = new CLManager();
}
cl::CommandQueue* Rendering::CLManager::getQueue() {
    return GetInstance()->q;
}
void Rendering::CLManager::killCL() {
    if (instance) {
        delete instance;
    }
}

void Rendering::CLManager::initKernels() {
    addKernel("VertexShader", Shaders::getVertexShader(GetInstance()->q));
    addKernel("PrimitiveAssembly", Shaders::getPrimitiveAssembly(GetInstance()->q));
    addKernel("Rasterization", Shaders::getRasterization(GetInstance()->q));
    addKernel("PixelShader", Shaders::getPixelShader(GetInstance()->q));
    addKernel("DepthShader", Shaders::getDepthShader(GetInstance()->q));
    addKernel("AlphaBlending", Shaders::getAlphaBlending(GetInstance()->q));
}
void Rendering::CLManager::addKernel(std::string name, const std::string& source) {
    if (GetInstance()->kernels.find(name) != GetInstance()->kernels.end()) {
        Error::SendError("Kernel already exists!", ERR_DUPLI_KERN);
    }

    cl::Program program(*GetInstance()->c, source);
    if (program.build() != CL_SUCCESS) {
        Error::SendError("Error building: " + program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(*GetInstance()->d), ERR_KERN_COMPI);
    }
    cl::Kernel* k = new cl::Kernel(program, name.c_str());
    GetInstance()->kernels[name] = k;
}
cl::Kernel* Rendering::CLManager::getKernel(std::string name) {
    if (GetInstance()->kernels.find(name) == GetInstance()->kernels.end()) {
        Error::SendError("Kernel doesn't exists!", ERR_KERN_NOT_F);
    }
    return GetInstance()->kernels[name];
}
void Rendering::CLManager::killKernels() {
    if (instance == NULL) {
        return;
    }
    for (std::unordered_map<std::string, cl::Kernel*>::iterator it = GetInstance()->kernels.begin(); it != GetInstance()->kernels.end(); it++) {
        delete it->second;
    }
    GetInstance()->kernels.clear();
}

int Rendering::CLManager::addTextureBuffers(void* texture, int size, bool waitForMore) {
}
void Rendering::CLManager::updateTextureBuffers() {
}
void Rendering::CLManager::killTextureBuffers() {
}
