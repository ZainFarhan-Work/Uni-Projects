#ifndef KEY_H
#define KEY_H

#include "datatype.h"

typedef struct Key Key;

Key* initializeKey(DataType type, int units, void* data);

Key* keyMalloc(DataType type, int units);

void keyFree(Key* key);

void keyStoreData(Key* key, void* data);

void keyAccessData(Key* key, void* var, DataType type, int units);

int getKeySize(Key* key);

void* getLocker(Key* key);

#endif