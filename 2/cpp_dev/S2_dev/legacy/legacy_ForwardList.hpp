#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <ostream>
namespace tampio
{
  template< typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ForwardList(const ForwardList &);
    ForwardList(ForwardList &&) noexcept;
    ~ForwardList();
    ForwardList &operator=(const ForwardList &);
    ForwardList &operator=(ForwardList &&) noexcept;
    friend ostream &operator<<(ostream &os, const ForwardList &dt);

    bool empty() const;
    pushFront(const T &);

  private:
  };
}

#endif
