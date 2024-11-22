#include"RendPipeline.h"
#include"../Shaders/DefaultShaders.h"

Rendering::RendPipeline* Rendering::RendPipeline::defaultPipe2d = 0;
Rendering::RendPipeline* Rendering::RendPipeline::defaultPipe3d = 0;

Rendering::Stage::Stage(cl::Kernel* k, unsigned int* params) : k(k), params(params) {}
Rendering::Stage::~Stage() {
    delete[] params;
}
cl::Kernel* Rendering::Stage::getKernel() {
    return k;
}
const unsigned int* Rendering::Stage::getParams() {
    return params;
}

Rendering::RendPipeline::RendPipeline(cl::CommandQueue* q, unsigned int numStages, Stage* stages, unsigned int* paramInfo, unsigned int* bufferBitmap)
: q(q), numStages(numStages), stages(stages), paramInfo(paramInfo), bufferBitmap(bufferBitmap), params(0) {}
Rendering::RendPipeline::~RendPipeline() {
    for (unsigned int i = 0; i < numStages; ++i) {
        delete stages[i];
    }
    delete[] stages;
    delete[] paramInfo;
    delete[] bufferBitmap;
    if (params) delete[] (char*)params;
}
void Rendering::RendPipeline::passParam(unsigned int paramInd, unsigned int size, void* param) {
    if (!params) {
        params = new char[paramInfo[0]];
    }
    if (paramInfo[1] <= paramInd) {
        Error::SendError("Specified parameter index is out of the expected bounds!", ERR_PIPE_PARAM);
        return;
    }
    if (paramInfo[paramInd*2 + 3] != size) {
        Error::SendError("Specified parameter size is incorrect for the parameter at specified index!", ERR_PIPE_PARAM);
        return;
    }
    for (unsigned int i = 0; i < size; ++i) {
        ((char*)params)[paramInfo[paramInd*2 + 2]+i] = ((char*)param)[i];
    }
}
void Rendering::RendPipeline::pipe(cl::Buffer* output, std::vector<cl::NDRange> offsets, std::vector<cl::NDRange> locals, std::vector<cl::NDRange> globals) {
    if (offsets.size() != numStages || locals.size() != numStages || globals.size() != numStages) {
        Error::SendError("Incorrect number of NDRanges for global/local dimensions!", ERR_PIPE_RANGE);
    }
    for (unsigned int i = 0; i < numStages; ++i) {
        const unsigned int* currParams = stages[i]->getParams();
        for (unsigned int n = 1; n <= currParams[0]; ++n) {
            void* currParam = params + ((size_t)(paramInfo[(currParams[n]+1)*2]));
            if (bufferBitmap[currParams[n]/8] & (0x1 << currParams[n]%8)) stages[i]->getKernel()->setArg(n-1, (cl::Buffer*)currParam);
            else stages[i]->getKernel()->setArg(n-1, (size_t)(paramInfo[currParams[n]*2 + 3]), currParam);
        }
        q->enqueueNDRangeKernel(*k, offsets[i], globals[i], locals[i]);
    }
    q->finish(); // MAKE SURE EVERYTHING HAPPENS SEQUENTIALLY!!! SEE LAST TWO OPTIONAL ARGS IN ENQUEUENDRANGE
    delete[] params;
    params = 0;
}

void Rendering::RendPipeline::initDefault(cl::CommandQueue* q); // TODO: DOOOOO MEEEEEE
Rendering::RendPipeline* Rendering::RendPipeline::getDefault2D() {
    return defaultPipe2d;
}
Rendering::RendPipeline* Rendering::RendPipeline::getDefault3D() {
    return defaultPipe3d;
}
void Rendering::RendPipeline::killDefault() {
    delete defaultPipe2d;
    delete defaultPipe3d;
}

Rendering::StageFBuilder::StageFBuilder(cl::CommandQueue* q) : q(q) {}
Rendering::StageFBuilder& Rendering::StageFBuilder::withKernel(const std::string& kName) {
    if (k) {
        Error::SendError("Specified multiple kernels?", ERR_BUILD_STGE);
    }
    k = Rendering::CLManager::getKernel(kName);
    return *this;
}
Rendering::StageFBuilder& Rendering::StageFBuilder::withParam(unsigned int indexFromPipe) {
    if (!k) {
        Error::SendError("Specified parameter before kernel?", ERR_BUILD_STGE);
    }
    paramInfo.push_back(indexFromPipe);
    return *this;
}
Rendering::Stage* Rendering::StageFBuilder::build() {
    unsigned int* paramInfo = new unsigned int[this->paramInfo.size()+1];
    paramInfo[0] = this->paramInfo.size();
    for (unsigned int i = 0; i < paramInfo[0]; ++i) {
        paramInfo[i+1] = this->paramInfo[i];
    }
    return new Stage(k, paramInfo);
}

Rendering::RendPipelineFBuilder::RendPipelineFBuilder(cl::CommandQueue* q) : q(q);
Rendering::RendPipelineFBuilder& Rendering::RendPipelineFBuilder::withParam(unsigned int size) {
    if (stages.size()) {
        Error::SendError("Specified a new parameter after beginning specifying stages?", ERR_BUILD_PIPE);
    }
    paramInfo.push_back(currTotalSize);
    paramInfo.push_back(size);
    currTotalSize += size;
    return *this;
}
Rendering::RendPipelineFBuilder& Rendering::RendPipelineFBuilder::withBuffer() {
    paramInfo.push_back(currTotalSize);
    paramInfo.push_back(8);
    currTotalSize += 8;
    unsigned int currInd = paramInfo.size()/2 - 1;
    while (bufferBitmap.size() <= currInd/8) bufferBitmap.push_back(0);
    bufferBitmap[currInd/8] |= 0x1 << currInd%8;
    return *this;
}
Rendering::RendPipelineFBuilder& Rendering::RendPipelineFBuilder::withStage(Stage* stage) {
    if (!(stage->getKernel())) {
        Error::SendError("Attempted to make a stage without a kernel!", ERR_BUILD_PIPE);
        return *this;
    }
    const unsigned int* stageParamInfo = stage->getParams();
    for (unsigned int i = 0; i < stageParamInfo[0]; ++i) {
        if (stageParamInfo[i+1] >= params.size()) {
            Error::SendError("Attempted to make a stage with a paramater that has yet to be specified!", ERR_BUILD_PIPE);
            return *this;
        }
    }
    stages.push_back(stage);
    return *this;
}
Rendering::RendPipeline* Rendering::RendPipelineFBuilder::build() {
    Stage** stages = new Stage*[this->stages.size()];
    for (unsigned int i = 0; i < this->stages.size(); ++i) {
        stages[i] = this->stages[i];
    }
    unsigned long long* bufferBitmap = new unsigned long long[this->bufferBitmap.size()];
    for (unsigned int i = 0; i < this->bufferBitmap.size(); ++i) {
        bufferBitmap[i] = this->bufferBitmap[i];
    }
    unsigned int* paramInfo = new unsigned int[this->paramInfo.size()+2];
    paramInfo[0] = currTotalSize;
    paramInfo[1] = this->paramInfo.size()/2;
    for (unsigned int i = 0; i < this->paramInfo.size(); ++i) {
        paramInfo[i+2] = this->paramInfo[i];
    }
    return new RendPipeline(q, this->stages.size(), stages, paramInfo, bufferBitmap);
}
