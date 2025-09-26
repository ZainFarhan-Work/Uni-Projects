#include "../include/operation_stack.h"
#include <cstddef> // size_t
using namespace std;

UndoRedoManager::UndoRedoManager(UserManager& um, PostPool& pool) : userManager(um), postPool(pool) {}
    

void UndoRedoManager::beginTransaction()
{
    transactionMarkers.push(undoStack.size());
}

void UndoRedoManager::commitTransaction()
{
    transactionMarkers.pop();
    undoStack.clear();
    redoStack.clear();
    trashList.clear();
}

void UndoRedoManager::rollbackTransaction()
{
    while (undoStack.size() != transactionMarkers.top())
    {
        
        undo();
    }
    
}

void UndoRedoManager::record(const OpFrame& f)
{
    undoStack.push_back(f);
    
}

bool UndoRedoManager::undo()
{
    if (undoStack.empty())
    {
        return false;
    }

    OpFrame f = undoStack.back();

    switch (f.type)
    {
    case OpType::CREATE_USER:
        userManager.deleteUser(f.userID);
        break;

    case OpType::DELETE_USER:
        userManager.createUser(f.userID, f.snapshot_username_or_content);
        break;

    case OpType::CREATE_POST:
        userManager.deletePost(f.userID, f.postID);
        break;

    case OpType::DELETE_POST:
        userManager.addPost(f.userID, postPool.allocPost());
        break;
    
    case OpType::FOLLOW:
        userManager.unfollow(f.userID, stoi(f.snapshot_username_or_content));
        break;

    case OpType::UNFOLLOW:
        userManager.follow(f.userID, stoi(f.snapshot_username_or_content));
        break;

    case OpType::EDIT_POST:
        userManager.deletePost(f.userID, f.postID);
        userManager.addPost(f.userID, postPool.allocPost());
        break;

    default:
        break;
    }

    redoStack.push_back(f);
    undoStack.pop_back();
    
    return true;
}

bool UndoRedoManager::redo()
{
    if (redoStack.empty())
    {
        return false;
    }
    
    OpFrame f = redoStack.back();

    switch (f.type)
    {
    case OpType::CREATE_USER:
        userManager.createUser(f.userID, f.snapshot_username_or_content);
        break;

    case OpType::DELETE_USER:
        userManager.deleteUser(f.userID);
        break;

    case OpType::CREATE_POST:
        userManager.addPost(f.userID, postPool.allocPost());
        break;

    case OpType::DELETE_POST:
        userManager.deletePost(f.userID, f.postID);
        break;
    
    case OpType::FOLLOW:
        userManager.follow(f.userID, stoi(f.snapshot_username_or_content));
        break;

    case OpType::UNFOLLOW:
        userManager.unfollow(f.userID, stoi(f.snapshot_username_or_content));
        break;

    case OpType::EDIT_POST:
        userManager.deletePost(f.userID, f.postID);
        userManager.addPost(f.userID, postPool.allocPost());
        break;

    default:
        break;
    }

    return false;
}
