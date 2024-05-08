#include "base-types.hpp"

tampio::point_t tampio::operator+(tampio::point_t const &lhs, tampio::point_t const &rhs)
{
  return tampio::point_t{lhs.x + rhs.x, lhs.y + rhs.y};
}

tampio::point_t tampio::operator-(tampio::point_t const &lhs, tampio::point_t const &rhs)
{
  return tampio::point_t{lhs.x - rhs.x, lhs.y - rhs.y};
}

tampio::point_t tampio::operator*(tampio::point_t const &lhs, double factor)
{
  return tampio::point_t{lhs.x * factor, lhs.y * factor};
}

tampio::point_t tampio::operator/(tampio::point_t const &lhs, double factor)
{
  return lhs * (1 / factor);
}
