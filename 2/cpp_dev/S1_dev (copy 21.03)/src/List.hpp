#ifndef LIST_H
#define LIST_H

#include <iostream>

template <class T>
class List;

template <class T>
inline std::ostream &operator<<(std::ostream &, const List<T> &);

template <class T>
class List
{
public:
    List();
    List(const List &);
    List(List &&) noexcept;
    virtual ~List();
    List &operator=(const List &);
    List &operator=(List &&) noexcept;

    void pushBack(T);
    void pushFront(T);
    T dropBack();
    T dropFront();

    T top() const;
    T bottom() const;

    bool isEmpty() const noexcept;

    template <class U>
    friend std::ostream &operator<<(std::ostream &is, const List<U> &list);

private:
    struct node_t
    {
        T data;
        node_t *next;
    };

    void swap(List &) noexcept;

    node_t *head_;
    node_t *tail_;
};

template <class T>
void List<T>::pushBack(T d)
{
    node_t *newNode = new node_t;
    newNode->data = d;
    newNode->next = head_;
    head_ = newNode;
};
template <class T>
void List<T>::pushFront(T d)
{

    if (!head_)
    {
        head_ = tail_ = new node_t;
    }
    else
    {
        tail_->next = new node_t;
        tail_ = tail_->next;
    }
    tail_->data = d;
    tail_->next = nullptr;
};
template <class T>
T List<T>::dropBack()
{
    // untested
    if (!head_)
    {
        throw std::logic_error("Queue is empty");
    }
    int res = head_->data;
    node_t *temp = head_;
    if (head_ == tail_)
    {
        head_ = tail_ = nullptr;
    }
    else
    {
        head_ = head_->next;
    }
    delete temp;
    return res;
};
template <class T>
T List<T>::dropFront()
{
    if (!head_)
    {
        throw std::logic_error("List is empty (underflow)");
    }
    T res = head_->data;
    node_t *temp = head_;
    if (head_ == tail_)
    {
        head_ = tail_ = nullptr;
    }
    else
    {
        head_ = head_->next;
    }
    delete temp;
    return res;
};

template <class T>
T List<T>::top() const
{
    return head_->data;
};
template <class T>
T List<T>::bottom() const
{
    return tail_->data;
};

template <class T>
List<T>::List() : head_(nullptr),
                  tail_(nullptr)
{
}

template <class T>
List<T>::List(const List &list) : head_(nullptr),
                                  tail_(nullptr)
{
    List<T> temp;
    node_t *src = list.head_;
    while (src)
    {
        temp.pushFront(src->data);
        src = src->next;
    }
    swap(temp);
}

template <class T>
List<T>::List(List &&list) noexcept : head_(nullptr),
                                      tail_(nullptr)
{
    swap(list);
}

template <class T>
List<T>::~List()
{
    while (head_)
    {
        node_t *temp = head_;
        head_ = head_->next;
        delete temp;
    }
}

template <class T>
List<T> &List<T>::operator=(const List &list)
{
    if (this == &list)
    {
        return *this;
    }

    List<T> tempList(list);
    swap(tempList);

    return *this;
}

template <class T>
List<T> &List<T>::operator=(List &&list) noexcept
{
    swap(list);
    return *this;
}

template <class T>
bool List<T>::isEmpty() const noexcept
{
    return !head_;
}

template <class T>
void List<T>::swap(List &list) noexcept
{
    std::swap(head_, list.head_);
}

// template <class T>
// std::ostream &operator<<(std::ostream &is, const List<T> &list)
// {
//     list->node_t *temp = list->head_;
//     if (temp)
//     {
//         is << temp->data;
//         temp = temp->next;
//     }
//     while (temp)
//     {
//         is << " " << temp->data;
//         temp = temp->next;
//     }
//     return is;
// }

#endif
