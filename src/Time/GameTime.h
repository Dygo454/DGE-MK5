#ifndef GAME_TIME_H
#define GAME_TIME_H

#include"../OS/OS.h"

#define ERR__NULL_TIME -300
#define ERR_DUPLI_TIME -301
#define ERR_TIME_OVERF -302

#define TIME_PRECISION 1000000.0

namespace Time {
    class GameTime {
    private:
        double startTime;
        double lastTime;
        double deltaTime = 0;
        u16 maxFps;
        GameTime(double startTime, u16 maxFps = 0) {
            this->startTime = startTime;
            this->lastTime = startTime;
            this->maxFps = maxFps;
        }
        static GameTime* instance;
        static GameTime* GetInstance();
    public:
        static void initTime(u16 maxFrameRate = 0);
        static void tickTime();
        static void killTime();
        static double getDeltaTime();
        static double getCurrentTime();
        static double getElapsedTime(double timePoint);
        static u16 getMaxFps();
    };
}

#endif
