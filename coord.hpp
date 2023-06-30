#pragma once
#include <ostream>

namespace mvc {
struct Coord {
  using Position = Coord;
  using Shift = Coord;
  int x;
  int y;
  Position& operator+=(Shift shift) {
    x += shift.x;
    y += shift.y;
    return *this;
  }
  Position& operator-=(Shift shift) {
    x -= shift.x;
    y -= shift.y;
    return *this;
  }
  Shift operator +(Coord rhv) {
    return {x + rhv.x, y + rhv.y};
  }
  Shift operator -(Coord rhv) {
    return {x - rhv.x, y - rhv.y};
  }
};

inline std::ostream& operator<<(std::ostream& stream, Coord xy) {
  stream << "Coordinates{ " << xy.x << ", " << xy.y << " }";
  return stream;
}

}  // namespace mvc
