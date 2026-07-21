#pragma once

#include <cstdlib>

#include "Node.h"

template<typename T>
class DoublyLinkedList
{
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    bool HasValue(const T& value) const;
    bool IsEmpty() const;

    const T* GetFrontOrNull();
    const T* GetBackOrNull();
    const T* GetValue(unsigned int index);

    void AddFront(T&& value);
    void AddBack(T&& value);

    bool RemoveFront();
    bool RemoveBack();

    bool Remove(const T& value);
    bool RemoveRandom();

private:
    Node<T>* getNodeOrNull(unsigned int index) const;
    Node<T>* getNodeOrNull(const T& value) const;
    void removeNode(Node<T>* deleteNode);

private:
    Node<T>* mHeadOrNull;
    Node<T>* mTailOrNull;

    unsigned int mSize;
};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : mHeadOrNull(nullptr)
    , mTailOrNull(nullptr)
    , mSize(0)
{
}

template<typename T>
bool DoublyLinkedList<T>::IsEmpty() const
{
    return mSize == 0 ? true : false;
}

template<typename T>
const T* DoublyLinkedList<T>::GetFrontOrNull()
{
    if (mHeadOrNull == nullptr)
    {
        return nullptr;
    }

    return mHeadOrNull->GetValue();
}

template<typename T>
const T* DoublyLinkedList<T>::GetBackOrNull()
{
    if (mTailOrNull == nullptr)
    {
        return nullptr;
    }

    return mTailOrNull->GetValue();
}

template<typename T>
const T* DoublyLinkedList<T>::GetValue(unsigned int index)
{
    assert(index < mSize);
    
    Node<T>* returnNode = getNodeOrNull(index);
    assert(returnNode != nullptr);

    return returnNode->GetValue();
}

template<typename T>
bool DoublyLinkedList<T>::HasValue(const T& value) const
{
    return getValueOrNull(value) == nullptr ? false : true;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    if (IsEmpty())
    {
        return;
    }

    while (mHeadOrNull != nullptr)
    {
        Node<T>* deleteNode = mHeadOrNull;
        mHeadOrNull = mHeadOrNull->GetNextNodeOrNull();

        delete deleteNode;
    }

    mHeadOrNull = nullptr;
    mTailOrNull = nullptr;
}

template<typename T>
void DoublyLinkedList<T>::AddFront(T&& value)
{
    ++mSize;
    
    Node<T>* newNode = new Node<T>(value);
    if (IsEmpty())
    {
        mHeadOrNull = newNode;
        mTailOrNull = mHeadOrNull;

        return;
    }

    assert(mHeadOrNull != nullptr);
    mHeadOrNull->SetPrevNode(newNode);
    newNode->SetNextNode(mHeadOrNull);

    mHeadOrNull = newNode;
}

template<typename T>
void DoublyLinkedList<T>::AddBack(T&& value)
{
    ++mSize;
    
    Node<T>* newNode = new Node<T>(value);
    if (IsEmpty())
    {
        mHeadOrNull = newNode;
        mTailOrNull = mHeadOrNull;

        return;
    }

    assert(mTailOrNull != nullptr);
    mTailOrNull->SetNextNode(newNode);
    newNode->SetPrevNode(mTailOrNull);

    mTailOrNull = newNode;
}

template<typename T>
bool DoublyLinkedList<T>::RemoveFront()
{
    if (IsEmpty())
    {
        return false;
    }

    removeNode(mHeadOrNull);
    return true;
}

template<typename T>
bool DoublyLinkedList<T>::RemoveBack()
{
    if (IsEmpty())
    {
        return false;
    }

    removeNode(mTailOrNull);
    return true;
}

template<typename T>
bool DoublyLinkedList<T>::Remove(const T& value)
{
    Node<T>* deleteNodeOrNull = getNodeOrNull(value);
    if (deleteNodeOrNull == nullptr)
    {
        return false;
    }

    removeNode();
    return true;
}

template<typename T>
bool DoublyLinkedList<T>::RemoveRandom()
{
    if (IsEmpty())
    {
        return false;
    }

    unsigned int randomIndex = (std::rand() % mSize) - 1;
    Node<T>* deleteNode = getNodeOrNull(randomIndex);
    removeNode(deleteNode);
    
    return true;
}

template<typename T>
Node<T>* DoublyLinkedList<T>::getNodeOrNull(unsigned int index) const
{
    Node<T>* nodeOrNull = mHeadOrNull;

    for (unsigned int i = 0; i < index; ++i)
    {
        assert(nodeOrNull != nullptr);
        nodeOrNull = nodeOrNull->GetNextNodeOrNull();
    }

    return nodeOrNull;
}

template<typename T>
Node<T>* DoublyLinkedList<T>::getNodeOrNull(const T& value) const
{
    Node<T>* nodeOrNull = mHeadOrNull;
    while (nodeOrNull != nullptr)
    {
        // Todo: T equals
        if (*nodeOrNull == value)
        {
            return nodeOrNull;
        }

        nodeOrNull = nodeOrNull->GetNextNodeOrNull();
    }

    return nullptr;
}

template<typename T>
void DoublyLinkedList<T>::removeNode(Node<T>* deleteNode)
{
    assert(deleteNode != nullptr);

    if (mSize == 1)
    {
        mHeadOrNull = nullptr;
        mTailOrNull = nullptr;
    }
    else if (deleteNode == mHeadOrNull)
    {
        mHeadOrNull = mHeadOrNull->GetNextNodeOrNull();

        deleteNode->GetNextNodeOrNull()->SetPrevNode(nullptr);
        deleteNode->SetNextNode(nullptr);

        assert(mHeadOrNull == mTailOrNull);
    }
    else if (deleteNode == mTailOrNull)
    {
        mTailOrNull = mTailOrNull->GetPrevNodeOrNull();

        deleteNode->GetPrevNodeOrNull()->SetNextNode(nullptr);
        deleteNode->SetPrevNode(nullptr);

        assert(mHeadOrNull == mTailOrNull);
    }
    else
    {
        Node<T>* nextNode = deleteNode->GetNextNodeOrNull();
        assert(nextNode != nullptr);

        Node<T>* prevNode = deleteNode->GetPrevNodeOrNull();
        assert(prevNode != nullptr);

        prevNode->SetNextNode(nextNode);
        nextNode->SetPrevNode(prevNode);
    }

    delete deleteNode;
    --mSize;
}