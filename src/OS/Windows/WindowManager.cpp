#if OS_ID == 0

#include"../OS.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_KEYDOWN:
            OS::Windows::setCurrentEvent(OS::WindowEvent(OS::WindowEvent::Type::KeyDown, OS::Windows::translateKeyID(wParam)));
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void OS::Windows::populateMap() {
    translator = new std::unordered_map<u8,u8>();
    std::unordered_map<u8,u8>& translatorRef = *translator;

    for (int i = 0; i < 26; i++) {
        translatorRef[i+0x41] = IN_A+i;
    }
    for (int i = 0; i < 10; i++) {
        translatorRef[i+0x30] = IN_0+i;
    }
    for (int i = 0; i < 10; i++) {
        translatorRef[i+VK_NUMPAD0] = IN_NUM_0+i;
    }
    for (int i = 0; i < 12; i++) {
        translatorRef[i+VK_F1] = IN_F1+i;
    }
    translatorRef[VK_ESCAPE] = IN_ESC;
    translatorRef[VK_SPACE] = IN_SPACE;
    translatorRef[VK_RETURN] = IN_ENTER;
    translatorRef[VK_LEFT] = IN_LEFT;
    translatorRef[VK_RIGHT] = IN_RIGHT;
    translatorRef[VK_UP] = IN_UP;
    translatorRef[VK_DOWN] = IN_DOWN;
    translatorRef[VK_NUMLOCK] = IN_NUMLOCK;
    translatorRef[VK_SCROLL] = IN_SCROLLLOCK;
    translatorRef[VK_OEM_3] = IN_TILDE;
    translatorRef[VK_TAB] = IN_TAB;
    translatorRef[VK_CAPITAL] = IN_CAPS;
    translatorRef[VK_LSHIFT] = IN_LSHIFT;
    translatorRef[VK_RSHIFT] = IN_RSHIFT;
    translatorRef[VK_LCONTROL] = IN_LCTRL;
    translatorRef[VK_RCONTROL] = IN_RCTRL;
    translatorRef[VK_LMENU] = IN_LALT;
    translatorRef[VK_RMENU] = IN_RALT;
    translatorRef[VK_LWIN] = IN_WIN;
    translatorRef[VK_RWIN] = IN_WIN;
    translatorRef[VK_DELETE] = IN_DEL;
    translatorRef[VK_INSERT] = IN_INSERT;
    translatorRef[VK_BACK] = IN_BACKSPACE;
    translatorRef[VK_OEM_PLUS] = IN_EQUALS;
    translatorRef[VK_OEM_MINUS] = IN_MINUS;
    translatorRef[VK_OEM_4] = IN_OPEN_BRACKET;
    translatorRef[VK_OEM_6] = IN_CLOSE_BRACKET;
    translatorRef[VK_OEM_5] = IN_BACKSLASH;
    translatorRef[VK_OEM_7] = IN_QUOTE;
    translatorRef[VK_OEM_1] = IN_SEMICOLON;
    translatorRef[VK_SNAPSHOT] = IN_PRTSCR;
    translatorRef[VK_HOME] = IN_HOME;
    translatorRef[VK_PRIOR] = IN_PGUP;
    translatorRef[VK_NEXT] = IN_PGDOWN;
    translatorRef[VK_END] = IN_END;
    translatorRef[VK_MEDIA_PLAY_PAUSE] = IN_MEDIA_PLAY_PAUSE;
    translatorRef[VK_MEDIA_STOP] = IN_MEDIA_STOP;
    translatorRef[VK_MEDIA_PREV_TRACK] = IN_MEDIA_PREV;
    translatorRef[VK_MEDIA_NEXT_TRACK] = IN_MEDIA_SKIP;
    translatorRef[VK_VOLUME_MUTE] = IN_MEDIA_MUTE;
    translatorRef[VK_VOLUME_DOWN] = IN_MEDIA_VOL_DOWN;
    translatorRef[VK_VOLUME_UP] = IN_MEDIA_VOL_UP;
    translatorRef[VK_MULTIPLY] = IN_NUM_STAR;
    translatorRef[VK_ADD] = IN_NUM_PLUS;
    translatorRef[VK_SUBTRACT] = IN_NUM_MINUS;
    translatorRef[VK_DIVIDE] = IN_NUM_SLASH;
    translatorRef[VK_DECIMAL] = IN_NUM_DOT;
}

#endif
