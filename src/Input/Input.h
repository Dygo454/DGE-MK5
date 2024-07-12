#ifndef INPUT_H
#define INPUT_H

#include<unordered_map>
#include<vector>
#include"../OS/OS.h"
#include"KeyCodes.h"

#define INPUT_ARR_SIZE 255

#define ERR__NULL_INPUT -200
#define ERR_NONALPHANUM -201

bool recieveInput(OS::WindowEvent e);

namespace Input {
    class InputManager {
    private:
        bool* currInputs;
        bool* oldInputs;
        std::unordered_map<OS::WindowEvent::Type, std::vector<bool (*)(OS::WindowEvent)>> onNexts;

        static InputManager* singleton;

        void newInputs() {
            bool* temp = currInputs;
            currInputs = oldInputs;
            oldInputs = temp;
            for (int i = 0; i < INPUT_ARR_SIZE; i++) {
                currInputs[i] = oldInputs[i];
            }
        }
        OS::GeneralWindowEventListener* inputListener = 0;

        InputManager() {
            inputListener = new OS::GeneralWindowEventListener(&recieveInput);
            currInputs = new bool[INPUT_ARR_SIZE];
            oldInputs = new bool[INPUT_ARR_SIZE];
        }
        ~InputManager() {
            delete inputListener;
            delete currInputs;
            delete oldInputs;
        }

        static InputManager* GetInstance() {
            if (singleton) {
                return singleton;
            }
            return singleton = new InputManager;
        }
    public:
        static bool recieveInput(OS::WindowEvent e) {
            bool processed = false;
            if (e.getType() == OS::WindowEvent::Type::KeyUp || e.getType() == OS::WindowEvent::Type::KeyDown) {
                bool old = GetInstance()->currInputs[e.getID()];
                GetInstance()->currInputs[e.getID()] = (e.getType() == OS::WindowEvent::Type::KeyDown);
                if (GetInstance()->currInputs[e.getID()] == old) {
                    return true;
                }
                processed = true;
            }
            GetInstance()->onNexts.emplace(e.getType(), std::vector<bool (*)(OS::WindowEvent)>(0));
            int size = GetInstance()->onNexts[e.getType()].size();
            for (int i = 0; i < size; i++) {
                bool (*onNext)(OS::WindowEvent) = GetInstance()->onNexts[e.getType()][0];
                processed = onNext(e) || processed;
                GetInstance()->onNexts[e.getType()].erase(GetInstance()->onNexts[e.getType()].begin());
            }
            return processed;
        }
        static void getNextEvent(bool (*onNext)(OS::WindowEvent), OS::WindowEvent::Type type) {
            GetInstance()->onNexts.emplace(type, std::vector<bool (*)(OS::WindowEvent)>(0));
            GetInstance()->onNexts[type].push_back(onNext);
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
        static bool GetKey(u8 id) {
            return GetInstance()->currInputs[id];
        }
        static bool GetKeyDown(u8 id) {
            return GetInstance()->currInputs[id] && !GetInstance()->oldInputs[id];
        }
        static bool GetKeyUp(u8 id) {
            return !GetInstance()->currInputs[id] && GetInstance()->oldInputs[id];
        }
    };
}

#endif
