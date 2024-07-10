#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

namespace OS {
    class WindowEvent{
    public:
        enum Type {
            None,
            KeyDown,
            KeyUp,
        };

    private:
        Type type;
        u8 id;
        int x;
        int y;

    public:
        WindowEvent(Type t = Type::None, u8 id = 0, int x = 0, int y = 0) {
            type = t;
            this->id = id;
            this->x = x;
            this->y = y;
        }
        Type getType() {return type;}
        int getID() {return id;}
        int getX() {return x;}
        int getY() {return y;}
    };
}

#endif
