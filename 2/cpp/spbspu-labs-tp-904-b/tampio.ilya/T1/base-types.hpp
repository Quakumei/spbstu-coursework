#ifndef BASETYPES_H
#define BASETYPES_H

namespace tampio
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };

  point_t operator+(point_t const &lhs, point_t const &rhs);
  point_t operator-(point_t const &lhs, point_t const &rhs);
  point_t operator*(point_t const &lhs, double factor);
  point_t operator/(point_t const &lhs, double factor);
}
#endif
