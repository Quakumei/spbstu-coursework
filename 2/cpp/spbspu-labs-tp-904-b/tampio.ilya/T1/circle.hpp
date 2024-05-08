#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"

namespace tampio
{
  class Circle : public Shape
  {
  public:
    Circle(double rad, const point_t &center);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(const point_t &p);

  private:
    double rad_;
    point_t center_;
    void scaleParameters(double factor);
  };

}

#endif
