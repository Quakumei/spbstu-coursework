#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <ostream>
#include "shape.hpp"

namespace tampio
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &a, const point_t &b);
    Rectangle(const rectangle_t &rect);
    friend std::ostream &operator<<(std::ostream &os, const Rectangle &obj);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(const point_t &p);

  private:
    point_t a_, b_;
    void scaleParameters(double factor);
  };
  std::ostream &operator<<(std::ostream &os, const tampio::Rectangle &obj);

}

#endif
