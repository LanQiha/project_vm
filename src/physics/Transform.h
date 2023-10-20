#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"


class Transform
{
    public:
        float X, Y;
        Vector2D position;
        Vector2D linearVelocity;
        float angularVelocity;
        float gravityScale;

        Transform(float x=0., float y=0.) : X(x), Y(y) {}

        void Log(std::string msg = "")
        {
            std::cout << msg << "(X Y) = (" << X << " " << Y << ")" << std::endl;
        }
};

#endif // TRANSFORM_H
