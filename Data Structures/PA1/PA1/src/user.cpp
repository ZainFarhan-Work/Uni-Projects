#include "../include/user.h"
#include "../include/follow_list.h"
#include <iostream>
using namespace std;

User::User(int id, const string& name) {
}

// Copy constructor
User::User(const User& other)  {
    // Don't copy the following relationships - they should be rebuilt separately
    // This prevents circular dependency issues and dangling pointers
}

// Copy assignment operator
User& User::operator=(const User& other) {
    
}

// Move constructor
User::User(User&& other) noexcept {
}

// Move assignment operator
User& User::operator=(User&& other) noexcept {
   
}

User::~User() {
    
}

void User::addPost(int postID, const string& category) {
    
}

void User::followUser(User* otherUser) {
    
}

void User::displayFollowing() const {
    
}