#include <cmath>
#include <stdexcept>
#include "circle.hpp"
double tampio::Circle::getArea() const
{
  return M_PI * rad_ * rad_;
}
void tampio::Circle::scaleParameters(double factor)
{
  point_t center = getFrameRect().pos;
  rad_ *= factor;
  center_ = center_ + (center_ - center) * factor;
}
tampio::Circle::Circle(double rad, const point_t &center)
{
  if (rad <= 0)
  {
    throw std::logic_error("Circle radius must be bigger than 0");
  }
  rad_ = rad;
  center_ = center;
}

tampio::rectangle_t tampio::Circle::getFrameRect() const
{
  return rectangle_t{rad_ * 2, rad_ * 2, center_};
}

void tampio::Circle::move(const point_t &p)
{
  center_ = p;
}
