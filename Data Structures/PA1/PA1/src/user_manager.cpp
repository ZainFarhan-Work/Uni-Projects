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
    
    User newUser(userID, username);

    return users.push_back(newUser);
    
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
    if (post == nullptr) return false;

    LinkedList<User>::Node* u = findUserByID(userID);

    if (u)
    {
        // u->data.posts.addPost(*post); // This is so stupid, I have to do this since u->data.addPost only takes id and ctegory as parameters
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
        if (!u->data.posts.findPost(postID)) return false;

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
        outputFile << curr->data.userID << "," << curr->data.userName;

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

        curr = curr->next;
    }

    outputFile.close();
    
}

void UserManager::importUsersCSV(const string& path)
{
    ifstream inputFile(path);

    if (!inputFile.is_open())
    {
        return;
    }

    users.clear();

    string line;
    vector<string> lines;


    // First Pass
    while (getline(inputFile, line))
    {
        vector<string> tokens;

        if (!line.empty())
        {
            lines.push_back(line);

            size_t start = 0;
            size_t pos;
            
            while ((pos = line.find(',', start)) != string::npos)
            {
                tokens.push_back(line.substr(start, pos - start));
                start = pos + 1;
            }
            tokens.push_back(line.substr(start));

            createUser(stoi(tokens[0]), tokens[1]);

            tokens.clear();
            
        }
    }

    inputFile.close();

    // Second Pass
    for (size_t i = 0; i < lines.size(); i++)
    {
        vector<string> tokens;
        
        size_t start = 0;
        size_t pos;
        
        while ((pos = lines[i].find(',', start)) != string::npos)
        {
            tokens.push_back(lines[i].substr(start, pos - start));
            start = pos + 1;
        }
        tokens.push_back(lines[i].substr(start));

        start = 0;
        
        while ((pos = tokens[2].find('|', start)) != string::npos)
        {
            follow(stoi(tokens[0]), stoi(tokens[2].substr(start, pos - start)));
            start = pos + 1;
        }
        if (tokens[2] != "") follow(stoi(tokens[0]), stoi(tokens[2].substr(start)));

        start = 0;
        
        while ((pos = tokens[3].find('|', start)) != string::npos)
        {
            string postString = tokens[3].substr(start, pos - start);
            vector<string> post;

            size_t postStart = 0;
            size_t postPos;

            while ((postPos = postString.find(':', postStart)) != string::npos)
            {
                post.push_back(postString.substr(postStart, postPos - postStart));
                
                postStart = postPos + 1;
            }
            post.push_back(postString.substr(postStart));

            start = pos + 1;

            Post p(stoi(post[0]), post[1], stoi(post[2]), "");

            addPost(stoi(tokens[0]), &p);
        }
        if (tokens[3] != "")
        {
            string postString = tokens[3].substr(start, pos - start);
            vector<string> post;

            size_t postStart = 0;
            size_t postPos;

            while ((postPos = postString.find(':', postStart)) != string::npos)
            {
                post.push_back(postString.substr(postStart, postPos - postStart));
                
                postStart = postPos + 1;
            }
            post.push_back(postString.substr(postStart));

            start = pos + 1;

            Post p(stoi(post[0]), post[1], stoi(post[2]), "");

            addPost(stoi(tokens[0]), &p);
        }



        tokens.clear();
    }

    inputFile.close();
    
}

void UserManager::dumpAllUsers(ostream& out) const
{
    LinkedList<User>::Node* temp = users.head();
    
    for (int i = 0; i < users.size(); i++)
    {

        out << "Id: " << temp->data.userID << ", ";
        out << "Name: " << temp->data.userName << ", ";
        out << "Follower: ";
        
        // Print Followers

        FollowNode* followNode = temp->data.following->head;

        while (followNode)
        {   
            out << followNode->user->userID;

            followNode = followNode->next;

            if (followNode)
            {
                out << "|";
            }
            
        }

        out << ", Posts: ";

        // Print Posts

        PostNode* postNode = temp->data.posts.head;

        while (postNode)
        {   
            out << postNode->post->postID << ":" << postNode->post->category << ":" << postNode->post->views;

            postNode = postNode->next;

            if (postNode)
            {
                out << "|";
            }
            
        }

        out << "\n";

        temp = temp->next;

    }
    
    
}