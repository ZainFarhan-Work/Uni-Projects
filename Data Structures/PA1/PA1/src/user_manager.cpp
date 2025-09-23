#include "../include/user_manager.h"
#include "../include/user.h"
#include "../include/follow_list.h"
#include "../include/post_pool.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

UserManager::UserManager() {}

UserManager::~UserManager() {}

LinkedList<User>::Node* UserManager::createUser(int userID, const string& username)
{

    LinkedList<User>::Node* tempUser = users.find([userID, username](const User& usr) -> bool {

        if (usr.userID == userID || usr.userName == username)
        {
            return true;
        }

        return false;

    });

    if (tempUser != nullptr)
    {
        return nullptr;
    }
    
    User newUser = User(userID, username);

    return users.push_front(newUser);
    
}

bool UserManager::deleteUser(int userID)
{
    LinkedList<User>::Node* tempUser = users.find([userID](const User& usr) -> bool {

        if (usr.userID == userID)
        {
            return true;
        }

        return false;

    });

    if (tempUser == nullptr)
    {
        return false;
    }
    

    users.remove(tempUser);
    return true;
    
}

bool UserManager::follow(int followerID, int followeeID)
{
    if (followerID == followeeID)
    {
        return false;
    }
    
    LinkedList<User>::Node* follower = users.find([followerID](const User& usr) -> bool {

        if (usr.userID == followerID)
        {
            return true;
        }

        return false;

    });

    LinkedList<User>::Node* followee = users.find([followeeID](const User& usr) -> bool {

        if (usr.userID == followeeID)
        {
            return true;
        }

        return false;

    });

    if (follower == nullptr || followee == nullptr)
    {
        return false;
    }

    if (follower->data.following->findFollowing(followee->data.userID))
    {
        return false;
    }


    follower->data.followUser(&followee->data);
    
    return true;
    
}

bool UserManager::unfollow(int followerID, int followeeID)
{
    LinkedList<User>::Node* follower = users.find([followerID](const User& usr) -> bool {

        if (usr.userID == followerID)
        {
            return true;
        }

        return false;

    });

    LinkedList<User>::Node* followee = users.find([followeeID](const User& usr) -> bool {

        if (usr.userID == followeeID)
        {
            return true;
        }

        return false;

    });

    if (follower == nullptr || followee == nullptr)
    {
        return false;
    }

    if (!follower->data.following->findFollowing(followee->data.userID))
    {
        return false;
    }

    follower->data.following->removeFollowing(followeeID);
    
    return true;
    
}

bool UserManager::isFollowing(int followerID, int followeeID) const
{
    auto& constUsers = const_cast<LinkedList<User>&>(users); // I hate that I have to do this, just to use the find function

    LinkedList<User>::Node* follower = constUsers.find([followerID](const User& usr) -> bool {

        if (usr.userID == followerID)
        {
            return true;
        }

        return false;

    });

    LinkedList<User>::Node* followee = constUsers.find([followeeID](const User& usr) -> bool {

        if (usr.userID == followeeID)
        {
            return true;
        }

        return false;

    });

    if (follower && followee && follower->data.following->findFollowing(followee->data.userID))
    {
        return true;
    }
    
    
    return false;
}

bool UserManager::addPost(int userID, Post* post)
{
    LinkedList<User>::Node* u = findUserByID(userID);

    if (u)
    {
        u->data.posts.addPost(*post); // THis is so stupid, I have to do this since u->data.addPost only takes id and ctegory as parameters
        return true;
    }
    

    return false;
    
}

bool UserManager::deletePost(int userID, PostID postID)
{

    LinkedList<User>::Node* u = findUserByID(userID);

    if (u)
    {
        u->data.posts.removePost(postID); // THis is so stupid, I have to do this since u->data.addPost only takes id and ctegory as parameters
        return true;
    }
    

    return false;
    
}

LinkedList<User>::Node* UserManager::findUserByID(int userID)
{
    LinkedList<User>::Node* tempUser = users.find([userID](const User& usr) -> bool {

        if (usr.userID == userID)
        {
            return true;
        }

        return false;

    });

    if (tempUser == nullptr)
    {
        return nullptr;
    }

    return tempUser;
    
}

LinkedList<User>::Node* UserManager::findUserByName(const string& username)
{

    LinkedList<User>::Node* tempUser = users.find([username](const User& usr) -> bool {

        if (usr.userName == username)
        {
            return true;
        }

        return false;

    });

    if (tempUser == nullptr)
    {
        return nullptr;
    }

    return tempUser;
}

void UserManager::exportUsersCSV(const string& path) const
{
    
}

void UserManager::importUsersCSV(const string& path)
{
    
}

void UserManager::dumpAllUsers(ostream& out) const
{
    
}