#include"RendPipeline.h"
#include"../Shaders/DefaultShaders.h"

std::unordered_map<std::string, cl::Kernel*>* Rendering::Stage::kernels = 0;

void Rendering::Stage::initKernels(cl::CommandQueue* q) {
    kernels = new std::unordered_map<std::string, cl::Kernel*>;
    (*kernels)[std::string("VertexShader")] = Shaders::getVertexShader(q);
    (*kernels)[std::string("PrimitiveAssembly")] = Shaders::getPrimitiveAssembly(q);
    (*kernels)[std::string("Rasterization")] = Shaders::getRasterization(q);
    (*kernels)[std::string("PixelShader")] = Shaders::getPixelShader(q);
    (*kernels)[std::string("DepthShader")] = Shaders::getDepthShader(q);
    (*kernels)[std::string("AlphaBlending")] = Shaders::getAlphaBlending(q);
}
void Rendering::Stage::killKernels() {
    for (std::unordered_map<std::string, cl::Kernel*>::iterator it = kernels->begin(); it != kernels->end(); it++) {
        delete it->second;
    }
    delete kernels;
}
Rendering::RendPipeline* Rendering::RendPipeline::defaultPipe = 0;

void Rendering::RendPipeline::initDefault(cl::CommandQueue* q) {
    Rendering::Stage::initKernels(q);
    std::vector<Stage> stages(6);
    stages[0] = Rendering::Stage((*Rendering::Stage::kernels)[std::string("VertexShader")], Shaders::doVertexShader);
    stages[1] = Rendering::Stage((*Rendering::Stage::kernels)[std::string("PrimitiveAssembly")], Shaders::doPrimitiveAssembly);
    stages[2] = Rendering::Stage((*Rendering::Stage::kernels)[std::string("Rasterization")], Shaders::doRasterization);
    stages[3] = Rendering::Stage((*Rendering::Stage::kernels)[std::string("PixelShader")], Shaders::doPixelShader);
    stages[4] = Rendering::Stage((*Rendering::Stage::kernels)[std::string("DepthShader")], Shaders::doDepthShader);
    stages[5] = Rendering::Stage((*Rendering::Stage::kernels)[std::string("AlphaBlending")], Shaders::doAlphaBlending);
    defaultPipe = new RendPipeline(q,stages);
}
void Rendering::RendPipeline::killDefault() {
    Rendering::Stage::killKernels();
    delete defaultPipe;
}
