
#include "rectangle.hpp"

double tampio::Rectangle::getArea() const
{
  rectangle_t frame = getFrameRect();
  return frame.height * frame.width;
}
void tampio::Rectangle::scaleParameters(double factor)
{
  point_t center = getFrameRect().pos;
  a_ = a_ + (a_ - center) * factor / 2;
  b_ = b_ + (b_ - center) * factor / 2;
}
tampio::Rectangle::Rectangle(const point_t &a, const point_t &b)
{
  if (b.x - a.x < 0 && b.y - a.y < 0)
  {
    throw std::logic_error("Rectangle edges must be placed correctly.");
  }
  a_ = a;
  b_ = b;
}

tampio::Rectangle::Rectangle(const rectangle_t &rect) :
    a_(rect.pos - point_t{rect.width / 2, rect.height / 2}),
    b_(rect.pos + point_t{rect.width / 2, rect.height / 2})
{}

std::ostream &tampio::operator<<(std::ostream &os, const tampio::Rectangle &obj)
{
  os << obj.a_.x << " " << obj.a_.y << " " << obj.b_.x << " " << obj.b_.y;
  return os;
}

tampio::rectangle_t tampio::Rectangle::getFrameRect() const
{
  point_t delta = b_ - a_;
  return rectangle_t{delta.x, delta.y, a_ + delta / 2};
}

void tampio::Rectangle::move(const point_t &p)
{
  point_t delta = b_ - a_;
  a_ = p - delta / 2;
  b_ = p + delta / 2;
}
