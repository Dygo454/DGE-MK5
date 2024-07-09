#ifndef INPUT_H
#define INPUT_H

#include"../OS/OS.h"

#define ERR__NULL_INPUT -200

bool recieveInput(OS::WindowEvent& e);

namespace Input {
    class InputManager {
    private:
        void clearInput() {
            // clear stored input
        }
        OS::GeneralWindowEventListener* inputListener = 0;

        InputManager() {
            inputListener = new OS::GeneralWindowEventListener(&recieveInput);
            //set up input storage
        }
        ~InputManager() {
            delete inputListener;
        }

        static InputManager* singleton;
        static InputManager* GetInstance() {
            if (singleton) {
                return singleton;
            }
            return singleton = new InputManager;
        }
    public:
        static bool recieveInput(OS::WindowEvent& e) {
            // recieve and store input
            return false;
        }
        static void initializeInput() {
            register_event_listener(GetInstance()->inputListener);
        }
        static void killInput() {
            if (singleton) {
                delete singleton;
                singleton = 0;
            }
        }
    };
}

#endif
