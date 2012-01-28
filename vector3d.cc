#include "vector3d.hh"

// Unary minus
Vector3D Vector3D::operator-() {
    return Vector3D(-x, -y, -z);
}

// Scalar multiplication
Vector3D operator*(double c, Vector3D w) {
    return Vector3D(c * w.x, c * w.y, c * w.z);
}

Vector3D operator*(Vector3D w, double c) {
    return c * w;
}

// Scalar division
Vector3D operator/(Vector3D w, double c) {
    return Vector3D(w.x / c, w.y / c, w.z / c);
}

Vector3D Vector3D::operator+(Vector3D w) {
    return Vector3D(x + w.x, y + w.y, z + w.z);
}

Vector3D Vector3D::operator-(Vector3D w) const {
    return Vector3D(x - w.x, y - w.y, z - w.z);
}

// Inner Dot Product
double Vector3D::operator*(Vector3D w) {
    return (x * w.x + y * w.y + z * w.z);
}

// Shorthand Operations
Vector3D& Vector3D::operator*=(double c) {
    x *= c; y *= c; z *= c;
    return *this;
}

Vector3D& Vector3D::operator/=(double c) {
    x /= c; y /= c; z /= c;
    return *this;
}

Vector3D& Vector3D::operator+=(Vector3D w) {
    x += w.x; y += w.y; z += w.z;
    return *this;
}

Vector3D& Vector3D::operator-=(Vector3D w) {
    x -= w.x; y -= w.y; z -= w.z;
    return *this;
}

// Special Operations
void Vector3D::normalize() {
    double l = this->len();
    if (l == 0) return;
    x /= l; y /= l; z /= l;
}
