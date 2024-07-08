#include"OS.h"
#include"OSWindowSettings.h"
#include"WindowEventListener.h"

OS::WindowSettings OS::WindowSettings::defaultSettings = {
    .className = "UntitledGamClass",
    .windowName = "UntitledGam",
    .x = CW_USEDEFAULT,
    .y = CW_USEDEFAULT,
    .width = CW_USEDEFAULT,
    .height = CW_USEDEFAULT,
    .windowStyles = 0,
    .optionalStyles = WS_OVERLAPPEDWINDOW
};

#if OS_ID == 0
OS::Windows* OS::Windows::singleton = NULL;
#elif OS_ID == 1
OS::MacOSX* OS::MacOSX::singleton = NULL;
#elif OS_ID == 2
OS::Unix* OS::Unix::singleton = NULL;
#else
Error::SendError("OS was not determined at compile!");
#endif
