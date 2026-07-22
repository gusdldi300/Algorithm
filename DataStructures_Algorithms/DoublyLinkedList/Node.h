#pragma once

#include <cassert>

template<typename T>
class Node
{
public:
    Node(T&& value);
    ~Node();

    Node<T>* GetNextNodeOrNull() const;
    Node<T>* GetPrevNodeOrNull() const;

    void SetPrevNode(Node<T>* node);
    void SetNextNode(Node<T>* node);
    
    const T* GetValue() const;

private:
    Node<T>* mPrevNodeOrNull;
    Node<T>* mNextNodeOrNull;

    T* mValue;
};

template<typename T>
Node<T>::Node(T&& value)
    : mPrevNodeOrNull(nullptr)
    , mNextNodeOrNull(nullptr)
{
    mValue = new T(std::move(value));
}

template<typename T>
Node<T>::~Node()
{
    delete mValue;
}

template<typename T>
Node<T>* Node<T>::GetNextNodeOrNull() const
{
    return mNextNodeOrNull;
}

template<typename T>
Node<T>* Node<T>::GetPrevNodeOrNull() const
{
    return mPrevNodeOrNull;
}

template<typename T>
void Node<T>::SetPrevNode(Node<T>* nodeOrNull)
{
    mPrevNodeOrNull = nodeOrNull;
}

template<typename T>
void Node<T>::SetNextNode(Node<T>* nodeOrNull)
{
    mNextNodeOrNull = nodeOrNull;
}

template<typename T>
const T* Node<T>::GetValue() const
{
    return mValue;
}

