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

    double* projectionMatrixOrtho = new double[16];
    double* projectionMatrixPersp = new double[16];
    for (int i = 0; i < 16; i++) {
        projectionMatrixOrtho[i] = 0;
        projectionMatrixPersp[i] = 0;
    }
    projectionMatrixOrtho[0] = 1.0/settings.sizeY;
    projectionMatrixOrtho[5] = 1.0/settings.sizeY;
    projectionMatrixOrtho[10] = -1 / (settings.farPlane - settings.nearPlane);
    projectionMatrixOrtho[11] = -settings.nearPlane / (settings.farPlane - settings.nearPlane);
    projectionMatrixOrtho[15] = 1;

    double scale = 1 / tan(settings.fovY * 0.5 * M_PI / 180);
    projectionMatrixPersp[0] = scale;
    projectionMatrixPersp[5] = scale;
    projectionMatrixPersp[10] = -settings.farPlane / (settings.farPlane - settings.nearPlane);
    projectionMatrixPersp[14] = -settings.farPlane * settings.nearPlane / (settings.farPlane - settings.nearPlane);
    projectionMatrixPersp[11] = -1;

    Shaders::projMatOrthoBuf = new cl::Buffer(GetInstance()->c, CL_MEM_READ_ONLY, sizeof(double)*16);
    Shaders::projMatPerspBuf = new cl::Buffer(GetInstance()->c, CL_MEM_READ_ONLY, sizeof(double)*16);
    GetInstance()->q.enqueueWriteBuffer(Shaders::projMatOrthoBuf, CL_TRUE, 0, sizeof(double)*16, projectionMatrixOrtho);
    GetInstance()->q.enqueueWriteBuffer(Shaders::projMatPerspBuf, CL_TRUE, 0, sizeof(double)*16, projectionMatrixPersp);
    delete[] projectionMatrixOrtho;
    delete[] projectionMatrixPersp;
}
cl::CommandQueue* Rendering::CLManager::getQueue() {
    return GetInstance()->q;
}
void Rendering::CLManager::killCL() {
    delete Shaders::projMatOrthoBuf;
    delete Shaders::projMatPerspBuf;
    if (instance) {
        delete instance;
    }
}

void Rendering::CLManager::initKernels() {
    addKernel("VertexShader", Shaders::getVertexShader());
    addKernel("PrimitiveAssembly", Shaders::getPrimitiveAssembly());
    addKernel("Rasterization", Shaders::getRasterization());
    addKernel("GBufferShader", Shaders::getGBufferShader());
    addKernel("LightingShader", Shaders::getLightingShader());
    addKernel("DepthShader", Shaders::getDepthShader());
    addKernel("CompositionShader", Shaders::getCompositionShader());
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
