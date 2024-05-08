#ifndef SHAPE_COLLECTION_HPP
#define SHAPE_COLLECTION_HPP

#include <iostream>
#include <memory>
#include <stdexcept>
#include "base-types.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
namespace tampio
{

  template< class T = std::shared_ptr< tampio::Shape > >
  class ShapeCollection
  {
  public:
    ShapeCollection();
    template< class U >
    friend std::ostream& operator<<(std::ostream&, const ShapeCollection< U >&);
    void appendElement(const T&);
    void scale(const point_t& center, double factor);
    bool isEmpty() const;

  private:
    const double EXTEND_FACTOR = 1.618;
    std::size_t size_;
    std::size_t capacity_;
    std::shared_ptr< T[] > data_;
    const T& operator[](std::size_t i) const;
    T& operator[](std::size_t i);

    double getTotalArea() const;
  };

  template< class T >
  std::ostream& operator<<(std::ostream& os, const ShapeCollection< T >& sc)
  {
    os << sc.getTotalArea();
    for (std::size_t i = 0; i < sc.size_; i++)
    {
      os << " ";
      os << Rectangle(sc.data_[i]->getFrameRect());
    }
    return os;
  }
}

template< class T >
bool tampio::ShapeCollection< T >::isEmpty() const
{
  return size_ == 0;
}

template< class T >
void tampio::ShapeCollection< T >::scale(const point_t& center, double factor)
{
  if (factor < 0)
  {
    throw std::logic_error("Scale factor must be positive");
  }
  for (std::size_t i = 0; i < size_; i++)
  {
    data_[i]->scale(factor);
    point_t center_ = data_[i]->getFrameRect().pos;
    data_[i]->move(center_ + (center_ - center) * factor / 2);
  }
}

template< class T >
double tampio::ShapeCollection< T >::getTotalArea() const
{
  double res = 0;
  for (std::size_t i = 0; i < this->size_; i++)
  {
    res += this->data_[i]->getArea();
  }
  return res;
}

template< class T >
tampio::ShapeCollection< T >::ShapeCollection() :
    size_(0),
    capacity_(1),
    data_(new T[1])
{}

template< class T >
void tampio::ShapeCollection< T >::appendElement(const T& elem)
{
  if (size_ == capacity_)
  {
    std::shared_ptr< T[] > temp(new T[static_cast< int >(capacity_ * EXTEND_FACTOR) + 1]);
    for (std::size_t i = 0; i < size_; i++)
    {
      temp[i] = data_[i];
    }
    data_.swap(temp);
    capacity_ = static_cast< int >(capacity_ * EXTEND_FACTOR) + 1;
  }
  data_[size_] = elem;
  ++size_;
}

template< class T >
const T& tampio::ShapeCollection< T >::operator[](std::size_t idx) const
{
  if (idx >= size_)
  {
    throw std::out_of_range("ShapeCollection");
  }
  return data_[idx];
}

template< class T >
T& tampio::ShapeCollection< T >::operator[](std::size_t idx)
{
  if (idx >= size_)
  {
    throw std::out_of_range("ShapeCollection");
  }
  return data_[idx];
}

#endif
