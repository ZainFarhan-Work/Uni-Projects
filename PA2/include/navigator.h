#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "../include/keychain.h"
#include "../include/locator.h"

typedef struct VaultNavigator{
    KeyChain* key_chain;
    Locator* map;
} VaultNavigator;

VaultNavigator* initializeNavigator(int num_allocations);

void navigatorMalloc(VaultNavigator* v_ptr, DataType type, int units, char* identifier);

void navigatorFree(VaultNavigator* v_ptr, char* identifier);

void storeData(VaultNavigator* v_ptr, char* identifier, void* data);

void accessData(VaultNavigator* v_ptr, char* identifier, void* dest);

void incrementPointer(VaultNavigator* v_ptr);

void decrementPointer(VaultNavigator* v_ptr);

void changePointer(VaultNavigator* v_ptr, char* identifier);

#endif // NAVIGATOR_H
