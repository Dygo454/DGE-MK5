#ifndef WINDOW_EVENT_LISTENER_H
#define WINDOW_EVENT_LISTENER_H

#include"WindowEvent.h"

namespace OS {
    class WindowEventListener {
    public:
        virtual bool recieveEvent(WindowEvent e) = 0;
    };
    class GeneralWindowEventListener : public WindowEventListener {
    private:
        bool (*listenerFunc)(WindowEvent) = NULL;
    public:
        GeneralWindowEventListener(bool (*listenerFunc)(WindowEvent)) {
            this->listenerFunc = listenerFunc;
        }
        bool recieveEvent(WindowEvent e) {
            return listenerFunc(e);
        }
    };
}

#endif
