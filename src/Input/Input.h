#ifndef INPUT_H
#define INPUT_H

#include<unordered_map>
#include<vector>
#include"../OS/OS.h"
#include"KeyCodes.h"

#define INPUT_ARR_SIZE 254

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
            GetInstance()->onNexts.emplace(e.getType(), std::vector<bool (*)(OS::WindowEvent)>(0));
            int size = GetInstance()->onNexts[e.getType()].size();
            for (int i = 0; i < size; i++) {
                bool (*onNext)(OS::WindowEvent) = GetInstance()->onNexts[e.getType()][0];
                processed = onNext(e) || processed;
                GetInstance()->onNexts[e.getType()].erase(GetInstance()->onNexts[e.getType()].begin());
            }
            // recieve and store input
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
    };
}

#endif
