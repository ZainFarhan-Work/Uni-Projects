#pragma once
#include <functional> 
#include <cstddef>    
using namespace std;

template<typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& d): data(d), prev(nullptr), next(nullptr) {}
    };

    LinkedList();
    ~LinkedList();

    Node* push_back(const T& val);   // O(1)
    Node* push_front(const T& val);  // O(1)
    void insert_after(Node* pos, const T& val); // O(1)
    void remove(Node* node); // O(1)
    Node* find(function<bool(const T&)> pred); // O(n)
    Node* head() const;
    Node* tail() const;
    size_t size() const;    // O(1)
    void clear();           // frees nodes

private:
    Node* _head;
    Node* _tail;
    size_t _size;
};

// Actual Implementation

template<typename T>
LinkedList<T>::LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}

template<typename T>
LinkedList<T>::~LinkedList() { clear(); }

template<typename T> // This Synatx is super weird tbh
typename LinkedList<T>::Node* LinkedList<T>::push_back(const T& val) {

    Node* node = new Node(val);

    if (_tail)
    {
        _tail->next = node;
        node->prev = _tail;
        _tail = node;
    }
    else
    {
        _head = _tail = node;
    }

    _size++;
    return node;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::push_front(const T& val) {

    Node* node = new Node(val);

    if (_head)
    {
        node->next = _head;
        _head->prev = node;
        _head = node;
    }
    else
    {
        _head = _tail = node;
    }
    
    _size++;
    return node;
}

template<typename T>
void LinkedList<T>::insert_after(Node* pos, const T& val)
{
    if (!pos) return;

    Node* node = new Node(val);
    
    node->prev = pos;
    node->next = pos->next;
    
    if (pos->next)
    {
        pos->next->prev = node;
    }
    else
    {
        // pos was the tail, so update _tail
        _tail = node;
    }

    pos->next = node;
    _size++;
}

template<typename T>
void LinkedList<T>::remove(Node* node)
{
    if (!node) return;

    if (node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        // node was head
        _head = node->next;
    }

    if (node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        // node was tail
        _tail = node->prev;
    }

    delete node;
    _size--;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::find(function<bool(const T&)> pred)
{
    if (_head == nullptr || _tail == nullptr || _size == 0) // Most of these are reduntant, but why not?
    {
        return nullptr;
    }

    Node* node = _head;

    while (node)
    {
        if (pred(node->data))
        {
            return node;
        }

        node = node->next;
        
    }

    return nullptr;
    
}

template<typename T>
void LinkedList<T>::clear()
{
    if (_head == nullptr || _tail == nullptr || _size == 0)
    {
        return;
    }

    Node* current = _head;
    Node* prev = nullptr;

    while (current)
    {
        prev = current;
        current = current->next;

        delete prev;
    }
    
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::head() const
{
    return _head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::tail() const
{
    return _tail;
}

template<typename T>
size_t LinkedList<T>::size() const
{
    return _size;
}
