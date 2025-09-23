#include "../include/operation_stack.h"
#include <cstddef> // size_t
using namespace std;

UndoRedoManager::UndoRedoManager(UserManager& um, PostPool& pool) : userManager(um), postPool(pool) {}
    

void UndoRedoManager::beginTransaction() {
   
}

void UndoRedoManager::commitTransaction() {
    
}

void UndoRedoManager::rollbackTransaction() {
    
}

void UndoRedoManager::record(const OpFrame& f) {
    
}

bool UndoRedoManager::undo()
{
    
    return false;
}

bool UndoRedoManager::redo()
{

    return false;
}
