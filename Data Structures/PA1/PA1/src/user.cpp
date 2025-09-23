#include "../include/user.h"
#include "../include/follow_list.h"
#include <iostream>
using namespace std;

User::User(int id, const string& name) : userID(id), userName(name) { following = new FollowList(); }

// Copy constructor
User::User(const User& other)
{
    // Don't copy the following relationships - they should be rebuilt separately
    // This prevents circular dependency issues and dangling pointers

    this->userID = other.userID;
    this->userName = other.userName;
    this->posts = other.posts;

    // deep copy here
    this->following = new FollowList();

    FollowNode* otherCurr = other.following->head;

    while (otherCurr)
    {
        if (otherCurr)
        {
            this->following->addFollowing(otherCurr->user);
        }

        otherCurr = otherCurr->next;
    }
}

// Copy assignment operator
User& User::operator=(const User& other)
{
    if (this == &other)
    {
        return *this;
    }

    this->userID = other.userID;
    this->userName = other.userName;
    this->posts = other.posts;

    if (following)
    {
        delete following;
    }

    // deep copy here
    this->following = new FollowList();

    FollowNode* otherCurr = other.following->head;
    FollowNode* prev = nullptr;

    while (otherCurr)
    {
        if (otherCurr)
        {
            this->following->addFollowing(otherCurr->user);
        }

        prev = otherCurr;
        otherCurr = otherCurr->next;
    }
    
    return *this;
    
}

// Move constructor
User::User(User&& other) noexcept
{
    following = other.following;
    other.following = nullptr;
}

// Move assignment operator
User& User::operator=(User&& other) noexcept
{
    if (following)
    {
        delete following;
    }
    
    following = other.following;
    other.following = nullptr;
   
    return *this;
}

User::~User()
{
    delete following;
    
}

void User::addPost(int postID, const string& category)
{
    Post p = Post(postID, category, 0, "");
    posts.addPost(p);
    
}

void User::followUser(User* otherUser)
{
    following->addFollowing(otherUser);
}

void User::displayFollowing() const
{
    following->displayFollowing();
}