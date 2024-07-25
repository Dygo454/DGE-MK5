#ifndef REND_PIPELINE_H
#define REND_PIPELINE_H

#include"../Camera/CameraSettings.h"
#include"../CLManagement/CLManager.h"
#include<string>
#include<vector>
#include<unordered_map>
#include<CL/cl.hpp>

namespace Rendering {
    class Stage {
    private:
        cl::Kernel* k;
        void (*passPtr)(cl::Kernel* ,cl::Buffer*, cl::Buffer*, cl::Buffer*, cl::CommandQueue*, const Rendering::CameraSettings&, cl::Buffer**, cl::Buffer*);
    public:
        Stage() {
            k = 0;
            passPtr = 0;
        }
        Stage(cl::Kernel* k, void (*passPtr)(cl::Kernel* ,cl::Buffer*, cl::Buffer*, cl::Buffer*, cl::CommandQueue*, const Rendering::CameraSettings&, cl::Buffer**, cl::Buffer*)) {
            this->k = k;
            this->passPtr = passPtr;
        }
        void pass(cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffer, cl::CommandQueue* q, const Rendering::CameraSettings& settings, cl::Buffer** passingBuffer, cl::Buffer* outBuffer) {
            passPtr(k, vertexBuffer, assemblyBuffer, textureBuffer, q, settings, passingBuffer, outBuffer);
        }
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
        void pipe(cl::Buffer* vertexBuffer, cl::Buffer* assemblyBuffer, cl::Buffer* textureBuffer, const Rendering::CameraSettings& settings, cl::Buffer* outBuffer) {
            cl::Buffer* passingBuffer = NULL;
            for (Stage stage : stages) {
                stage.pass(vertexBuffer, assemblyBuffer, textureBuffer, q, settings, &passingBuffer, outBuffer);
            }
            if (passingBuffer) {
                delete passingBuffer;
            }
        }
        static RendPipeline* defaultPipe;
        static void initDefault(cl::CommandQueue* q);
        static void killDefault();
    };
}

#endif
