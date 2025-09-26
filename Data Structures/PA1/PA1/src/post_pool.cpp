#include "../include/post_pool.h"
#include <iostream>
using namespace std;

PostPool::PostPool(size_t block_size)
{
    blocks.push_back(new Post[block_size]);
    this->block_size = block_size;

    current_block_index = 0;
    alloc_count = 0;
    reuse_count = 0;
   
}

PostPool::~PostPool()
{
    purge();
}

Post* PostPool::allocPost()
{
    if (!free_list.empty())
    {
        Post* p = free_list.front();
        free_list.erase(free_list.begin());
        reuse_count++;
        return p;
    }
    
    if (alloc_count < block_size)
    {
        return blocks[current_block_index] + (alloc_count++);
    }

    allocateBlock();
    current_block_index++;
    alloc_count = 0;

    if (alloc_count < block_size)
    {
        return blocks[current_block_index] + (alloc_count++);
    }

    return nullptr;
   
}

void PostPool::freePost(Post* p)
{
    if (p == nullptr)
    {
        return;
    }

    for (int i = 0; i <= current_block_index; i++) {
        for (int j = 0; j < block_size; j++) {
            if (blocks[i] + j == p) {
                p->postID = 0;
                p->category = "";
                p->views = 0;
                p->content = "";
                free_list.push_back(p);
                return;
            }
        }
    }
    
    // int i = 0;

    // while (i < current_block_index)
    // {
    //     for (int j = 0; j < block_size; j++)
    //     {
    //         if (blocks[i] + j == p)
    //         {
    //             p->postID = 0;
    //             p->category = "";
    //             p->views = 0;
    //             p->content = "";
    //             free_list.push_back(p);
    //             return;
    //         }
            
    //     }

    //     i++;
    // }
   
}

size_t PostPool::totalAllocations() const { return (current_block_index * block_size) + alloc_count; }

size_t PostPool::reuseCount() const { return reuse_count; }

void PostPool::purge()
{
    for (int i = 0; i < current_block_index; i++)
    {
        delete[] blocks[i];
    }

    alloc_count = 0;
    reuse_count = 0;
    current_block_index = 0;
    
}

void PostPool::allocateBlock()
{
    blocks.push_back(new Post[block_size]);
}