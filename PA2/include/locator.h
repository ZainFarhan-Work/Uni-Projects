#ifndef LOCATOR_H
#define LOCATOR_H

#include <stdint.h>

typedef struct Locator Locator;

Locator* initializeMap(int num_allocations, void* addr, char* identifier);

void releaseMap(Locator* map);

void clearMap(Locator* map);

Locator* resizeMap(Locator* map, int new_num_allocs);

void makeEntry(Locator** map, void* addr, char* identifier);

void removeEntry(Locator* map, char* identifier);

void* getOrigin(Locator* map);

void* getPointer(Locator* map, char* identifier);

uintptr_t getAddress(Locator* map, int index);

char* getIdentifier(Locator* map, int index);

#endif