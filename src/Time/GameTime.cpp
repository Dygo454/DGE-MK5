#include"GameTime.h"
#include"../Error/error.h"
#include<time.h>

#define NOW() clock()/(CLOCKS_PER_SEC/TIME_PRECISION)

Time::GameTime* Time::GameTime::instance = 0;

Time::GameTime* Time::GameTime::GetInstance() {
    if (instance == 0) {
        Error::SendError("Time hasn't been initialized!", ERR__NULL_TIME);
    }
    return instance;
}

void Time::GameTime::initTime(u16 maxFrameRate) {
    if (instance != 0) {
        Error::SendError("Time has already been initialized!", ERR_DUPLI_TIME);
    }
    instance = new GameTime(NOW(), maxFrameRate);
}

void Time::GameTime::tickTime() {
    double now;
    do {
        now = NOW();
        GetInstance()->deltaTime = now-GetInstance()->lastTime;
    } while (GetInstance()->maxFps > 0 && GetInstance()->deltaTime < TIME_PRECISION/GetInstance()->maxFps);
    if (now < GetInstance()->lastTime) {
        Error::SendError("Program was open too long. Time overflow!", ERR_TIME_OVERF);
    }
    GetInstance()->lastTime = now;
}

void Time::GameTime::killTime() {
    delete GetInstance();
}

double Time::GameTime::getDeltaTime() {
    return GetInstance()->deltaTime;
}

double Time::GameTime::getCurrentTime() {
    return NOW();
}

double Time::GameTime::getElapsedTime(double timePoint) {
    return NOW()-timePoint;
}

u16 Time::GameTime::getMaxFps() {
    return GetInstance()->maxFps;
}
