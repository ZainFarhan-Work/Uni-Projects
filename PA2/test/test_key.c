#include "../src/key.c"
#include <time.h>

int testInitialization(){
    int marks = 0;
    char* data = "HelloWorld";
    Key* key_01 = initializeKey(RED, 11, data);
    Key* key_0x = initializeKey(RED, 0, data);

    if(key_01->key_size == (sizeof(char) * 11) && !strcmp(data, ((char*)key_01->locker)) && key_0x == NULL){
        marks += 4;
    }

    free(key_01->locker);
    free(key_01);


    printf(" %d/%d\n", marks, 4);
    return marks;
}

int testMalloc(){
    int marks = 0;

    Key* key_1 = keyMalloc(BLUE, 1);
    Key* key_2 = keyMalloc(RED, 1);

    Key* key_x = keyMalloc(BLUE, 0);
    if(key_1->key_size == sizeof(double) && key_1->locker && key_2->key_size == sizeof(char) && key_2->locker && !key_x){
        marks += 3;
    }

    keyFree(key_1);
    keyFree(key_2);

    Key* key_3 = keyMalloc(BLACK, 10);
    
    /*
    If the below case fails, it means that the actual allocated
    memory is not of integer size. Hence, storing and then consequently 
    accessing it as an integer gives value mismatch.
    */
    int valid = 1;
    if(key_3->key_size == 10 * sizeof(int) && key_3->locker){
        for(int i = 0; i < 10; i++){
            ((int*)key_3->locker)[i] = i;
        }
        
        for(int i = 0; i < 10; i++){
            if(((int*)key_3->locker)[i] != i){
                valid = 0;
                break;
            }
        }
    }
    else{
        valid = 0;
    }

        if(valid){
        marks += 2;
    }


    keyFree(key_3);

    printf(" %d/%d\n", marks, 5);
    return marks;
}

int testStoreAccess(){
    int marks = 0;
    double b1 = (double)rand()/(double)RAND_MAX;
    char b2 = 'a' + (rand() % 26);
    float b3 = (float)rand()/(float)RAND_MAX;
    
    //units storage + access
    Key* key_1 = keyMalloc(BLUE, 1);
    Key* key_2 = keyMalloc(RED, 1);
    Key* key_3 = keyMalloc(GREEN, 1);

    keyStoreData(key_1, &b1);
    keyStoreData(key_2, &b2);
    keyStoreData(key_3, &b3);
    keyStoreData(NULL, &b3);
    keyStoreData(key_1, NULL);

    if(*((double*)key_1->locker) == b1 && *((char*)key_2->locker) == b2 && *((float*)key_3->locker) == b3){
        marks += 1;
    }

    double b1_temp;
    char b2_temp;
    float b3_temp;

    keyAccessData(key_1, &b1_temp, BLUE, 1);
    keyAccessData(key_2, &b2_temp, RED, 1);
    keyAccessData(key_3, &b3_temp, GREEN, 1);
    keyAccessData(key_2, NULL, RED, 1);
    keyAccessData(NULL, &b3_temp, GREEN, 1);

    if(b1_temp == b1 && b2_temp == b2 && b3_temp == b3){
        marks += 2;
    }

    keyFree(key_3);

    //Size mismatch
    //i) dest < src
    int temp1[3] = {__INT_MAX__, __INT_MAX__, __INT_MAX__};

    keyAccessData(key_1, &temp1[1], BLACK, 1);

    int corrupt_bit = 0;
    if(marks < 0 || marks > 3 || temp1[0] != __INT_MAX__ || temp1[2] != __INT_MAX__){
        corrupt_bit = 1;
        marks = 0;
    }

    keyFree(key_1);

    if(corrupt_bit){
        printf("\033[31m Stack corrupted\033[0m");
    }

    //ii) src < dest
    int temp2 = __INT_MAX__;

    keyAccessData(key_2, &temp2, BLACK, 1);
    
    // printf("\n temp2: %x | %x", __INT_MAX__, temp2);
    
    if(temp2 == __INT_MAX__){
        marks -= 1;
    }

    keyFree(key_2);

    //Non-unit storage + access
    Key* key_4 = keyMalloc(BLACK, 20);
    int store_b4[20];
    int access_b4[20];

    for(int i = 0; i < 20; i++){
        store_b4[i] = i;
    }

    keyStoreData(key_4, store_b4);

    int valid = 1;
    for(int i = 0; i < 20; i++){
        if(((int*)key_4->locker)[i] != store_b4[i]){
            valid = 0;
        }
    }

    keyAccessData(key_4, access_b4, BLACK, 20);

    for(int i = 0; i < 20; i++){
        if(access_b4[i] != ((int*)key_4->locker)[i]){
            valid = 0;
        }
    }

    if(valid){
        marks += 2;
    }
    
    keyFree(key_4);
    
    printf(" %d/%d\n", marks, 5);
    return marks;
}


int main(){
    printf("\033[32mThese 15 marks won't count towards your score!\033[0m");
    printf("\n");
    printf("\033[1m\033[36m\nTesting Key:\n\n\033[0m");
    srand(time(NULL));
    int total = 0;

    printf("\033[35mTesting initialization:\033[0m");
    total += testInitialization();

    printf("\033[33mkey_free() will be used from now\033[0m\n");

    printf("\033[35mTesting malloc:\033[0m");
    total += testMalloc();
    
    printf("\033[35mTesting data storage & access:\033[0m");
    total += testStoreAccess();

    FILE *file = fopen("test/temporary.txt", "w");
    if (file == NULL) {
        perror("Runtime error - rerun program");
        return 1;
    }

    fprintf(file, "%d\n%d", total, 15);
    fclose(file);
}