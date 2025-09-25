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
        // u->data.posts.addPost(*post); // THis is so stupid, I have to do this since u->data.addPost only takes id and ctegory as parameters
        u->data.addPost(post->postID, post->category); // This just leaves the views and content blank for now
        return true;
    }
    

    return false;
    
}

bool UserManager::deletePost(int userID, PostID postID)
{

    LinkedList<User>::Node* u = findUserByID(userID);

    if (u)
    {
        u->data.posts.removePost(postID);
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
    ofstream outputFile(path);

    if (!outputFile.is_open())
    {
        return;
    }

    LinkedList<User>::Node* curr = users.head();

    for (size_t i = 0; i < users.size(); i++)
    {
        outputFile << curr->data.userID << "," << curr->data.userName << ",";

        // Print Followers

        outputFile << ",";

        FollowNode* followNode = curr->data.following->head;

        while (followNode)
        {   
            outputFile << followNode->user->userID;

            followNode = followNode->next;

            if (followNode)
            {
                outputFile << "|";
            }
            
        }

        outputFile << ",";

        // Print Posts

        PostNode* postNode = curr->data.posts.head;

        while (postNode)
        {   
            outputFile << postNode->post->postID << ":" << postNode->post->category << ":" << postNode->post->views;

            postNode = postNode->next;

            if (postNode)
            {
                outputFile << "|";
            }
            
        }

        outputFile << "\n";
    }

    outputFile.close();

    ifstream inputFile(path);

    if (!inputFile.is_open())
    {
        return;
    }

    string line;

    while (getline(inputFile, line))
    {
        if (!line.empty())
        {
            cout << "\n" << line << endl;
        }
    }

    inputFile.close();
    
}

void UserManager::importUsersCSV(const string& path)
{
    ifstream inputFile(path);

    if (!inputFile.is_open())
    {
        return;
    }

    users.clear();
    cout << "\n\n----- Import -----\n\n";

    string line;
    vector<string> tokens;


    // First Pass
    while (getline(inputFile, line))
    {
        if (!line.empty())
        {
            stringstream temp(line);
            string tempString;
            
            while (getline(temp, tempString, ','))
            {
                tokens.push_back(tempString);
                cout << "\n" << tokens.back() << endl;
            }
            
            User user = User(stoi(tokens[0]), tokens[1]);

            users.push_back(user);

            temp.clear();
            tokens.clear();
            
        }
    }

    inputFile.close();
    
}

void UserManager::dumpAllUsers(ostream& out) const
{
    
}