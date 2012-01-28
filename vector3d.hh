#ifndef GUARD_vector3d_hh
#define GUARD_vector3d_hh

#include <iostream>
#include <sstream>

template <class T> struct Vector3D {
    T x, y, z;

    Vector3D(T _x, T _y, T _z) :
	    x(_x), y(_y), z(_z) {}
    Vector3D() : x(0), y(0), z(0) {}

    std::string str(void) {
        std::ostringstream s;
        s << "(" << this->x << "," << this->y << "," << this->z << ")";
        return s.str();
    }

    T abs2(void) {
        return x*x + y*y + z*z;
    }

    T abs(void) {
        return sqrt(this->abs2());
    }

    Vector3D operator+(const Vector3D& v) {
        return Vector3D(
                x + v.x,
                y + v.y,
                z + v.z);
    }

    Vector3D operator +=(Vector3D v) {
        *this = *this + v;
        return *this;
    }

    Vector3D operator -(Vector3D v) {
        return Vector3D(
                x - v.x,
                y - v.y,
                z - v.z);
    }

    Vector3D operator -(void) {
        return Vector3D(-x, -y, -z);
    }

    Vector3D operator -=(Vector3D v) {
        *this = *this - v;
        return *this;
    }

    // Scalar multiplication
    Vector3D operator *(T k) {
        return Vector3D(x * k,
                y * k,
                z * k);
    }

    // Dot product
    T operator *(Vector3D v) {
        return x * v.x +
                y * v.y +
                z * v.z;
    }

    bool operator ==(Vector3D v) {
        return x == v.x &&
                y == v.y &&
                z == v.z;
    }
};

#endif // GUARD
