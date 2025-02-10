#include "../include/key.h"

typedef struct KeyChain{
    Key* key;
    DataType type;
    int units;
    int index;
    struct KeyChain* next;

} KeyChain;

KeyChain* initializeKeyChain(DataType type, int units, void* data){
    
}

KeyChain* keyChainMalloc(DataType type, int units, KeyChain* origin){
    
}

void keyChainFree(KeyChain* key_chain, KeyChain* origin){
    
}

void keyChainStoreData(KeyChain* key_chain, void* data){
    
}

void keyChainAccessData(KeyChain* key_chain, void* dest){
    
}

KeyChain* findKeyChain(KeyChain* origin, int index) {
    
}

void keyChainMoveData(KeyChain* src, KeyChain* dest) {
   
}

KeyChain* getNext(KeyChain* key_chain){
   
}

KeyChain* getPrevious(KeyChain* key_chain, KeyChain* origin){
   
}

void keyChainClearData(KeyChain* origin) {
    // clear the whole linked list
}

void keyChainCompleteRelease(KeyChain* origin) {
    
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