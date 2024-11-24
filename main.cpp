#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include"src/Time/GameTime.h"
#include"src/Error/error.h"
#include"src/OS/OS.h"
#include"src/Input/Input.h"
#include"src/Rendering/CLManagement/CLManager.h"
#include"src/Rendering/RendPipeline/RendPipeline.h"
using namespace std;

void cleanUp(int id) {
    Rendering::RendPipeline::killDefault();
    Rendering::CLManager::killTextureBuffers();
    Rendering::CLManager::killKernels();
    Rendering::CLManager::killCL();
    Input::InputManager::killInput();
    kill_window();
    Time::GameTime::killTime();
    exit(id);
}

void setUp() {
    Error::attatchCleanUp(cleanUp);
    Time::GameTime::initTime(0);
    OS::WindowSettings set = OS::WindowSettings::defaultSettings;
    init_window(set);
    Input::InputManager::initializeInput();
    Rendering::CLManager::initCL();
    Rendering::CLManager::initKernels();
    Rendering::RendPipeline::initDefault(Rendering::CLManager::getQueue());
}

int main(int argc, char* argv[]) {
    setUp();

    while (OS::WindowEvent::running) {
        Time::GameTime::tickTime();
        while (poll_window_event()) {
        }
    }
    cleanUp(0);
    return 0;
}
