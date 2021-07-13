// Copyright: GEATEC engineering, 2020
// License: Apache 2

// Nice compiler and hi-res console when zoomed out and nrOfRows == 192: https://www.onlinegdb.com/online_c++_compiler

#include <math.h>
#include <iostream>
#include <vector>

namespace st = std;

class Object;

typedef st::vector <Object*> Objects;

const int nrOfRows = 96;
const int nrOfCols = 3 * nrOfRows;

const int traceDepth = 3;
const int aLot = 1000;

const char *pixelChars = "MNIL+-. ";
                    
struct Vec3D {
    float x, y, z;
    Vec3D (float x, float y, float z): x (x), y (y), z (z) {}
    Vec3D minus () {return Vec3D (-x, -y, -z);}
    Vec3D add (Vec3D other) {return Vec3D (x + other.x, y + other.y, z + other.z);}
    Vec3D sub (Vec3D other) {return Vec3D (x - other.x, y - other.y, z - other.z);}
    Vec3D mul (float scalar) {return Vec3D (x * scalar, y * scalar, z * scalar);}
    Vec3D div (float scalar) {return Vec3D (x / scalar, y / scalar, z / scalar);}
    float norm () {return sqrt (pow (x, 2) + pow (y, 2) + pow (z, 2));}
    Vec3D unit () {auto aNorm = norm (); return Vec3D (x / aNorm, y / aNorm, z / aNorm);}
    float dot (Vec3D other) {return x * other.x + y * other.y + z * other.z;}
    Vec3D cross (Vec3D other) {return Vec3D (y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);}
};

struct Ray {
    Vec3D support;
    Vec3D direction;
    Objects &objects;
    float brightness;
    float tracedDepth;
    Object *currentObject;

    Ray (float xStart, float yStart, Objects &objects):
        support (Vec3D (0, 0, 3)),
        direction (Vec3D (xStart, yStart, 0) .sub (support) .unit ()),
        objects (objects),
        brightness (1),
        tracedDepth (0),
        currentObject (0) {
    }

    void trace ();
};

struct Object {
    Vec3D center;
    Object (float x, float y, float z): center (x, y, z) {}
    virtual bool hit (Ray &ray) = 0;
};

struct Sphere: Object {
    float radius;
    Sphere (float x, float y, float z, float radius): Object (x, y, z), radius (radius) {};

    bool hit (Ray &ray) {
        if (ray.currentObject != this && dist (ray) < radius) {
            if (ray.currentObject && ray.direction.dot (center.sub (ray.currentObject->center)) < 0) {
                return false;
            }

            ray.support = hitPoint (ray);
            ray.brightness *= 0.6;
            auto normal = ray.support.sub (center) .unit ();
            auto radial = normal.mul (ray.direction.dot (normal));
            auto tangential = ray.direction.sub (radial);
            ray.direction = tangential.sub (radial) .unit ();

            ray.currentObject = this;
            return true;
        }
        return false;
    }

    Vec3D hitPoint (Ray &ray) {                                                                 // https://en.wikipedia.org/wiki/Line-sphere_intersection 
        auto blabla = ray.support.sub (center);
        auto nabla = pow (ray.direction.dot (blabla), 2) - pow (blabla.norm (), 2) + pow (radius, 2);
        auto aDist = -ray.direction.dot (blabla) - sqrt (nabla);
        return ray.support.add (ray.direction.mul (aDist));
    }

    float dist (Ray &ray) {return ray.support.sub (center) .cross (ray.direction) .norm ();}    // https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
};

struct Floor: Object {
    float side;
    float stride;
    Vec3D normal;
    Floor (float x, float y, float z, float side, float stride): Object (x, y, z), side (side), stride (stride) , normal (Vec3D (0, 1, 0)) {}

    bool hit (Ray &ray) {
        if (ray.currentObject != this) {
            if (!ray.direction.y || ray.currentObject && ray.direction.dot (center.sub (ray.currentObject->center)) < 0) {
                return false;
            }

            ray.support = hitPoint (ray);

            float xRelAbs = abs (ray.support.x - center.x);
            float zRelAbs = abs (ray.support.z - center.z);
            float halfSide = side / 2;

            if (xRelAbs > halfSide || zRelAbs > halfSide || ray.direction.dot (Vec3D (0, 1, 0)) > 0) {
                return false;
            }

            int xCrude = aLot + ray.support.x / stride;
            int zCrude = aLot + ray.support.z / stride;
            ray.brightness *= ((xCrude % 2 && !(zCrude % 2)) || (!(xCrude % 2) && zCrude % 2) ? 0 : 1);
            auto radial = normal.mul (ray.direction.dot (normal));
            auto tangential = ray.direction.sub (radial);
            ray.direction = tangential.sub (radial) .unit ();
            ray.currentObject = this;
            return true;
        }
        return false;    
    }

    Vec3D hitPoint (Ray &ray) {                                                                 // https://en.wikipedia.org/wiki/Line-plane_intersection
        float aDist = center.sub (ray.support) .dot (normal) / ray.direction.dot (normal);
        return ray.support.add (ray.direction .mul (aDist));
    }
};

struct Raytracer {
    Objects objects = Objects ({
        new Floor (0, -1.2, -2,  20, 0.7),
        new Sphere (-0.4, 0.23, -1, 0.4),
        new Sphere (0.4, 0.4, -1.2, 0.3),
        new Sphere (0.7, -0.15, -1.5, 0.2)
    });

    ~Raytracer () {
        for (auto object: objects) {
            delete object;
        }
    }

    float image [nrOfRows][nrOfCols];

    Raytracer () {
        trace ();
        scale ();
        show ();
    }

    void trace () {
        for (auto rowIndex = 0; rowIndex < nrOfRows; rowIndex++) {
            for (auto colIndex = 0; colIndex < nrOfCols; colIndex++) {
                auto ray = Ray (getX (colIndex), getY (rowIndex), objects);
                ray.trace ();
                image [rowIndex][colIndex] = ray.brightness;
            }
        }
    }

    void scale () {
        float maxBrightness = 0;

        for (auto rowIndex = 0; rowIndex < nrOfRows; rowIndex++) {
            for (auto colIndex = 0; colIndex < nrOfCols; colIndex++) {
                if (image [rowIndex][colIndex] > maxBrightness) {
                    maxBrightness = image [rowIndex][colIndex];
                }
            }
        }

        float scaleFactor = ((sizeof (pixelChars) / sizeof (char)) - 1) / maxBrightness;

        for (auto rowIndex = 0; rowIndex < nrOfRows; rowIndex++) {
            for (auto colIndex = 0; colIndex < nrOfCols; colIndex++) {
                image[rowIndex][colIndex] *= scaleFactor;
            }
        }
    }

    void show () {
        st::cout << '\n';
        for (auto rowIndex = 0; rowIndex < nrOfRows; rowIndex++) {
            st::cout << "                                   ";
            for (auto colIndex = 0; colIndex < nrOfCols; colIndex++) {
                st::cout << pixelChars [int (image [rowIndex][colIndex])];
            }
            st::cout << '\n';
        }
        st::cout << '\n';
    }

    float getX (float colIndex) {return (colIndex - nrOfCols / 2) / (0.65 * nrOfCols);}
    float getY (float rowIndex) {return (nrOfRows - rowIndex - nrOfRows / 2) / nrOfRows;}
};

void Ray::trace () {
    for (auto object: objects) {
        if (object->hit (*this)) {
            if (++tracedDepth < traceDepth) {
                trace ();
            }
            break;
        }
    }
}

int main () {
    Raytracer ();
    return 0;
}
