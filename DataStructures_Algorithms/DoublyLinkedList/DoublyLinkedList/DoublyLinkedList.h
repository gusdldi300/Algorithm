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
    bool Add(unsigned int index, T&& value);

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
    return getNodeOrNull(value) == nullptr ? false : true;
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
    Node<T>* newNode = new Node<T>(std::move(value));

    if (IsEmpty())
    {
        mTailOrNull = newNode;
    }
    else
    {
        assert(mHeadOrNull != nullptr);

        mHeadOrNull->SetPrevNode(newNode);
        newNode->SetNextNode(mHeadOrNull);
    }

    ++mSize;
    mHeadOrNull = newNode;
}

template<typename T>
void DoublyLinkedList<T>::AddBack(T&& value)
{
    Node<T>* newNode = new Node<T>(std::move(value));

    if (IsEmpty())
    {
        mHeadOrNull = newNode;
    }
    else
    {
        assert(mTailOrNull != nullptr);

        newNode->SetPrevNode(mTailOrNull);
        mTailOrNull->SetNextNode(newNode);
    }

    ++mSize;
    mTailOrNull = newNode;
}

template<typename T>
bool DoublyLinkedList<T>::Add(unsigned int index, T&& value)
{
    if (index > mSize)
    {
        return false;
    }

    if (index == 0)
    {
        AddFront(std::move(value));
    }
    else if (index == mSize)
    {
        AddBack(std::move(value));
    }
    else
    {
        Node<T>* newNode = new Node<T>(std::move(value));
        Node<T>* nextNode = getNodeOrNull(index);
        assert(nextNode != nullptr);

        Node<T>* lastNode = nextNode->GetPrevNodeOrNull();
        lastNode->SetNextNode(newNode);
        newNode->SetPrevNode(nextNode->GetPrevNodeOrNull());

        newNode->SetNextNode(nextNode);
        nextNode->SetPrevNode(newNode);

        ++mSize;
    }

    return true;
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

    removeNode(deleteNodeOrNull);
    return true;
}

template<typename T>
bool DoublyLinkedList<T>::RemoveRandom()
{
    if (IsEmpty())
    {
        return false;
    }

    unsigned int randomIndex = std::rand() % mSize;
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
        if (*nodeOrNull->GetValue() == value)
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
    }
    else if (deleteNode == mTailOrNull)
    {
        mTailOrNull = mTailOrNull->GetPrevNodeOrNull();

        deleteNode->GetPrevNodeOrNull()->SetNextNode(nullptr);
        deleteNode->SetPrevNode(nullptr);
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