#ifndef WINDOW_SETTINGS_H
#define WINDOW_SETTINGS_H

#include<string>

namespace OS {
    struct WindowSettings {
        std::string className;
        std::string windowName;
        unsigned int x;
        unsigned int y;
        unsigned int width;
        unsigned int height;
        unsigned int windowStyles;
        unsigned int optionalStyles;
        static WindowSettings defaultSettings;
    };
}

#endif
