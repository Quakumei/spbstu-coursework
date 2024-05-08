#include <cmath>
#include <stdexcept>
#include "ellipse.hpp"

double tampio::Ellipse::getArea() const
{
  return M_PI * radx_ * rady_;
}
void tampio::Ellipse::scaleParameters(double factor)
{
  point_t center = getFrameRect().pos;
  radx_ *= factor;
  rady_ *= factor;
  center_ = center_ + (center_ - center) * factor;
}
tampio::Ellipse::Ellipse(double rady, double radx, const point_t &center)
{
  if (radx <= 0 || rady <= 0)
  {
    throw std::logic_error("Ellipse radiuses must be bigger than 0");
  }
  radx_ = radx;
  rady_ = rady;
  center_ = center;
}

tampio::rectangle_t tampio::Ellipse::getFrameRect() const
{
  return rectangle_t{radx_ * 2, rady_ * 2, center_};
}

void tampio::Ellipse::move(const point_t &p)
{
  center_ = p;
}
