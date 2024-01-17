#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <string>


class Vector2D
{
    public:
        float X, Y;

        Vector2D(float x=0, float y=0): X(x), Y(y) {}

        inline Vector2D operator+(const Vector2D& v2)
        const {
            return Vector2D(X + v2.X, Y + v2.Y);
        }

        inline Vector2D operator-(const Vector2D& v2)
        const {
            return Vector2D(X - v2.X, Y - v2.Y);
        }

        inline Vector2D operator*(const float scalar)
        const {
            return Vector2D(X * scalar, Y * scalar);
        }

        inline Vector2D operator*(const Vector2D& v2)
        const {
            return Vector2D(X*v2.X - Y*v2.Y, Y*v2.X + X*v2.Y);
        }

        inline Vector2D operator/(const float scalar)
        const {
            return Vector2D(X / scalar, Y / scalar);
        }

        inline void Log(const std::string& msg = "")
        {
            std::cout << msg << "(X Y) = (" << X << " " << Y << ")" << std::endl;
        }
};

#endif // VECTOR2D_H
