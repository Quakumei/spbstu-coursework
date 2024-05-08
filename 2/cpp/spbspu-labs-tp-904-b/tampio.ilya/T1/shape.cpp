#include <stdexcept>
#include "shape.hpp"
#include "rectangle.hpp"

void tampio::Shape::move(double dx, double dy)
{
  move(getFrameRect().pos + point_t{dx, dy});
}

void tampio::Shape::scale(double factor)
{
  if (factor < 0)
  {
    throw std::logic_error("Scale factor must be positive.");
  }
  scaleParameters(factor);
}
