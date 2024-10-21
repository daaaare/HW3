#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "stack.h"
#include "node.h"
#include <stdexcept>

template <class ItemType>
class LinkedStack : public StackInterface<ItemType> {
private:
    Node<ItemType>* topNode; 

public:
    LinkedStack(); 
    virtual ~LinkedStack(); 

    bool isEmpty() const override; 
    void push(const ItemType& newEntry) override; 
    ItemType pop() override; 
    ItemType peek() const override;
    void clear(); 
};

#endif 
