#include <iostream>

#ifndef LIST_H
#define LIST_H

template <typename T> 
struct Node {
    T val;
    Node* next;

    // Constructor
    Node(T _val) : val(_val), next(nullptr) {}
};




#endif