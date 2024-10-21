#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "stack.h"
#include <stdexcept>

template<class ItemType>
class ArrayStack : public StackInterface<ItemType> {
private:
    static const int DEFAULT_CAPACITY = 100;  //default capacity of stack array
    ItemType items[DEFAULT_CAPACITY];  //array of stack items
    int top;  //index to top of stack

public:
    ArrayStack();

    bool isEmpty() const override;
    void push(const ItemType& newEntry) override;
    ItemType pop() override;
    ItemType peek() const override;
};

#endif 
