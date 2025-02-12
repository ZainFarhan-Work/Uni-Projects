#include "../include/key.h"

typedef struct KeyChain{
    Key* key;
    DataType type;
    int units;
    int index;
    struct KeyChain* next;

} KeyChain;

KeyChain* initializeKeyChain(DataType type, int units, void* data)
{

    KeyChain* origin = (KeyChain*) malloc(sizeof(KeyChain));

    if (origin == NULL)
    {
        return NULL;
    }

    origin->key = initializeKey(type, units, data);

    origin->type = type;
    origin->units = units;
    origin->index = 0;
    origin->next = NULL;
    
    return origin;

}

KeyChain* keyChainMalloc(DataType type, int units, KeyChain* origin)
{
    KeyChain* new = (KeyChain*) malloc(sizeof(KeyChain));

    if (new == NULL)
    {
        return NULL;
    }
    
    int index = 1;

    new->key = initializeKey(type, units, NULL);
    new->type = type;
    new->units = units;
    new->index = 0;
    new->next = NULL;

    if (origin == NULL)
    {
        return NULL;
    }

    KeyChain* temp;

    temp = origin;

    while (temp->next != NULL)
    {
        temp = temp->next;
        index++;
    }

    new->index = index;
    temp->next = new;

    return new;
    
}

void keyChainFree(KeyChain* key_chain, KeyChain* origin)
{
    if (origin == NULL)
    {
        return;
    }
    
    keyFree(key_chain->key);
    KeyChain* temp = origin;    

    while (temp->next != key_chain)
    {
        temp = temp->next;
    }

    temp->next = key_chain->next;
    free(key_chain);

    while (temp->next != NULL)
    {
        temp = temp->next;
        temp->index--;
    }
    
}

void keyChainStoreData(KeyChain* key_chain, void* data)
{
    keyStoreData(key_chain->key, data);
    
}

void keyChainAccessData(KeyChain* key_chain, void* dest)
{
    keyAccessData(key_chain->key, dest, key_chain->type, key_chain->units);  
}

KeyChain* findKeyChain(KeyChain* origin, int index)
{
    if (origin == NULL || index < 0)
    {
        return NULL;
    }
    
    KeyChain* temp = origin;

    while (temp->next != NULL && temp->index != index)
    {
        temp = temp->next;
    }

    if (temp->index == index)
    {
        return temp;
    }
    

    return NULL;
    
}

void keyChainMoveData(KeyChain* src, KeyChain* dest)
{
    // keyStoreData(dest->key, getLocker(src->key));

    // void* src_data = malloc(src->units * sizeof(getSize(src->type)));

    // keyChainAccessData( src, src_data);

    // keyStoreData(dest->key, (void*) src_data);

    // free(src_data);
}

KeyChain* getNext(KeyChain* key_chain)
{
    KeyChain* temp = findKeyChain(key_chain, key_chain->index + 1);

    return temp;
   
}

KeyChain* getPrevious(KeyChain* key_chain, KeyChain* origin)
{
    KeyChain* temp = findKeyChain(origin, key_chain->index - 1);

    return temp;
}

void keyChainClearData(KeyChain* origin)
{
    // clear the whole linked list

    if (origin == NULL)
    {
        return;
    }
    
    KeyChain* temp = origin;

    while (temp != NULL)
    {
        temp->units = 0;
        temp = temp->next;
    }
    
}

void keyChainCompleteRelease(KeyChain* origin)
{
    if (origin == NULL)
    {
        return;
    }
    
    KeyChain* temp = origin;
    KeyChain* temp2;

    do
    {
        temp2 = temp;

        keyFree(temp2->key);
        free(temp2);
        
        temp = temp->next;

    } while (temp != NULL);
    
}

/*
------------------------------------------------------------------------------
DO NOT EDIT THE FUNCTIONS BELOW - TESTING PURPOSES
*/

Key* getKey(KeyChain* key_chain){
    return key_chain->key;
}

DataType getType(KeyChain* key_chain){
    return key_chain->type;
}

int getUnits(KeyChain* key_chain){
    return key_chain->units;
}

int getIndex(KeyChain* key_chain){
    return key_chain->index;
}