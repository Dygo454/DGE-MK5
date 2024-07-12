#ifndef REND_PIPELINE_H
#define REND_PIPELINE_H

#include"../Camera/CameraSettings.h"
#include<string>
#include<vector>
#include<unordered_map>
#include<CL/cl.hpp>

namespace Rendering {
    class Stage {
    private:
        cl::Kernel* k;
        void (*passPtr)(cl::Kernel*, cl::Buffer*&, cl::CommandQueue*, const Rendering::CameraSettings&);
    public:
        Stage() {
            k = 0;
            passPtr = 0;
        }
        Stage(cl::Kernel* k, void (*passPtr)(cl::Kernel*, cl::Buffer*&, cl::CommandQueue*, const Rendering::CameraSettings&)) {
            this->k = k;
            this->passPtr = passPtr;
        }
        void pass(cl::Buffer*& buffer, cl::CommandQueue* q, const Rendering::CameraSettings& settings) {
            passPtr(k, buffer, q, settings);
        }
        static std::unordered_map<std::string, cl::Kernel*>* kernels;
        static void initKernels(cl::CommandQueue* q);
        static void killKernels();
    };

    class RendPipeline {
    private:
        cl::CommandQueue* q;
        std::vector<Stage> stages;
    public:
        RendPipeline(cl::CommandQueue* q, std::vector<Stage>& stages) {
            this->q = q;
            this->stages = stages;
        }
        void pipe(cl::Buffer* buffer, const Rendering::CameraSettings& settings) {
            cl::Buffer* movingPtr = buffer;
            for (Stage stage : stages) {
                stage.pass(movingPtr, q, settings);
            }
        }
        static RendPipeline* defaultPipe;
        static void initDefault(cl::CommandQueue* q);
        static void killDefault();
    };
}

#endif
