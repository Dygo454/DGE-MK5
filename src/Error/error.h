#ifndef ERROR_H
#define ERROR_H

#include<string>

namespace Error {
    void attatchCleanUp(void (*func)(int));
    void SendError(std::string errMsg, int exitID = -1);
    void SendQuit();
}

#endif
