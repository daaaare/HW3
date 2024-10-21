#ifndef STACK_H
#define STACK_H

template<class ItemType>
class StackInterface {
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const ItemType& newEntry) = 0;
    virtual ItemType pop() = 0;
    virtual ItemType peek() const = 0;
    virtual ~StackInterface() {};
};

#endif
