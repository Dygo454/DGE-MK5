#include"../OS.h"

#if OS_ID == 0

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
   switch (uMsg) {
       case WM_DESTROY:
           PostQuitMessage(0);
           Error::SendQuit();
       case WM_CLOSE:
           DestroyWindow(hwnd);
           Error::SendQuit();
   }
   // TODO: parse for listener and current
   return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#endif
