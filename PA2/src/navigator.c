#include "../include/keychain.h"
#include "../include/locator.h"
#include "../include/navigator.h"

VaultNavigator* initializeNavigator(int num_allocations)
{
    VaultNavigator* nav = (VaultNavigator*) malloc(sizeof(VaultNavigator));

    if (nav == NULL)
    {
        return NULL;
    }

    KeyChain* chain = initializeKeyChain(RED, 7, "origin\0");

    nav->map = initializeMap(num_allocations, chain, "origin\0");
    nav->key_chain = NULL;
    
    return nav;
    
}

void navigatorMalloc(VaultNavigator* v_ptr, DataType type, int units, char* identifier)
{
    KeyChain* chain = initializeKeyChain(type, units, identifier);
    makeEntry(&v_ptr->map, chain, identifier);

    

    v_ptr->key_chain = chain;
}

void navigatorFree(VaultNavigator* v_ptr, char* identifier){
     
}

void storeData(VaultNavigator* v_ptr, char* identifier, void* data){
    
}

void accessData(VaultNavigator* v_ptr, char* identifier, void* dest){
   
}

void incrementPointer(VaultNavigator* v_ptr){
    
}

void decrementPointer(VaultNavigator* v_ptr){
    
}

void changePointer(VaultNavigator* v_ptr, char* identifier){
    
}
