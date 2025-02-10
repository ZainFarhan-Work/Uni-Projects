#ifndef KEYCHAIN_H
#define KEYCHAIN_H

#include "../include/key.h"

typedef struct KeyChain KeyChain;

KeyChain* initializeKeyChain(DataType type, int units, void* data);

KeyChain* keyChainMalloc(DataType type, int units, KeyChain* origin);

void keyChainFree(KeyChain* key_chain, KeyChain* origin);

void keyChainStoreData(KeyChain* key_chain, void* data);

void keyChainAccessData(KeyChain* key_chain, void* dest);

KeyChain* findKeyChain(KeyChain* origin, int index);

void keyChainMoveData(KeyChain* src, KeyChain* dest);

void keyChainClearData(KeyChain* origin);

void keyChainCompleteRelease(KeyChain* origin);

KeyChain* getNext(KeyChain* key_chain);

KeyChain* getPrevious(KeyChain* key_chain, KeyChain* origin);

Key* getKey(KeyChain* key_chain);

DataType getType(KeyChain* key_chain);

int getUnits(KeyChain* key_chain);

int getIndex(KeyChain* key_chain);

#endif