#include"OS.h"
#include"WindowEventListener.h"

OS::WindowSettings OS::WindowSettings::defaultSettings = {
    .className = "UntitledGamClass",
    .windowName = "UntitledGam",
    .x = CW_USEDEFAULT,
    .y = CW_USEDEFAULT,
    .width = CW_USEDEFAULT,
    .height = CW_USEDEFAULT,
    .windowStyles = WS_OVERLAPPEDWINDOW,
    .optionalStyles = 0
};

bool OS::WindowEvent::running = true;

#if OS_ID == 0
OS::Windows* OS::Windows::singleton = NULL;
std::unordered_map<u8,u8>* OS::Windows::translator = NULL;
#elif OS_ID == 1
OS::MacOSX* OS::MacOSX::singleton = NULL;
#elif OS_ID == 2
OS::Unix* OS::Unix::singleton = NULL;
#else
Error::SendError("OS was not determined at compile!");
#endif
