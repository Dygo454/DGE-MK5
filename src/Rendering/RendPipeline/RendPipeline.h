#ifndef REND_PIPELINE_H
#define REND_PIPELINE_H

#include"../Camera/CameraSettings.h"
#include"../CLManagement/CLManager.h"
#include<string>
#include<vector>
#include<unordered_map>
#include<CL/cl.hpp>

#define ERR_BUILD_STGE -400
#define ERR_BUILD_PIPE -401
#define ERR_PIPE_PARAM -402
#define ERR_PIPE_RANGE -403

namespace Rendering {
    class Stage {
    private:
        cl::Kernel* k;
        unsigned int* params; // num params, [param_x pipeInd], ...
    public:
        Stage(cl::Kernel* k, unsigned int* params);
        ~Stage();
        cl::Kernel* getKernel();
        const unsigned int* getParams();
    };

    class RendPipeline {
    private:
        cl::CommandQueue* q;
        unsigned int numStages;
        Stage** stages;
        unsigned int* paramInfo; // total size, num params, [param_x offset, param_x size], ...
        unsigned long long* bufferBitmap;
        void* params;

        static RendPipeline* defaultPipe2d;
        static RendPipeline* defaultPipe3d;
    public:
        RendPipeline(cl::CommandQueue* q, unsigned int numStages, Stage* stages, unsigned int* paramInfo);
        ~RendPipeline();
        void passParam(unsigned int paramInd, unsigned int size, void* param);
        void pipe(cl::Buffer* output, const CameraSettings& settings);

        static void initDefault(cl::CommandQueue* q);
        static Rendering::RendPipeline* getDefault2D();
        static Rendering::RendPipeline* getDefault3D();
        static void killDefault();
    };

    class StageFBuilder {
    private:
        cl::CommandQueue* q;
        cl::Kernel* k;
        std::vector<unsigned int> paramInfo;
        unsigned int* data = NULL;
    public:
        StageFBuilder(cl::CommandQueue* q);
        StageFBuilder& withKernel(const std::string& kName);
        StageFBuilder& withParam(unsigned int indexFromPipe, unsigned int size);
        Stage* build();
    };

    class RendPipelineFBuilder {
    private:
        cl::CommandQueue* q;
        std::vector<Stage*> stages;
        unsigned int currTotalSize = 0;
        std::vector<unsigned int> paramInfo;
        std::vector<unsigned long long> bufferBitmap;
    public:
        RendPipelineFBuilder(cl::CommandQueue* q);
        RendPipelineFBuilder& withParam(unsigned int size);
        RendPipelineFBuilder& withStage(Stage* stage);
        RendPipeline* build();
    };
}

#endif
