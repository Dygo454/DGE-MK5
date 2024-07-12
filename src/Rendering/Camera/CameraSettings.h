#ifndef CAMERA_SETTINGS_H
#define CAMERA_SETTINGS_H

namespace Rendering {
    struct CameraSettings {
    public:
        unsigned int targetX;
        unsigned int targetY;
        unsigned int nearPlane;
        unsigned int farPlane;
        unsigned int fovY;
        bool orthographic;
        void* targetTexture;
    };
}

#endif
