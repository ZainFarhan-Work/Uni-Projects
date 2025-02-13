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
    Locator* map = (Locator*) malloc((num_allocations + 2) * sizeof(Locator));

    if (map == NULL)
    {
        return NULL;
    }
    
    for (int i = 0; i < num_allocations + 1; i++)
    {
        map[i].identifier = NULL;
        map[i].address = (uintptr_t) NULL;
    }

    map[0].identifier = identifier;
    map[0].address = (uintptr_t) addr;

    map[num_allocations + 1].identifier = "END";

    return map;
    
}

void releaseMap(Locator* map){
    
}

void clearMap(Locator* map)
{
    // free(map);
    
}

Locator* resizeMap(Locator* map, int new_num_allocs)
{
    Locator* new_map = initializeMap(new_num_allocs, NULL, NULL);
    Locator* temp;
    int count = -1;
    
    do
    {
        count++;
        temp = map + count;

        if (temp->identifier != "END")
        {
            new_map[count] = *temp;
        }
        

    } while (temp->identifier != "END");

    clearMap(map);

    return new_map;
    
}

void makeEntry(Locator** map, void* addr, char* identifier)
{
    int count = -1;
    Locator* temp;
    
    do
    {
        count++;
        temp = *map + count;

    } while (temp->identifier != NULL && temp->identifier != "END");

    if (temp->identifier == "END")
    {
        *map = resizeMap(*map, (count - 1) * 2);

        count = -1;

        do
        {
            count++;
            temp = *map + count;

        } while (temp->identifier != NULL && temp->identifier != "END");

    }
    
    temp->identifier = identifier;
    temp->address = (uintptr_t) addr;
    
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