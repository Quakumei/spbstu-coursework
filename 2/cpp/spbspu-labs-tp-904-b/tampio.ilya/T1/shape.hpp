#ifndef SHAPE_H
#define SHAPE_H

#include <ostream>
#include "base-types.hpp"

namespace tampio
{
  class Shape
  {
  public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &p) = 0;
    virtual void move(double dx, double dy);
    virtual void scale(double factor);

  protected:
    virtual void scaleParameters(double factor) = 0;
  };
}
#endif
