#include "../include/navigator.h"
#include "../include/keychain.h"
#include "../include/locator.h"
#include "../include/key.h"

typedef struct KeyChain{
    Key* key;
    DataType type;
    int units;
    int index;
    struct KeyChain* next;

} KeyChain;

typedef struct Locator {
    char* identifier;
    uintptr_t address;

} Locator;


void completeDeallocation(VaultNavigator** v_ptr)
{
    Locator* map = v_ptr[0]->map;
    printLocator(map);
    printf("Is Fragmented: %d", isFragmented((KeyChain*) map->address));
    printf("Here\n");

    keyChainCompleteRelease((KeyChain*) map->address);
    releaseMap(map);
    
    free(*v_ptr);
}

int isFragmented(KeyChain* origin)
{
    KeyChain* temp;

    if (origin == NULL)
    {
        return 0;
    }

    temp = origin;

    do
    {
        if (temp->key == NULL)
        {
            return 1;
        }

        temp = temp->next;
        
    } while (temp != NULL);
    
    return 0;
    
}

void printLocator(Locator* map)
{
    int index = 0;

    printf("-----------------------------------\n");

    do
    {
        map = map + 1;
        index++;

        if (map->identifier == NULL)
        {
            break;
        }

        printf("Index %d : %s : %ld\n", index, map->identifier, map->address);

    } while (1);

    printf("-----------------------------------\n");
        
}


// int main()
// {
//     KeyChain* chain = initializeKeyChain(RED, 120, "Hey Hello my man");
//     Locator* map = initializeMap(20, chain, "origin");

//     VaultNavigator* nav = initializeNavigator(20);

//     navigatorMalloc(nav, RED, 120, "element1");

//     // printLocator(map);
//     // printf("Is Fragmented: %d\n", isFragmented(chain));
// }


// ---------------- Instructions for Test cases --------------//

/*
You can create an int main() function below to test your escape.c.
To test escape.c, navigate to the src directory in the terminal. You can do this by "cd src".

Then run the following command:

gcc escape.c key.c keychain.c navigator.c locator.c -o test

And then:

./test

Delete your int main() afterwards, or comment it out because it will not let you test other files.
*/

