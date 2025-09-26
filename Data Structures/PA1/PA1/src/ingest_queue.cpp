#include "../include/ingest_queue.h"

#include <iostream>
using namespace std;

IngestQueue::IngestQueue(size_t capacity)
{
    buffer = new Post*[capacity];

    for (int i = 0; i < capacity; i++)
    {
        buffer[i] = nullptr;
    }
    
    this->capacity = capacity;

    head_idx = 0;
    tail_idx = 0;
    count = 0;
}

IngestQueue::~IngestQueue()
{
    for (int i = 0; i < capacity; i++)
    {
        delete buffer[i];
    }

    delete[] buffer;
}

bool IngestQueue::enqueue(Post* p)
{

    if (tail_idx >= capacity)
    {
        tail_idx = 0;
    }
    
    if (tail_idx == head_idx && count >= capacity)
    {
        return false;
    }
    
    buffer[tail_idx] = p;
    tail_idx++;

    count++;
    
    return true;
}

Post* IngestQueue::dequeue()
{

    if (empty())
    {
        return nullptr;
    }

    if (head_idx >= capacity)
    {
        head_idx = 0;
    }
    
    Post* p = buffer[head_idx];
    buffer[head_idx] = nullptr;
    head_idx++; 

    count--;

    return p;
}

size_t IngestQueue::size() const { return count; }

bool IngestQueue::empty() const { return head_idx == tail_idx && count == 0; }

size_t IngestQueue::dequeueBatch(Post** out_array, size_t max_k)
{
    if (max_k > count)
    {
        max_k = count;
    }
    
    int j = 0;

    for (int i = 0; i < max_k; i++)
    {
        out_array[i] = dequeue();

        if (out_array[i])
        {
            j++;
        }
        
    }
    
    return j;
}