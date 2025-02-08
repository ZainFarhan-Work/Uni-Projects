#include "../src/keychain.c"

int testInitialization(KeyChain* origin, DataType type, int units, char* data){
    int marks = 0;

    if(origin->type == type && origin->units == units && origin->index == 0 && origin->next == NULL && getKeySize(origin->key) == (int)(sizeof(char) * units) && !strcmp(data, ((char*)getLocker(origin->key)))){
        marks += 3;
    }

    printf(" %d/%d\n", marks, 3);

    return marks;
}

int testMalloc(KeyChain* origin, KeyChain* keychain_1, KeyChain* keychain_2, KeyChain* keychain_3, DataType* types){
    int marks = 0;
    int valid_1 = 1;
    int valid_2 = 1;
    int i = 0;
    KeyChain* temp = origin;
    
    KeyChain* keychain_4 = keyChainMalloc(BLACK, 0, NULL);

    if(origin->next == keychain_1 && keychain_1->next == keychain_2 && keychain_2->next == keychain_3 && keychain_3->next == NULL && keychain_4 == NULL){
        marks += 2;
    }

    while(temp != NULL){
        if(temp->type != types[i]){
            valid_1 = 0;
            break;
        }

        if(temp->index != i){
            valid_2 = 0;
            break;
        }

        i++;
        temp = temp->next;
    }

    if(valid_1){
        marks += 1;
    }

    if(valid_2){
        marks += 2;
    }

    printf(" %d/%d\n", marks, 5);

    return marks;
}

int testFree(KeyChain* origin, KeyChain* keyChain_1, KeyChain* keyChain_2, KeyChain* keyChain_3, DataType* types){
    int marks = 0;
    int valid_link = 1;
    int valid_index = 1;
    KeyChain* keyChain_4 = keyChainMalloc(types[4], 2, origin);
    KeyChain* keyChain_5 = keyChainMalloc(types[5], 4, origin);
    KeyChain* keyChain_6 = keyChainMalloc(types[6], 11, origin);
    KeyChain* keyChain_7 = keyChainMalloc(types[7], 3, origin);
    KeyChain* keyChain_8 = keyChainMalloc(types[8], 5, origin);
    KeyChain* keyChain_9 = keyChainMalloc(types[9], 1, origin);

    keyChainFree(keyChain_7, origin);
    
    if(keyChain_6->next != keyChain_8){
        valid_link = 0;
    }

    if(keyChain_8->index != 7 || keyChain_9->index != 8){
        valid_index = 0;
    }

    keyChainFree(keyChain_5, origin);

    if(keyChain_4->next != keyChain_6){
        valid_link = 0;
    }

    if(keyChain_6->index != 5 || keyChain_8->index != 6 || keyChain_9->index != 7){
        valid_index = 0;
    }

    keyChainFree(keyChain_8, origin);

    if(keyChain_6->next != keyChain_9){
        valid_link = 0;
    }

    if(keyChain_9->index != 6){
        valid_index = 0;
    }
    
    keyChainFree(keyChain_9, origin);

    if(keyChain_6->next != NULL){
        valid_link = 0;
    }

    keyChainFree(keyChain_6, origin);

    if(keyChain_4->next != NULL){
        valid_link = 0;
    }

    if(keyChain_4->index != 4){
        valid_index = 0;
    }

    keyChainFree(keyChain_4, origin);

    if(origin->next != keyChain_1 || keyChain_1->next != keyChain_2 || keyChain_2->next != keyChain_3 || keyChain_3->next != NULL){
        valid_link = 0;
    }

    if(valid_link){
        marks += 2;
    }

    if(valid_index){
        marks += 3;
    }

    keyChainFree(keyChain_3, NULL);

    printf(" %d/%d\n", marks, 5);

    return marks;
}

int testStoreAccess(KeyChain* keyChain_1, KeyChain* keyChain_2, KeyChain* keyChain_3){
    int marks = 0;
    char p1[] = "HelloWorld";
    float p2 = (float)rand()/(float)RAND_MAX;
    double p3[] = {(double)rand()/(double)RAND_MAX, (double)rand()/(double)RAND_MAX};

    keyChainStoreData(keyChain_1, &p1);
    keyChainStoreData(keyChain_2, &p2);
    keyChainStoreData(keyChain_3, &p3);

    if(!strcmp(p1, ((char*)getLocker(keyChain_1->key))) && *((float*)getLocker(keyChain_2->key)) == p2 && (((double*)getLocker(keyChain_3->key))[0] == p3[0] && ((double*)getLocker(keyChain_3->key))[1] == p3[1])){
        marks += 1;
    }

    char p1_access[11];
    float p2_access;
    double p3_access[2];

    keyChainAccessData(keyChain_1, p1_access);
    keyChainAccessData(keyChain_2, &p2_access);
    keyChainAccessData(keyChain_3, p3_access);

    if(!strcmp(p1_access, p1) && p2_access == p2 && (p3_access[0] == p3[0] && p3_access[1] == p3[1])){
        marks += 1;
    }

    printf(" %d/%d\n", marks, 2);
    
    return marks;
}

