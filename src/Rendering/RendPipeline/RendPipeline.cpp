#include"RendPipeline.h"
#include"../Shaders/DefaultShaders.h"

Rendering::RendPipeline* Rendering::RendPipeline::defaultPipe = 0;

void Rendering::RendPipeline::initDefault(cl::CommandQueue* q) {
    // std::vector<Stage> stages(5);
    // stages[0] = Rendering::Stage(Rendering::CLManager::getKernel("VertexShader"), Shaders::doVertexShader);
    // stages[1] = Rendering::Stage(Rendering::CLManager::getKernel("PrimitiveAssembly"), Shaders::doPrimitiveAssembly);
    // stages[2] = Rendering::Stage(Rendering::CLManager::getKernel("DepthShader"), Shaders::doDepthShader);
    // stages[3] = Rendering::Stage(Rendering::CLManager::getKernel("Rasterization"), Shaders::doRasterization);
    // stages[4] = Rendering::Stage(Rendering::CLManager::getKernel("PixelShader"), Shaders::doPixelShader);
    // defaultPipe = new RendPipeline(q,stages);
}
void Rendering::RendPipeline::killDefault() {
    // delete defaultPipe;
}
