#ifndef OS_H
#define OS_H

#include"WindowEvent.h"
#include"WindowSettings.h"
#include"WindowEventListener.h"

#define OS_ID -1

#ifdef _WIN32
#undef OS_ID
#define OS_ID 0
#include"Windows/WindowManager.h"
#define init_window(n) OS::Windows::initWindow(n)
#define kill_window() OS::Windows::killWindow()
#define write_screen(a,b) OS::Windows::writeScreen(a,b)
#define poll_window_event(n) OS::Windows::pollEvent(n)
#define register_event_listener(n) OS::Windows::registerListener(n)
#endif

#ifdef __APPLE__
#undef OS_ID
#define OS_ID 1
#include"MacOSX/WindowManager.h"
#define init_window(n) OS::MacOSX::initWindow(n)
#define kill_window() OS::MacOSX::killWindow()
#define write_screen(a,b) OS::MacOSX::writeScreen(a,b)
#define poll_window_event(n) OS::MacOSX::pollEvent(n)
#define register_event_listener(n) OS::MacOSX::registerListener(n)
#endif

#ifdef __unix__
#undef OS_ID
#define OS_ID 2
#include"Unix/WindowManager.h"
#define init_window(n) OS::Unix::initWindow(n)
#define kill_window() OS::Unix::killWindow()
#define write_screen(a,b) OS::Unix::writeScreen(a,b)
#define poll_window_event(n) OS::Unix::pollEvent(n)
#define register_event_listener(n) OS::Unix::registerListener(n)
#endif

#endif
