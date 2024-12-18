#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include<Windows.h>
#include<string>
#include<CL/cl.hpp>
#include<unordered_map>
#include"../../Error/error.h"
#include"../../Input/KeyCodes.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace OS {
    class Windows{
    private:
        WNDCLASS wc;
        HWND hwnd;
        HDC hdc;
        void* bitmapMemory;

        int bitmapWidth;
        int bitmapHeight;
        int clientWidth;
        int clientHeight;
        BITMAPINFO bitmapInfo;

        WindowEvent current;
        WindowEventListener* listener = NULL;

        static Windows* singleton;
        static std::unordered_map<u8,u8>* translator;
        static Windows* GetInstance() {
            if (singleton) {
                return singleton;
            }
            Error::SendError("Window not initiallized!", ERR_NULL_WINDOW);
            return NULL;
        }
        Windows(WindowSettings set) {
            wc = {};
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = GetModuleHandle(NULL);
            wc.lpszClassName = set.className.c_str();
            RegisterClass(&wc);


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
                unsigned int error = GetLastError();
                Error::SendError("Error while opening window! Error code: "+std::to_string(error)+".", ERR_HWND_CREATE);
            }
            ShowWindow(hwnd, SW_SHOW);
            this->hwnd = hwnd;

            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            clientWidth = clientRect.right - clientRect.left;
            clientHeight = clientRect.bottom - clientRect.top;
            bitmapWidth = clientWidth;
            bitmapHeight = clientHeight;
            bitmapMemory = VirtualAlloc(0,bitmapWidth*bitmapHeight*4,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
            bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
            bitmapInfo.bmiHeader.biWidth = bitmapWidth;
            bitmapInfo.bmiHeader.biHeight = -bitmapHeight;
            bitmapInfo.bmiHeader.biPlanes = 1;
            bitmapInfo.bmiHeader.biBitCount = 32;
            bitmapInfo.bmiHeader.biCompression = BI_RGB;
            hdc = GetDC(hwnd);
            writeBuffer();
        }
        ~Windows() {
            ReleaseDC(hwnd, hdc);
            DestroyWindow(hwnd);
            VirtualFree(bitmapMemory, 0, MEM_RELEASE);
        }
        void writeBuffer() {
            StretchDIBits(hdc, 0, 0, bitmapWidth, bitmapHeight, 0, 0, clientWidth, clientHeight, bitmapMemory, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
        }
    public:
        static void setCurrentEvent(WindowEvent e) {
            GetInstance()->current = e;
            GetInstance()->listener->recieveEvent(e);
        }
        static u8 translateKeyID(u8 id) {
            std::unordered_map<u8,u8>::const_iterator got = translator->find(id);
            if (got == translator->end()) {
                return IN_UNDEFINED;
            }
            return got->second;
        }
        static void populateMap();

        static void initWindow(WindowSettings set) {
            if (singleton) {
                Error::SendError("Cannot initiallize window twice!", ERR_DUPLICATE_W);
            }
            singleton = new OS::Windows(set);
            populateMap();
        }
        static void killWindow() {
            if (singleton) {
                delete singleton;
                singleton = NULL;
            }
            delete translator;
            translator = NULL;
        }
        static void writeScreen(cl::Buffer* buffer, cl::CommandQueue& q) {
            Windows& instance = *GetInstance();
            q.enqueueReadBuffer(*buffer,CL_TRUE,0,instance.bitmapWidth*instance.bitmapHeight*4,instance.bitmapMemory);
            cl_int error = q.finish();
            if (error != CL_SUCCESS) {
                Error::SendError("Error synchronyzing queue! Error code: "+std::to_string((int)error)+".", ERR_WRITING_BUF);
            }
        }
        static bool pollEvent() {
            MSG msg = {};
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
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
