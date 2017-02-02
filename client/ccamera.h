#ifndef CCAMERA_H
#define CCAMERA_H

#include "utility.h"

class CCamera {
public:
    CCamera();
    Math::CBoundingFrustum frustum() const;
    QVector3D position() const;
};

#endif // CCAMERA_H
