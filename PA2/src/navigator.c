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
    int count = -1;
    int end = 0;

    do
    {
        count ++;

        if (getIdentifier(v_ptr->map, count) != NULL)
        {
            end = !strcmp(getIdentifier(v_ptr->map, count), "END");

            if (!strcmp(getIdentifier(v_ptr->map, count), identifier))
            {
                return;
            }
            
        }
        
    } while (!end);
    
    KeyChain* chain = keyChainMalloc(type, units, (KeyChain*) getAddress(v_ptr->map, 0));
    makeEntry(&v_ptr->map, chain, identifier);

    v_ptr->key_chain = chain;
}

void navigatorFree(VaultNavigator* v_ptr, char* identifier){
     
}

void storeData(VaultNavigator* v_ptr, char* identifier, void* data)
{
    if (!strcmp("origin", identifier))
    {
        return;
    }

    keyChainStoreData((KeyChain*) getPointer(v_ptr->map, identifier), data);    
    
}

void accessData(VaultNavigator* v_ptr, char* identifier, void* dest)
{
    if (!strcmp("origin", identifier))
    {
        return;
    }

    keyChainAccessData((KeyChain*) getPointer(v_ptr->map, identifier), dest);

}

void incrementPointer(VaultNavigator* v_ptr)
{
    int index = getIndex(v_ptr->key_chain);

    printf("INDEX: %d", index);

    v_ptr->key_chain = (KeyChain*) getAddress(v_ptr->map, index + 1);
    
}

void decrementPointer(VaultNavigator* v_ptr)
{
    // int index = getIndex(v_ptr->key_chain);

    // if (!strcmp(getIdentifier(v_ptr->map, index - 1), "origin"))
    // {
    //     return;
    // }
    
    // v_ptr->key_chain = (KeyChain*) getAddress(v_ptr->map, index - 1);
    
}

void changePointer(VaultNavigator* v_ptr, char* identifier)
{
    // if (!strcmp("origin", identifier))
    // {
    //     return;
    // }
    
    // v_ptr->key_chain = (KeyChain*) getPointer(v_ptr->map, identifier);
    
}
