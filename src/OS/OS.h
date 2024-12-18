#ifndef OS_H
#define OS_H

#define ERR_NULL_WINDOW -100
#define ERR_DUPLICATE_W -101
#define ERR_HWND_CREATE -102
#define ERR_WRITING_BUF -103

using u32 = unsigned int;
using u16 = unsigned short;
using u8 = unsigned char;
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
#define poll_window_event() OS::Windows::pollEvent()
#define register_event_listener(n) OS::Windows::registerListener(n)
#endif

#ifdef __APPLE__
#undef OS_ID
#define OS_ID 1
#include"MacOSX/WindowManager.h"
#define init_window(n) OS::MacOSX::initWindow(n)
#define kill_window() OS::MacOSX::killWindow()
#define write_screen(a,b) OS::MacOSX::writeScreen(a,b)
#define poll_window_event() OS::MacOSX::pollEvent()
#define register_event_listener(n) OS::MacOSX::registerListener(n)
#endif

#ifdef __unix__
#undef OS_ID
#define OS_ID 2
#include"Unix/WindowManager.h"
#define init_window(n) OS::Unix::initWindow(n)
#define kill_window() OS::Unix::killWindow()
#define write_screen(a,b) OS::Unix::writeScreen(a,b)
#define poll_window_event() OS::Unix::pollEvent()
#define register_event_listener(n) OS::Unix::registerListener(n)
#endif

#endif
