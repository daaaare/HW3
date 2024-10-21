#include "arrayStack.h"

template<class ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1) {}

template<class ItemType>
bool ArrayStack<ItemType>::isEmpty() const {
    return top == -1;
}

template<class ItemType>
void ArrayStack<ItemType>::push(const ItemType& newEntry) {
    if (top >= DEFAULT_CAPACITY - 1)
        throw std::overflow_error("Stack overflow");
    items[++top] = newEntry;
}

template<class ItemType>
ItemType ArrayStack<ItemType>::pop() {
    if (isEmpty())
        throw std::runtime_error("Attempt to pop from an empty stack");
    return items[top--];
}

template<class ItemType>
ItemType ArrayStack<ItemType>::peek() const {
    if (isEmpty())
        throw std::runtime_error("Attempt to peek at an empty stack");
    return items[top];
}

template class ArrayStack<int>;
template class ArrayStack<char>;
template class ArrayStack<double>;
template class ArrayStack<std::string>;