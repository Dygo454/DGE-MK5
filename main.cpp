#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include"src/Time/GameTime.h"
#include"src/Error/error.h"
#include"src/OS/OS.h"
#include"src/Input/Input.h"

#include<iostream>
#include<thread>
using namespace std;

void cleanUp(int id) {
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
