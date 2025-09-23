#include "../include/follow_list.h"
#include "../include/user.h"
#include <iostream>
using namespace std;

FollowList::~FollowList()
{
    FollowNode* prev = nullptr;
    FollowNode* node = head;

    while (node)
    {
        prev = node;
        node = node->next;

        delete prev;
    }

    head = nullptr;
    
}

void FollowList::addFollowing(User* u)
{
    FollowNode* node = new FollowNode(u);

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

bool FollowList::removeFollowing(int userID)
{
    if (head == nullptr)
    {
        return false;
    }

    FollowNode* prev = nullptr;
    FollowNode* node = head;

    while (node && node->user->userID != userID)
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
    node = nullptr; // Isn't this the same as Post List?

    return true;
    
}

User* FollowList::findFollowing(int userID)
{

    if (head == nullptr)
    {
        return nullptr;
    }

    FollowNode* node = head;

    while (node && node->user->userID != userID)
    {
        cout << "\nUserID in List: " << node->user->userID << "\n";
        node = node->next;

        if (node && node->user->userID == userID)
        {
            return node->user;
        }
        
    }

    return node->user;
    
}

void FollowList::displayFollowing() const
{
    if (head == nullptr)
    {
        cout << "<EMPTY>" << endl;
    }

    FollowNode* node = head;

    while (node)
    {
        cout << endl;
        
        cout << "ID: " << node->user->userID << endl;
        cout << "Name: " << node->user->userName << endl;
        cout << "Posts: " << endl;
        cout << "--------------------------" << endl;
        // node->user->posts.displayPosts();
        cout << "--------------------------" << endl;
        cout << endl;

        cout << endl;

        node = node->next;
        
    }
   
}