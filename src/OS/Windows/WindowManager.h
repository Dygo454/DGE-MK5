#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include<Windows.h>
#include"../../Error/error.h"

#include<iostream>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace OS {
    class Windows{
    private:
        WNDCLASS* wc;
        HWND* hwnd;

        WindowEvent current;
        WindowEventListener* listener = NULL;

        static Windows* singleton;
        static Windows* GetInstance() {
            if (singleton) {
                return singleton;
            }
            Error::SendError("Window not initiallized!", -100);
        }
        Windows(WindowSettings set) {
            WNDCLASS wc = {};
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = GetModuleHandle(NULL);
            wc.lpszClassName = set.className.c_str();
            RegisterClass(&wc);
            this->wc = &wc;


            HWND hwnd = CreateWindowEx(
                set.optionalStyles,
                set.className.c_str(),
                set.windowName.c_str(),
                set.windowStyles,
                set.x, set.y, set.width, set.height,
                NULL,
                NULL,
                GetModuleHandle(NULL),
                NULL
            );
            if (hwnd == NULL) {
                Error::SendError("Error while opening window!", -102);
            }
            ShowWindow(hwnd, SW_SHOW);
            this->hwnd = &hwnd;
        }
    public:
        static void initWindow(WindowSettings set) {
            if (singleton) {
                Error::SendError("Cannot initiallize window twice!", -101);
            }
            singleton = new OS::Windows(set);
        }
        static void killWindow() {
            if (singleton) {
                delete singleton;
                singleton = NULL;
            }
        }
        static void writeScreen(unsigned int* screen, int size) {
        }
        static bool pollEvent(WindowEvent& e) {
            MSG msg = {};
            if (GetMessage(&msg, NULL, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                e = GetInstance()->current;
                return true;
            }
            return false;
        }
        static void registerListener(WindowEventListener* listener) {
            GetInstance()->listener = listener;
        }
    };
}

#endif
