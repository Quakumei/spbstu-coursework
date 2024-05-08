#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <functional>
#include <utility>
#include "Stack.hpp"

namespace tampio
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BinarySearchTree
  {
  private:
    struct BST_node;

  public:
    struct Iterator;
    struct ConstIterator;

    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree&);
    BinarySearchTree(BinarySearchTree&&) noexcept;
    BinarySearchTree& operator=(const BinarySearchTree& other);
    BinarySearchTree& operator=(BinarySearchTree&& src) noexcept;

    void push(const Key&, const Value&);
    void dropKey(const Key&);
    bool empty() const;

    template< class F >
    F traverse_lnr(F f) const;
    template< class F >
    F traverse_rnl(F f) const;
    template< class F >
    F traverse_breadth(F f) const;

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;

  private:
    BST_node* root_;
    Compare cmp_;
    void swap(BinarySearchTree&) noexcept;

    void treeDelete(BST_node*);
    BST_node* mostLeft(BST_node*);
  };
}

template< typename Key, typename Value, typename Compare >
template< class F >
F tampio::BinarySearchTree< Key, Value, Compare >::traverse_lnr(F f) const
{
  Stack< BST_node* > stack;
  BST_node* temp = root_;
  while (temp || !stack.isEmpty())
  {
    if (temp)
    {
      stack.push(temp);
      temp = temp->left_;
    }
    else
    {
      temp = stack.peek();
      stack.rmBack();
      f(temp->data_);
      temp = temp->right_;
    }
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< class F >
F tampio::BinarySearchTree< Key, Value, Compare >::traverse_rnl(F f) const
{
  Stack< BST_node* > stack;
  BST_node* temp = root_;
  while (temp || !stack.isEmpty())
  {
    if (temp)
    {
      stack.push(temp);
      temp = temp->right_;
    }
    else
    {
      temp = stack.peek();
      stack.rmBack();
      f(temp->data_);
      temp = temp->left_;
    }
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
template< class F >
F tampio::BinarySearchTree< Key, Value, Compare >::traverse_breadth(F f) const
{
  if (!root_)
  {
    return f;
  }
  Stack< BST_node* > stack;
  stack.push(root_);

  while (!stack.isEmpty())
  {
    struct BST_node* node = stack.peek();
    stack.rmBack();
    f(node->data_);

    if (node->right_)
    {
      stack.push(node->right_);
    }
    if (node->left_)
    {
      stack.push(node->left_);
    }
  }
  return f;
}

template< typename Key, typename Value, typename Compare >
struct tampio::BinarySearchTree< Key, Value, Compare >::Iterator
{
  Iterator& operator++();
  Iterator operator++(int);
  Iterator(BST_node*, BinarySearchTree*);
  bool operator!=(const Iterator&) const;
  bool operator!=(const ConstIterator&) const;
  bool operator==(const Iterator&) const;
  bool operator==(const ConstIterator&) const;
  Iterator() = default;
  std::pair< Key, Value >& operator*();
  std::pair< Key, Value >* operator->();

private:
  BST_node* curr() const;
  Stack< BST_node* > stack_;
  Compare cmp_;
  void treeDelete(BST_node*);
  BST_node* mostLeft(BST_node*);

  friend BinarySearchTree< Key, Value, Compare >;
};

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::BST_node*
tampio::BinarySearchTree< Key, Value, Compare >::Iterator::curr() const
{
    return !stack_.isEmpty() ? stack_.peek() : nullptr;
}

template< typename Key, typename Value, typename Compare >
struct tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator
{

  ConstIterator& operator++();
  ConstIterator operator++(int);
  bool operator!=(const ConstIterator&) const;
  bool operator!=(const Iterator&) const;
  bool operator==(const ConstIterator&) const;
  bool operator==(const Iterator&) const;
  ConstIterator() = default;
  ConstIterator(BST_node*, const BinarySearchTree*);
  std::pair< Key, Value >& operator*() const;
  std::pair< Key, Value >* operator->() const;

private:
  BST_node* curr() const;
  Stack< BST_node* > stack_;
  friend BinarySearchTree< Key, Value, Compare >;
};

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::BST_node*
tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator::curr() const
{
    return !stack_.isEmpty() ? stack_.peek() : nullptr;
}


template< typename Key, typename Value, typename Compare >
struct tampio::BinarySearchTree< Key, Value, Compare >::BST_node
{
  std::pair< Key, Value > data_;
  BST_node* left_;
  BST_node* right_;
  long height_;
  BST_node() = default;
  BST_node(std::pair< Key, Value > pair,
      BST_node* left = nullptr,
      BST_node* right = nullptr,
      long height = 1);
  BST_node(const BST_node&);

  // AVL-tree
  static long getHeight(BST_node* node);
  static long balanceFactor(BST_node* node);
  static void updateHeight(BST_node* node);
  static BST_node* rotateRight(BST_node* nodeA);
  static BST_node* rotateLeft(BST_node* nodeB);
  static BST_node* balance(BST_node* node);
  static BST_node* insert(BST_node* rootNode, const Key& key, const Value& value);
  static BST_node* findMin(BST_node* node);
  static BST_node* removeMin(BST_node* node);
  static BST_node* removeKey(BST_node* p, const Key& key);
};

template< typename Key, typename Value, typename Compare >
void tampio::BinarySearchTree< Key, Value, Compare >::BST_node::updateHeight(BST_node* node)
{
  long heightLeft = getHeight(node->left_);
  long heightRight = getHeight(node->right_);
  node->height_ = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
}
template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::BST_node*
tampio::BinarySearchTree< Key, Value, Compare >::BST_node::rotateRight(BST_node* nodeA)
{
  BST_node* nodeB = nodeA->left_;
  nodeA->left_ = nodeB->right_;
  nodeB->right_ = nodeA;
  updateHeight(nodeA);
  updateHeight(nodeB);
  return nodeB;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::BST_node*
tampio::BinarySearchTree< Key, Value, Compare >::BST_node::rotateLeft(BST_node* nodeB)
{
  BST_node* nodeA = nodeB->right_;
  nodeB->right_ = nodeA->left_;
  nodeA->left_ = nodeB;
  updateHeight(nodeB);
  updateHeight(nodeA);
  return nodeA;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::BST_node*
tampio::BinarySearchTree< Key, Value, Compare >::BST_node::balance(BST_node* node)
{
  updateHeight(node);
  if (balanceFactor(node) == 2)
  {
    if (balanceFactor(node->right_) < 0)
    {
      node->right_ = rotateRight(node->right_);
    }
    return rotateLeft(node);
  }
  if (balanceFactor(node) == -2)
  {
    if (balanceFactor(node->left_) > 0)
    {
      node->left_ = rotateLeft(node->left_);
    }
    return rotateRight(node);
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::BST_node*
tampio::BinarySearchTree< Key, Value, Compare >::BST_node::insert(BST_node* rootNode,
    const Key& key,
    const Value& value)
{
  if (!rootNode)
  {
    return new BST_node(std::pair< Key, Value >(key, value));
  }
  if (Compare()(key, rootNode->data_.first))
  {
    rootNode->left_ = insert(rootNode->left_, key, value);
  }
  else if (Compare()(rootNode->data_.first, key))
  {
    rootNode->right_ = insert(rootNode->right_, key, value);
  }
  else
  {
    rootNode->data_.second = value;
  }
  return balance(rootNode);
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::BST_node*
tampio::BinarySearchTree< Key, Value, Compare >::BST_node::findMin(BST_node* node)
{
  return node->left_ ? findMin(node->left_) : node;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::BST_node*
tampio::BinarySearchTree< Key, Value, Compare >::BST_node::removeMin(BST_node* node)
{
  if (!node->left_)
  {
    return node->right_;
  }
  node->left_ = removeMin(node->left_);
  return balance(node);
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::BST_node*
tampio::BinarySearchTree< Key, Value, Compare >::BST_node::removeKey(BST_node* p, const Key& key)
{
  if (!p)
  {
    return nullptr;
  }
  if (key < p->data_.first)
  {
    p->left_ = removeKey(p->left_, key);
  }
  else if (key > p->data_.first)
  {
    p->right_ = removeKey(p->right_, key);
  }
  else
  {
    BST_node* leftNode = p->left_;
    BST_node* rightNode = p->right_;
    delete p;
    if (!rightNode)
    {
      return leftNode;
    }
    BST_node* min = findMin(rightNode);
    min->right_ = removeMin(rightNode);
    min->left_ = leftNode;
    return balance(min);
  }
  return balance(p);
}

template< typename Key, typename Value, typename Compare >
long tampio::BinarySearchTree< Key, Value, Compare >::BST_node::balanceFactor(BST_node* node)
{
  return getHeight(node->right_) - getHeight(node->left_);
}

template< typename Key, typename Value, typename Compare >
long tampio::BinarySearchTree< Key, Value, Compare >::BST_node::getHeight(BST_node* node)
{
  return node ? node->height_ : 0;
}

template< typename Key, typename Value, typename Compare >
tampio::BinarySearchTree< Key, Value, Compare >::BST_node::BST_node(std::pair< Key, Value > pair,
    BST_node* left,
    BST_node* right,
    long height) :
    data_(pair),
    left_(left),
    right_(right),
    height_(height)
{
}

template< typename Key, typename Value, typename Compare >
tampio::BinarySearchTree< Key, Value, Compare >::BST_node::BST_node(const BST_node& node) :
    data_(node.data_),
    left_(node.left_),
    right_(node.right_),
    height_(node.height_)
{
}

template< typename Key, typename Value, typename Compare >
tampio::BinarySearchTree< Key, Value, Compare >::BinarySearchTree() :
    root_(nullptr)
{
}

template< typename Key, typename Value, typename Compare >
tampio::BinarySearchTree< Key, Value, Compare >::BinarySearchTree(BinarySearchTree&& src) noexcept :
    root_(src.root_),
    cmp_(src.cmp_)
{
  src.root_ = nullptr;
}

template< typename Key, typename Value, typename Compare >
tampio::BinarySearchTree< Key, Value, Compare >& tampio::BinarySearchTree< Key, Value, Compare >::operator=(
    const BinarySearchTree& other)
{
  BinarySearchTree< Key, Value, Compare > newTree(other);
  swap(newTree);
  return *this;
}

template< typename Key, typename Value, typename Compare >
tampio::BinarySearchTree< Key, Value, Compare >& tampio::BinarySearchTree< Key, Value, Compare >::operator=(
    BinarySearchTree&& other) noexcept
{
  if (this != &other)
  {
    swap(other);
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
tampio::BinarySearchTree< Key, Value, Compare >::~BinarySearchTree()
{
  if (!empty())
  {
    treeDelete(root_);
  }
}

template< typename Key, typename Value, typename Compare >
tampio::BinarySearchTree< Key, Value, Compare >::BinarySearchTree(const BinarySearchTree& other) :
    root_(nullptr)
{
  for (ConstIterator otherIt = other.cbegin(); otherIt != other.cend(); ++otherIt)
  {
    push(otherIt->first, otherIt->second);
  }
}

template< typename Key, typename Value, typename Compare >
void tampio::BinarySearchTree< Key, Value, Compare >::swap(BinarySearchTree& tree) noexcept
{
  std::swap(root_, tree.root_);
  std::swap(cmp_, tree.cmp_);
}

template< typename Key, typename Value, typename Compare >
void tampio::BinarySearchTree< Key, Value, Compare >::treeDelete(BST_node* treeRoot)
{
  if (treeRoot != nullptr)
  {
    treeDelete(treeRoot->left_);
    treeDelete(treeRoot->right_);
    delete treeRoot;
  }
}

template< typename Key, typename Value, typename Compare >
bool tampio::BinarySearchTree< Key, Value, Compare >::empty() const
{
  return !root_;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::BST_node*
tampio::BinarySearchTree< Key, Value, Compare >::mostLeft(BST_node* node)
{
  while (node->left_)
  {
    node = node->left_;
  }
  return node;
}

template< typename Key, typename Value, typename Compare >
void tampio::BinarySearchTree< Key, Value, Compare >::push(const Key& key, const Value& value)
{
  root_ = BST_node::insert(root_, key, value);
}


template< typename Key, typename Value, typename Compare >
void tampio::BinarySearchTree< Key, Value, Compare >::dropKey(const Key& key)
{
  root_ = BST_node::removeKey(root_, key);
}

template< typename Key, typename Value, typename Compare >
tampio::BinarySearchTree< Key, Value, Compare >::Iterator::Iterator(BST_node* node, BinarySearchTree* tree)
{
  BST_node* ptr = tree->root_;
  while (ptr)
  {
    stack_.push(ptr);
    ptr = ptr->left_;
  }
  while (!stack_.isEmpty() && curr() != node)
  {
    (*this)++;
  }
}

template< typename Key, typename Value, typename Compare >
tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator::ConstIterator(BST_node* node,
    const BinarySearchTree* tree)
{
  BST_node* ptr = tree->root_;
  while (ptr)
  {
    stack_.push(ptr);
    ptr = ptr->left_;
  }
  while (!stack_.isEmpty() && curr() != node)
  {
    (*this)++;
  }
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::Iterator
tampio::BinarySearchTree< Key, Value, Compare >::begin()
{
  Iterator iter(mostLeft(root_), this);
  return iter;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::Iterator
tampio::BinarySearchTree< Key, Value, Compare >::end()
{
  return Iterator();
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator
tampio::BinarySearchTree< Key, Value, Compare >::cbegin() const
{
  BST_node* current = root_;
  if (!current)
  {
    return ConstIterator(nullptr, this);
  }
  while (current->left_)
  {
    current = current->left_;
  }
  ConstIterator it(current, this);
  return it;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator
tampio::BinarySearchTree< Key, Value, Compare >::cend() const
{
  return ConstIterator();
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::Iterator&
tampio::BinarySearchTree< Key, Value, Compare >::Iterator::operator++()
{
  BST_node* cur = !stack_.isEmpty() ? curr()->right_ : nullptr;
  stack_.rmBack();
  while (cur)
  {
    stack_.push(cur);
    cur = cur->left_;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator&
tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator++()
{
  BST_node* cur = !stack_.isEmpty() ? curr()->right_ : nullptr;
  stack_.rmBack();
  while (cur)
  {
    stack_.push(cur);
    cur = cur->left_;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::Iterator
tampio::BinarySearchTree< Key, Value, Compare >::Iterator::operator++(int)
{
  Iterator result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator
tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator++(int)
{
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value >& tampio::BinarySearchTree< Key, Value, Compare >::Iterator::operator*()
{
  return curr()->data_;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value >* tampio::BinarySearchTree< Key, Value, Compare >::Iterator::operator->()
{
  return &(curr()->data_);
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value >& tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator*() const
{
  return curr()->data_;
}

template< typename Key, typename Value, typename Compare >
std::pair< Key, Value >* tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator->() const
{
  return &(curr()->data_);
}

template< typename Key, typename Value, typename Compare >
bool tampio::BinarySearchTree< Key, Value, Compare >::Iterator::operator==(const Iterator& other) const
{
  return curr() == other.curr();
}

template< typename Key, typename Value, typename Compare >
bool tampio::BinarySearchTree< Key, Value, Compare >::Iterator::operator==(const ConstIterator& other) const
{
  return curr() == other.curr();
}

template< typename Key, typename Value, typename Compare >
bool tampio::BinarySearchTree< Key, Value, Compare >::Iterator::operator!=(const Iterator& other) const
{
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
bool tampio::BinarySearchTree< Key, Value, Compare >::Iterator::operator!=(const ConstIterator& other) const
{
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
bool tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator==(const ConstIterator& other) const
{
  return this->curr() == other.curr();
}

template< typename Key, typename Value, typename Compare >
bool tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator==(const Iterator& other) const
{
  return this->curr() == other.curr();
}

template< typename Key, typename Value, typename Compare >
bool tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator!=(const ConstIterator& other) const
{
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
bool tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator::operator!=(const Iterator& other) const
{
  return !(*this == other);
}

#endif
