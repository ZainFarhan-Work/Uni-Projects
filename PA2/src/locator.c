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

    map[num_allocations + 1].identifier = "END\0";

    return map;
    
}


void releaseMap(Locator* map)
{
    free(map); 
}


void clearMap(Locator* map)
{
    Locator* temp;
    int count = -1;
    int end = 0;

    do
    {
        count++;
        temp = map + count;

        if (temp->identifier != NULL)
        {
            end = !strcmp(temp->identifier, "END");
        }
        

        if (!end)
        {
            temp->identifier = NULL;
            temp->address = (uintptr_t) NULL;   
        }

    } while (!end);

}


Locator* resizeMap(Locator* map, int new_num_allocs)
{
    Locator* new_map = initializeMap(new_num_allocs, NULL, NULL);
    Locator* temp;
    int count = -1;
    int end = 0;
    
    do
    {
        count++;
        temp = map + count;

        if (temp->identifier != NULL)
        {
            end = !strcmp(temp->identifier, "END");
        }

        if (!end)
        {
            new_map[count] = *temp;
        }
        

    } while (!end);

    releaseMap(map);

    return new_map;
    
}


void makeEntry(Locator** map, void* addr, char* identifier)
{
    int count = -1;
    Locator* temp;
    int end = 0;
    
    do
    {
        count++;
        temp = *map + count;

        if (temp->identifier != NULL)
        {
            end = !strcmp(temp->identifier, "END");
        }

    } while (temp->identifier != NULL && !end);

    if (end)
    {
        *map = resizeMap(*map, (count - 1) * 2);

        count = -1;

        do
        {
            count++;
            temp = *map + count;

            if (temp->identifier != NULL)
            {
                end = !strcmp(temp->identifier, "END");
            }

        } while (temp->identifier != NULL && !end);

    }
    
    temp->identifier = identifier;
    temp->address = (uintptr_t) addr;
    
}


void removeEntry(Locator* map, char* identifier)
{
    Locator* temp;
    int count = -1;
    int match = 0;
    int end = 0;

    if (map[0].identifier == identifier)
    {
        // Check if the Rest of the Array is Empty
        int empty = 1;

        do
        {
            count++;
            temp = map + count;

            if (temp->identifier != NULL)
            {
                end = !strcmp(temp->identifier, "END");

                if (!end)
                {
                    empty = 0;
                    break;
                }
            }

        } while (!end);

        if (empty)
        {
            map[0].identifier = NULL;
            map[0].address = (uintptr_t) NULL;
            return;
        }

        return;
        
    }
    
    do
    {
        count++;
        temp = map + count;

        if (temp->identifier != NULL)
        {
            match = !strcmp(temp->identifier, identifier);
            end = !strcmp(temp->identifier, "END");
        }

    } while (!match && !end);

    if (end)
    {
        return;
    }

    do
    {
        if (map[count + 1].identifier != NULL)
        {
            end = !strcmp(map[count + 1].identifier, "END");
        }

        if (!end)
        {
            temp->identifier = map[count + 1].identifier;
            temp->address = map[count + 1].address;
        }
        else
        {
            temp->identifier = NULL;
            temp->address = (uintptr_t) NULL;
        }
        
        count++;
        temp = map + count;

    } while (!end);
     
}


void* getOrigin(Locator* map)
{
    if (map[0].identifier == NULL)
    {
        return NULL;
    }

    return (void*) map[0].address;
    
}


void* getPointer(Locator* map, char* identifier)
{
    Locator* temp;
    int count = -1;
    int match = 0;
    int end = 0;

    do
    {
        count++;
        temp = map + count;

        if (temp->identifier != NULL)
        {
            match = !strcmp(temp->identifier, identifier);
            end = !strcmp(temp->identifier, "END");
        }

    } while (!match && !end);

    if (end)
    {
        return NULL;
    }

    return (void*) temp->address;
   
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