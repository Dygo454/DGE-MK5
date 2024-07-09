#include"Input.h"

Input::InputManager* Input::InputManager::singleton = 0;

bool recieveInput(OS::WindowEvent& e) {
    return Input::InputManager::recieveInput(e);
}
