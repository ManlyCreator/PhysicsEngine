#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>
#include <AnalogMath/definitions.hpp>

namespace AnalogMath {
  class Vec2 {
    public:
      real x, y;

      inline Vec2() : x(0.0f), y(0.0f) { }
      inline Vec2(real val) : x(val), y(val) { }
      inline Vec2(real xVal, real yVal) : x(xVal), y(yVal)  { }
      inline ~Vec2() { };

      inline real Length() {
        return sqrt(x*x + y*y);
      }
      inline real Dot(Vec2 &v) {
        return x*v.x + y*v.y;
      }
      inline Vec2 Normalized() {
        real length = Length();
        return Vec2(x/length, y/length);
      }
      inline Vec2 operator+(Vec2 &vec) { return Vec2(x + vec.x, y + vec.y); };
      inline Vec2 operator-(Vec2 &vec) { return Vec2(x - vec.x, y - vec.y); };
      inline Vec2 operator*(real val) { return Vec2(x * val, y * val); };

      friend std::ostream &operator<<(std::ostream &out, Vec2 &v);
  };

  class Vec3 {
    public:
      real x, y, z;

      inline Vec3() : x(0.0f), y(0.0f), z(0.0f) { }
      inline Vec3(real val) : x(val), y(val), z(val) { }
      inline Vec3(real xVal, real yVal, real zVal) : x(xVal), y(yVal), z(zVal)  { }
      inline ~Vec3() { };
      inline Vec3 operator+(Vec3 &v) { return Vec3(x + v.x, y + v.y, z + v.z); }

      friend std::ostream &operator<<(std::ostream &out, Vec3 &v);
  };

  template <typename T>
  inline const real *GetValuePtr(T &vec) { return &(vec.x); };

  inline std::ostream &operator<<(std::ostream &out, AnalogMath::Vec2 &v) {
    out << "< " << v.x << ", " << v.y << " >";
    return out;
  }

  inline std::ostream &operator<<(std::ostream &out, AnalogMath::Vec3 &v) {
    out << "< " << v.x << ", " << v.y << ", " << v.z << " >";
    return out;
  }
}

#endif
