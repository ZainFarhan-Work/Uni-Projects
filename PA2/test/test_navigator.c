#include "../src/navigator.c"
#include "../src/escape.c"

int testInitialize(VaultNavigator* v_ptr, char* identifier, int units){
    int marks = 0;  

    if(!strcmp((char*)(getLocker(getKey((KeyChain*)((void*)getAddress(v_ptr->map, 0))))), identifier) && getUnits((KeyChain*)((void*)getAddress(v_ptr->map, 0))) == units){
        marks += 2;
    }

    if(v_ptr->key_chain == NULL && !strcmp(getIdentifier(v_ptr->map, 0), identifier)){
        marks += 2;
    }

    printf(" %d/%d\n", (int)marks, 4);

    return marks;    
}

int testMalloc(VaultNavigator* v_ptr, char* identifiers[], int units[], DataType types[]){
    int marks = 0;
    
    int valid = 1;
    for(int i = 1; i < 11; i++){
        navigatorMalloc(v_ptr, types[i], units[i], identifiers[i]);

        if(v_ptr->key_chain != (KeyChain*)((void*)getAddress(v_ptr->map, i))){
            valid = 0;
        }


        
    }



    for(int i = 0; i < 11; i++){
        navigatorMalloc(v_ptr, types[i], units[i], identifiers[i]);

        if(v_ptr->key_chain != getPointer(v_ptr->map, identifiers[10])){
            valid = 0;
        }
    }



    if(valid){
        marks += 2;
    }

    valid = 1;
    for(int i = 0; i < 11; i++){
        if(strcmp(getIdentifier(v_ptr->map, i), identifiers[i]) != 0 || getUnits((KeyChain*)((void*)getAddress(v_ptr->map, i))) != units[i] || getIndex((KeyChain*)((void*)getAddress(v_ptr->map, i))) != i || getType((KeyChain*)((void*)getAddress(v_ptr->map, i))) != types[i]){
            valid = 0;
        }
    }

    if(valid){
        marks += 3;
    }

    printf(" %d/%d\n", marks, 5);
    return marks;
}

