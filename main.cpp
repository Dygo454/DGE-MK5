#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include"src/Error/error.h"
#include"src/OS/OS.h"
#include"src/Input/Input.h"

#include<iostream>
#include<string>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<stdint.h>
#include<CL/cl.hpp>
using namespace std;
using namespace cl;

void cleanUp(int id) {
    kill_window();
    Input::InputManager::killInput();
    exit(id);
}

int main(int argc, char* argv[]) {
    Error::attatchCleanUp(cleanUp);
    OS::WindowSettings set = OS::WindowSettings::defaultSettings;
    init_window(set);
    Input::InputManager::initializeInput();

    while (true) {
        OS::WindowEvent e;
        poll_window_event(e);
    }

    cleanUp(0);
}
