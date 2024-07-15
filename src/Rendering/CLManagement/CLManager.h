#ifndef CL_MANAGER_H
#define CL_MANAGER_H

#include"../Shaders/DefaultShaders.h"
#include"../../Error/error.h"
#include<CL/cl.hpp>
#include<string>
#include<vector>
#include<unordered_map>

#define ERR__NULL_CL__ -400
#define ERR_DUPLICA_CL -401
#define ERR__INIT_CL__ -402
#define ERR__INIT_KERN -403
#define ERR__INIT_TEXT -404
#define ERR_KERN_NOT_F -405
#define ERR_KERN_COMPI -406
#define ERR_DUPLI_KERN -407
#define ERR_CL_RUNTIME -408
#define ERR_CL_DEL_ORD -409

namespace Rendering {
    class CLManager {
    private:
        cl::Platform* p;
        cl::Device* d;
        cl::Context* c;
        cl::CommandQueue* q;
        std::unordered_map<std::string, cl::Kernel*> kernels;
        std::vector<cl::Buffer*> textures;
        cl::Buffer* textureListBuffer;

        CLManager() {
            std::vector<cl::Platform> all_platforms;
            cl::Platform::get(&all_platforms);
            if (all_platforms.size()==0) {
                Error::SendError("No platforms found. Check OpenCL installation!", ERR__INIT_CL__);
                exit(1);
            }
            cl::Platform defaultPlatform=all_platforms[0];
            p = new cl::Platform(defaultPlatform);
            Error::SendDebug("Using platform: " + p->getInfo<CL_PLATFORM_NAME>());

            std::vector<cl::Device> all_devices;
            p->getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
            if(all_devices.size()==0){
                Error::SendError("No devices found. Check OpenCL installation!", ERR__INIT_CL__);
                exit(1);
            }
            cl::Device defaultDevice=all_devices[0];
            d = new cl::Device(defaultDevice);
            Error::SendDebug("Using device: " + d->getInfo<CL_DEVICE_NAME>());

            c = new cl::Context(*d);

            q = new cl::CommandQueue(*c, *d);
        }
        ~CLManager() {
            if (textures.size() > 0 || kernels.size() > 0) {
                Error::SendError("Deletion order was wrong: should delete kernels and textures before CL!", ERR_CL_DEL_ORD);
            }
            delete p;
            delete d;
            delete c;
            delete q;
            delete textureListBuffer;
        }

        static CLManager* instance;
        static CLManager* GetInstance();
    public:
        static void initCL();
        static cl::CommandQueue* getQueue();
        static void killCL();

        static void initKernels();
        static void addKernel(std::string name, const std::string& source);
        static cl::Kernel* getKernel(std::string name);
        static void killKernels();

        static int addTextureBuffers(void* texture, int size, bool waitForMore = false);
        static void updateTextureBuffers();
        static void killTextureBuffers();
    };
}

/*
std::vector<cl::Platform> all_platforms;
cl::Platform::get(&all_platforms);

if (all_platforms.size()==0) {
    std::cout<<" No platforms found. Check OpenCL installation!\n";
    exit(1);
}
cl::Platform default_platform=all_platforms[0];
std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

// get default device (CPUs, GPUs) of the default platform
std::vector<cl::Device> all_devices;
default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
if(all_devices.size()==0){
    std::cout<<" No devices found. Check OpenCL installation!\n";
    exit(1);
}

// use device[1] because that's a GPU; device[0] is the CPU
cl::Device default_device=all_devices[1];
std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";

// a context is like a "runtime link" to the device and platform;
// i.e. communication is possible
cl::Context context({default_device});

// create the program that we want to execute on the device
cl::Program::Sources sources;

// calculates for each element; C = A + B
std::string kernel_code=
    "   void kernel simple_add(global const int* A, global const int* B, global int* C, "
    "                          global const int* N) {"
    "       int ID, Nthreads, n, ratio, start, stop;"
    ""
    "       ID = get_global_id(0);"
    "       Nthreads = get_global_size(0);"
    "       n = N[0];"
    ""
    "       ratio = (n / Nthreads);"  // number of elements for each thread
    "       start = ratio * ID;"
    "       stop  = ratio * (ID + 1);"
    ""
    "       for (int i=start; i<stop; i++)"
    "           C[i] = A[i] + B[i];"
    "   }";
sources.push_back({kernel_code.c_str(), kernel_code.length()});

cl::Program program(context, sources);
if (program.build({default_device}) != CL_SUCCESS) {
    std::cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
    exit(1);
}

// apparently OpenCL only likes arrays ...
// N holds the number of elements in the vectors we want to add
int N[1] = {100};
int n = N[0];

// create buffers on device (allocate space on GPU)
cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int) * n);
cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int) * n);
cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int) * n);
cl::Buffer buffer_N(context, CL_MEM_READ_ONLY,  sizeof(int));

// create things on here (CPU)
int A[n], B[n];
for (int i=0; i<n; i++) {
    A[i] = i;
    B[i] = n - i - 1;
}
// create a queue (a queue of commands that the GPU will execute)
cl::CommandQueue queue(context, default_device);
*/

#endif