int testStoreAccess(VaultNavigator* v_ptr, char* identifiers[]){
    int marks = 0;
    int int_1 = __INT_MAX__;
    float float_2 = (float)rand()/(float)RAND_MAX;
    double double_3 = (double)rand()/(double)RAND_MAX;
    char char_4 = 'a' + (rand() % 26);
    char char_5[11] = "HelloWorld";
    double double_6[2] = {(double)rand()/(double)RAND_MAX, (double)rand()/(double)RAND_MAX};
    float float_7[4] = {(float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX};
    int int_8[10] = {(int)rand(), (int)rand(), (int)rand(), (int)rand(), (int)rand(), (int)rand(), (int)rand(), (int)rand(), (int)rand(), (int)rand()};
    int int_9[5] = {(int)rand(), (int)rand(), (int)rand(), (int)rand(), (int)rand()};
    char char_10[6] = "CS200";

    void* datas[10] = {&int_1, &float_2, &double_3, &char_4, char_5, double_6, float_7, int_8, int_9, char_10};

    for(int i = 0; i < 10; i++){
        storeData(v_ptr, identifiers[i+1], datas[i]);
    }

    int int_1_access, int_8_access[10], int_9_access[5];
    double double_3_access, double_6_access[2];
    float float_2_access, float_7_access[4];
    char char_4_access, char_5_access[11], char_10_access[6];

    void* access[10] = {&int_1_access, &float_2_access, &double_3_access, &char_4_access, char_5_access, double_6_access, float_7_access, int_8_access, int_9_access, char_10_access};

    for(int i = 0; i < 10; i++){
        accessData(v_ptr, identifiers[i+1], access[i]);

    }

    int valid = 1;
    if(int_1 != int_1_access || float_2 != float_2_access || double_3 != double_3_access || char_4 != char_4_access || strcmp(char_5, char_5_access) != 0 || strcmp(char_10, char_10_access) != 0){
        valid = 0;
    }

    for(int i = 0; i < 10; i++){
        if((i < 2 && double_6[i] != double_6_access[i]) || (i < 4 && float_7[i] != float_7_access[i]) || (int_8[i] != int_8_access[i]) || (i < 5 && int_9[i] != int_9_access[i])){
            valid = 0;
            break;
        }
    }

    storeData(v_ptr, identifiers[0], char_10);

    if(strcmp(getIdentifier(v_ptr->map, 0), "origin") != 0){
        valid = 0;
    }

    if(valid){
        marks += 4;
    }

    valid = 1;

    printf(" %d/%d\n", marks, 4);
    return marks;
}

int testPointerOperations(VaultNavigator* v_ptr, char* identifiers[]){
    int marks = 0;

    v_ptr->key_chain = getOrigin(v_ptr->map);
    
    int valid = 1;
    for(int i = 0; i < 11; i++){
        if(v_ptr->key_chain != getPointer(v_ptr->map, identifiers[i])){
            valid = 0;
            break;
        }

        if(i < 10){
            incrementPointer(v_ptr);
        }
    }

    if(valid){
        marks += 1;
    }

    valid = 1;
    for(int i = 10; i > 0; i--){
        if(v_ptr->key_chain != getPointer(v_ptr->map, identifiers[i])){
            valid = 0;
            break;
        }

        if(i > 1){
            decrementPointer(v_ptr);
        }
    }

    decrementPointer(v_ptr);

    if(v_ptr->key_chain == getOrigin(v_ptr->map)){
        valid = 0;
    }

    if(valid){
        marks += 2;
    }

    valid = 1;
    for(int i = 1; i < 11; i++){
        if(i%2){
            changePointer(v_ptr, identifiers[i]);

            if(v_ptr->key_chain != getPointer(v_ptr->map, identifiers[i])){
                valid = 0;
                break;
            }
        }
    }

    changePointer(v_ptr, identifiers[0]);

    if(v_ptr->key_chain == getOrigin(v_ptr->map)){
        valid = 0;
    }

    if(valid){
        marks += 2;
    }

    printf(" %d/%d\n", marks, 5);
    return marks;
}

int testFree(VaultNavigator* v_ptr, char* identifiers[]){
    int marks = 0;

    for(int i = 0; i < 11; i++){
        if(i%2){
            navigatorFree(v_ptr, identifiers[i]);
        }
    }

    int valid = 1;
    for(int i = 0; i < 11; i++){
        if(i%2){
            if(getPointer(v_ptr->map, identifiers[i]) != NULL){
                valid = 0;
                break;
            }
        }
        else{
            if(i+2 < 11 && getNext(getPointer(v_ptr->map, identifiers[i])) != getPointer(v_ptr->map, identifiers[i+2])){
                valid = 0;
                break;
            }

            if(getPointer(v_ptr->map, identifiers[i]) != (void*)getAddress(v_ptr->map, i/2)){
                valid = 0;
                break;
            }
        }
    }

    if(valid){
        marks += 4;
    }

    printf("Here\n");
    printf("working?3\n");
    completeDeallocation(&v_ptr);

    printf(" %d/%d\n", marks, 4);
    return marks;
}

int main(){
    printf("\033[1m\033[36m\nTesting Vault Navigator:\n\n\033[0m");
    int total = 0;

    DataType types[11] = {RED, BLACK, GREEN, BLUE, RED, RED, BLUE, GREEN, BLACK, BLACK, RED};
    int units[11] = {7, 1, 1, 1, 1, 11, 2, 4, 10, 5, 6};
    char* identifiers[11] = {"origin", "int_1", "float_2", "double_3", "char_4", "char_5", "double_6", "float_7", "int_8", "int_9", "char_10"};

    VaultNavigator* v_ptr = initializeNavigator(10);

    printf("\033[35mTesting initialization:\033[0m");
    total += testInitialize(v_ptr, identifiers[0], units[0]);

    printf("\033[35mTesting malloc:\033[0m");
    total += testMalloc(v_ptr, identifiers, units, types);

    printf("\033[35mTesting store and access:\033[0m");
    total += testStoreAccess(v_ptr, identifiers);

    printf("\033[35mTesting navigator operations:\033[0m");
    total += testPointerOperations(v_ptr, identifiers);

    printf("\033[33musing navigator_free()\033[0m\n");

    printf("\033[35mTesting free:\033[0m");
    total += testFree(v_ptr, identifiers);

    FILE *file = fopen("test/temporary.txt", "w");
    if (file == NULL) {
        perror("Runtime error - rerun program");
        return 1;
    }

    fprintf(file, "%d\n%d", total, 25);
    fclose(file);
}