int testClearDataandRelease(KeyChain *origin)
{
    int marks = 0;
    char *test_1 = "CS200";
    int test_2 = 200;
    char *test_3 = "Calloc";
    char *test_4 = "PA1";
    float test_5 = 100.0;

    KeyChain *node_1 = origin->next;
    KeyChain *node_2 = node_1->next;
    KeyChain *node_3 = node_2->next;
    KeyChain *node_4 = node_3->next;
    node_4->next = NULL;

    keyChainStoreData(origin, &test_1);
    keyChainStoreData(node_1, &test_2);
    keyChainStoreData(node_2, &test_3);
    keyChainStoreData(node_3, &test_4);
    keyChainStoreData(node_4, &test_5);

    keyChainClearData(origin);
    if (origin->units == 0 && node_1->units == 0 && node_2->units == 0 && node_3->units == 0 && node_4->units == 0)
    {
        marks += 2;
    }
    keyChainCompleteRelease(origin);
    if (origin->next == NULL && node_1->next == NULL && node_2->next == NULL && node_3->next == NULL && node_4->next == NULL)
    {
        marks += 1;
    }
    if (origin->key == NULL && node_1->key == NULL && node_2->key == NULL && node_3->key == NULL && node_4->key == NULL)
    {
        marks += 1;
    }
    
    printf("Marks: %d/%d\n", marks, 4);
    return marks;
}

int testMoveData(){
    KeyChain *node_1;
    KeyChain *node_2;
    int marks = 0;
    char *test = "testing-moving";
    keyChainStoreData(node_1, &test);
    keyChainMoveData(node_1, node_2);
    if (node_2->units == node_1->units && node_2->type == node_1->type && node_1->key==node_2->key)
    {
        marks += 4;
    }
    printf("Marks: %d/%d\n", marks, 4);
    return marks;
}

int testNextPrev(KeyChain* origin, KeyChain* keyChain_1, KeyChain* keyChain_2, KeyChain* keyChain_3){
    int marks = 0;

    KeyChain* origin_next = getNext(origin);
    KeyChain* p1_next = getNext(keyChain_1);
    KeyChain* p2_next = getNext(keyChain_2);
    KeyChain* p3_next = getNext(keyChain_3);

    if(origin_next == keyChain_1 && p1_next == keyChain_2 && p2_next == keyChain_3 && p3_next == NULL){
        marks += 2;
    }

    KeyChain* origin_prev = getPrevious(origin, origin);
    KeyChain* p1_prev = getPrevious(keyChain_1, origin);
    KeyChain* p2_prev = getPrevious(keyChain_2, origin);
    KeyChain* p3_prev = getPrevious(keyChain_3, origin);

    if(origin_prev == NULL && p1_prev == origin && p2_prev == keyChain_1 && p3_prev == keyChain_2){
        marks += 2;
    }

    printf(" %d/%d\n", marks, 4);

    return marks;
}

int main(){

    printf("\033[1m\033[36m\nTesting Key Chain:\n\n\033[0m");

    int total = 0;
    DataType types[10] = {RED, RED, GREEN, BLUE, BLACK, BLACK, RED, BLUE, GREEN, RED};

    printf("\033[35mTesting initialization:\033[0m");
    char* data = "CS200";
    int units = 6;
    KeyChain* origin = initializeKeyChain(types[0], units, data);
    total += testInitialization(origin, types[0], units, data);

    KeyChain* keyChain_1 = keyChainMalloc(types[1], 11, origin);
    KeyChain* keyChain_2 = keyChainMalloc(types[2], 1, origin);
    KeyChain* keyChain_3 = keyChainMalloc(types[3], 2, origin);

    printf("\033[35mTesting malloc:\033[0m");
    total += testMalloc(origin, keyChain_1, keyChain_2, keyChain_3, types);

    printf("\033[33mkey_free() will be used from now on\033[0m\n");

    printf("\033[35mTesting free:\033[0m");
    total += testFree(origin, keyChain_1, keyChain_2, keyChain_3, types);

    printf("\033[35mTesting store & access data:\033[0m");
    total += testStoreAccess(keyChain_1, keyChain_2, keyChain_3);

    printf("\033[35mTesting clear & release data:\033[0m");
    total += testClearDataandRelease(origin);

    printf("\033[35mTesting move data:\033[0m");
    total += testMoveData();

    printf("\033[35mTesting get next & previous:\033[0m");
    total += testNextPrev(origin, keyChain_1, keyChain_2, keyChain_3);

    keyChainCompleteRelease(origin);

    FILE *file = fopen("test/temporary.txt", "w");
    if (file == NULL) {
        perror("Runtime error - rerun program");
        return 1;
    }

    fprintf(file, "%d\n%d", total, 30);
    fclose(file);
}