#ifndef GUARD_vector_hh
#define GUARD_vector_hh

struct Vector3D {
    // Properties
    double x, y, z;

    // Constructors
    Vector3D(Vector3D v) : x(v.x), y(v.y), z(v.z) {}
    Vector3D(double _x, double _y, double _z) :
            x(_x), y(_y), z(_z) {};
    ~Vector3D() {};

    // Vector3D Unary Operations
    Vector3D operator-();

    // Scalar Multiplication
    friend Vector3D operator*(int, Vector3D);
    friend Vector3D operator*(double, Vector3D);
    friend Vector3D operator*(Vector3D, int);
    friend Vector3D operator*(Vector3D, double);
    // Scalar Division
    friend Vector3D operator/(Vector3D, int);
    friend Vector3D operator/(Vector3D, double);

    // Vector3D Arithmetic Operations
    Vector3D operator+(Vector3D);    // vector add
    Vector3D operator-(Vector3D);    // vector subtract
    double operator*(Vector3D);    // inner dot product

    Vector3D& operator*=(double);      // vector scalar mult
    Vector3D& operator/=(double);      // vector scalar div

    // Comparison
    int operator==(Point);
    int operator!=(Point);
    
    // Point Relations
    friend double d(Point, Point);         // Distance
    friend double d2(Point, Point);        // Distance^2

    // Vector3D Properties
    double len() {
        return sqrt(x*x + y*y + z*z);
    }
    double len2() {
        return (x*x + y*y + z*z);
    }

    // Input/Output streams
    friend istream& operator>>(istream&, Point&);
    friend ostream& operator<<(ostream&, Point);

    // Special Operations
    void normalize();
};

#endif GUARD_vector_hh
