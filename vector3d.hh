#ifndef GUARD_vector_hh
#define GUARD_vector_hh

#include <cmath>
#include <iostream>
#include <sstream>

struct Vector3D {
    // Properties
    double x, y, z;

    // Constructors
    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(double _x, double _y, double _z) :
            x(_x), y(_y), z(_z) {};
    ~Vector3D() {};

    // Vector3D Unary Operations
    Vector3D operator-();

    // Scalar Multiplication
    friend Vector3D operator*(double, Vector3D);
    friend Vector3D operator*(Vector3D, double);
    // Scalar Division
    friend Vector3D operator/(Vector3D, double);

    // Vector3D Arithmetic Operations
    Vector3D operator+(Vector3D);    // vector add
    Vector3D operator-(Vector3D) const;    // vector subtract
    double operator*(Vector3D);    // inner dot product

    Vector3D& operator*=(double);      // vector scalar mult
    Vector3D& operator/=(double);      // vector scalar div

    // Comparison
    int operator==(Vector3D);
    int operator!=(Vector3D);

    // Shorthand Operations
    Vector3D& operator+=(Vector3D);      // vector increment
    Vector3D& operator-=(Vector3D);      // vector decrement
    
    // Vector3D Relations
    friend double d(Vector3D, Vector3D);         // Distance
    friend double d2(Vector3D, Vector3D);        // Distance^2

    // Vector3D Properties
    double len() const {
        return sqrt(x*x + y*y + z*z);
    }
    double len2() const {
        return (x*x + y*y + z*z);
    }
    std::string str() const {
        std::ostringstream os;
        os << "(" << x << "," << y << "," << z << ")";
        return os.str();
    }

    // Input/Output streams
    friend std::ostream& operator<<(std::ostream&, const Vector3D&);

    // Special Operations
    void normalize();
};

// Output stream
std::ostream& operator<<(std::ostream&, const Vector3D&);

#endif
