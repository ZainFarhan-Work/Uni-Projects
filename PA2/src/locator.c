#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Locator {
    char* identifier;
    uintptr_t address;

} Locator;

Locator* initializeMap(int num_allocations, void* addr, char* identifier)
{
    Locator* map = (Locator*) malloc(num_allocations * sizeof(Locator));

    map->identifier = identifier;
    map->address = (uintptr_t) addr;

    return map;
    
}

void releaseMap(Locator* map){
    
}

void clearMap(Locator* map)
{
    // free(map);
    
}

Locator* resizeMap(Locator* map, int new_num_allocs){
    
}

void makeEntry(Locator** map, void* addr, char* identifier)
{
    
    
}

void removeEntry(Locator* map, char* identifier){
     
}

void* getOrigin(Locator* map){
    
}

void* getPointer(Locator* map, char* identifier){
   
}

/*
------------------------------------------------------------------------------
DO NOT EDIT THE FUNCTIONS BELOW - TESTING PURPOSES
*/

uintptr_t getAddress(Locator* map, int index){
    return map[index].address;
}

char* getIdentifier(Locator* map, int index){
    return map[index].identifier;
}