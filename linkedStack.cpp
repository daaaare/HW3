#include "linkedStack.h"

template <class ItemType>
LinkedStack<ItemType>::LinkedStack() : topNode(nullptr) {}

template <class ItemType>
LinkedStack<ItemType>::~LinkedStack() {
    clear();
}

template <class ItemType>
bool LinkedStack<ItemType>::isEmpty() const {
    return topNode == nullptr;
}

template <class ItemType>
void LinkedStack<ItemType>::push(const ItemType& newEntry) {
    Node<ItemType>* newNode = new Node<ItemType>(newEntry, topNode);
    topNode = newNode;
}

template <class ItemType>
ItemType LinkedStack<ItemType>::pop() {
    if (isEmpty())
        throw std::runtime_error("Attempt to pop from an empty stack");

    Node<ItemType>* nodeToDelete = topNode;
    ItemType item = topNode->getItem();
    topNode = topNode->getNext();
    delete nodeToDelete;
    return item;
}

template <class ItemType>
ItemType LinkedStack<ItemType>::peek() const {
    if (isEmpty())
        throw std::runtime_error("Attempt to peek at an empty stack");

    return topNode->getItem();
}

template <class ItemType>
void LinkedStack<ItemType>::clear() {
    while (!isEmpty()) {
        pop();
    }
}

// Explicit template instantiation
template class LinkedStack<int>;
template class LinkedStack<char>;
template class LinkedStack<double>;
template class LinkedStack<std::string>;
