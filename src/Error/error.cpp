#include"error.h"


#define error(s)
#define debug(s)


#if DEBUG != 0

#include<iostream>
#undef error
#undef debug
#define error(s) std::cerr << s << std::endl
#define debug(s) std::cout << s << std::endl

#endif

namespace Error {
    void (*cleanUp)(int) = NULL;
    void attatchCleanUp(void (*func)(int)) {
        cleanUp = func;
    }
    void SendError(std::string errMsg, int exitID) {
        error(errMsg);
        if (cleanUp == NULL) {
            error("Clean up method was not attatched!");
            exit(-1);
        }
        cleanUp(exitID);
    }
    void SendDebug(std::string msg) {
        debug(msg);
    }
    void SendQuit() {
        if (cleanUp == NULL) {
            error("Clean up method was not attatched!");
            exit(-1);
        }
        cleanUp(0);
    }
}

#undef error
#undef debug
