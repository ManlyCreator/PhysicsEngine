#ifndef MATRIX_H
#define MATRIX_H

#include <AnalogMath/definitions.hpp>
#include <AnalogMath/vector.hpp>
#include <ostream>

namespace AnalogMath {
  class Mat3 {
    public:
      real elements[9];

      inline Mat3() { std::fill(elements, elements + 9, 0.0f); }
      inline Mat3(float diagonal) { 
        std::fill(elements, elements + 9, 0.0f); 
        elements[0] = diagonal;
        elements[4] = diagonal;
        elements[8] = diagonal;
      }

      inline float &operator()(unsigned row, unsigned col) { 
        return elements[row + 3*col];
      };

      inline Mat3 operator+(const Mat3 &m) {
        Mat3 result;

        for (int i = 0; i < 9; i++) {
          result.elements[i] = elements[i] + m.elements[i];
        }

        return result;
      }

      inline Mat3 operator*(const real &s) {
        Mat3 result;

        for (int i = 0; i < 9; i++) {
          result.elements[i] = elements[i] *s;
        }

        return result;
      }

      inline Vec3 operator*(const Vec3 &v) {
        Vec3 result;

        result.x = v.x*elements[0] + v.y*elements[3] + v.z*elements[6];
        result.y = v.x*elements[1] + v.y*elements[4] + v.z*elements[7];
        result.z = v.x*elements[2] + v.y*elements[5] + v.z*elements[8];

        return result;
      }

      inline Mat3 operator*(const Mat3 &m) {
        Mat3 result;

        result.elements[0] = elements[0]*m.elements[0] + elements[3]*m.elements[1] + elements[6]*m.elements[2];
        result.elements[1] = elements[1]*m.elements[0] + elements[4]*m.elements[1] + elements[7]*m.elements[2];
        result.elements[2] = elements[2]*m.elements[0] + elements[5]*m.elements[1] + elements[8]*m.elements[2];

        result.elements[3] = elements[0]*m.elements[3] + elements[3]*m.elements[4] + elements[6]*m.elements[5];
        result.elements[4] = elements[1]*m.elements[3] + elements[4]*m.elements[4] + elements[7]*m.elements[5];
        result.elements[5] = elements[2]*m.elements[3] + elements[5]*m.elements[4] + elements[8]*m.elements[5];

        result.elements[6] = elements[0]*m.elements[6] + elements[3]*m.elements[7] + elements[6]*m.elements[8];
        result.elements[7] = elements[1]*m.elements[6] + elements[4]*m.elements[7] + elements[7]*m.elements[8];
        result.elements[8] = elements[2]*m.elements[6] + elements[5]*m.elements[7] + elements[8]*m.elements[8];

        return result;
      }

      friend std::ostream &operator<<(std::ostream &out, AnalogMath::Mat3 &m);
  };

  inline std::ostream &operator<<(std::ostream &out, AnalogMath::Mat3 &m) {
    out << "[ " << m(0, 0) << ", " << m(0, 1) << ", " << m(0, 2) << " ]\n";
    out << "[ " << m(1, 0) << ", " << m(1, 1) << ", " << m(1, 2) << " ]\n";
    out << "[ " << m(2, 0) << ", " << m(2, 1) << ", " << m(2, 2) << " ]";
    return out;
  }
}


#endif
