#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.hpp"

namespace tampio
{
  class Ellipse : public Shape
  {
  public:
    Ellipse(double radx, double rady, const point_t &center);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(const point_t &p);

  private:
    double radx_, rady_;
    point_t center_;
    void scaleParameters(double factor);
  };
}

#endif
