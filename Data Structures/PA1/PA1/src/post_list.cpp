#include "../include/post_list.h"
#include <iostream>

PostList::~PostList()
{

    PostNode* prev = nullptr;
    PostNode* node = head;

    while (node)
    {
        prev = node;
        node = node->next;

        delete prev;
    }

    head = nullptr;

}

void PostList::addPost(const Post& p)
{
    Post* temp = new Post(p.postID, p.category, p.views, p.content);
    PostNode* node = new PostNode(temp);

    if (head)
    {
        node->next = head;
        head = node;
    }
    else
    {
        head = node;
    }
}

bool PostList::removePost(int postID)
{
    if (isEmpty())
    {
        return false;
    }

    PostNode* prev = nullptr;
    PostNode* node = head;

    while (node && node->post->postID != postID)
    {
        prev = node;
        node = node->next;
    }

    if (!node)
    {
        return false;
    }

    if (prev)
    {
        prev->next = node->next;
    }
    else
    {
        head = node->next;
    }
    

    delete node;
    node = nullptr; // I don't think this is strictly neccessary but just in case

    return true;
    
}

Post* PostList::findPost(int postID)
{
    if (isEmpty())
    {
        return nullptr;
    }

    PostNode* node = head;

    while (node && node->post->postID != postID)
    {
        node = node->next;

        if (node && node->post->postID == postID)
        {
            return node->post;
        }
        
    }

    return nullptr;
    
}

void PostList::displayPosts() const
{
    if (isEmpty())
    {
        cout << "<EMPTY>" << endl;
    }

    PostNode* node = head;

    while (node)
    {
        cout << "ID: " << node->post->postID << endl;
        cout << "Category: " << node->post->category << endl;
        cout << "Views: " << node->post->views << endl;
        cout << "Content: " << node->post->content << endl;

        node = node->next;
        
    }
    
    
}

bool PostList::isEmpty() const { return head == nullptr; }