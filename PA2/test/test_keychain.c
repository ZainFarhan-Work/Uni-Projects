#include "../src/keychain.c"

int testInitialization(KeyChain *origin, DataType type, int units, char *data)
{
    int marks = 0;

    if (origin->type == type && origin->units == units && origin->index == 0 && origin->next == NULL && getKeySize(origin->key) == (int)(sizeof(char) * units) && !strcmp(data, ((char *)getLocker(origin->key))))
    {
        marks += 3;
    }

    printf(" %d/%d\n", marks, 3);

    return marks;
}

int testMalloc(KeyChain *origin, KeyChain *keychain_1, KeyChain *keychain_2, KeyChain *keychain_3, DataType *types)
{
    int marks = 0;
    int valid_1 = 1;
    int valid_2 = 1;
    int i = 0;
    KeyChain *temp = origin;

    KeyChain *keychain_4 = keyChainMalloc(BLACK, 0, NULL);

    if (origin->next == keychain_1 && keychain_1->next == keychain_2 && keychain_2->next == keychain_3 && keychain_3->next == NULL && keychain_4 == NULL)
    {
        marks += 2;
    }

    while (temp != NULL)
    {
        if (temp->type != types[i])
        {
            valid_1 = 0;
            break;
        }

        if (temp->index != i)
        {
            valid_2 = 0;
            break;
        }

        i++;
        temp = temp->next;
    }

    if (valid_1)
    {
        marks += 1;
    }

    if (valid_2)
    {
        marks += 2;
    }

    printf(" %d/%d\n", marks, 5);

    return marks;
}

int testFree(KeyChain *origin, KeyChain *keyChain_1, KeyChain *keyChain_2, KeyChain *keyChain_3, DataType *types)
{
    int marks = 0;
    int valid_link = 1;
    int valid_index = 1;
    KeyChain *keyChain_4 = keyChainMalloc(types[4], 2, origin);
    KeyChain *keyChain_5 = keyChainMalloc(types[5], 4, origin);
    KeyChain *keyChain_6 = keyChainMalloc(types[6], 11, origin);
    KeyChain *keyChain_7 = keyChainMalloc(types[7], 3, origin);
    KeyChain *keyChain_8 = keyChainMalloc(types[8], 5, origin);
    KeyChain *keyChain_9 = keyChainMalloc(types[9], 1, origin);

    keyChainFree(keyChain_7, origin);

    if (keyChain_6->next != keyChain_8)
    {
        valid_link = 0;
    }

    if (keyChain_8->index != 7 || keyChain_9->index != 8)
    {
        valid_index = 0;
    }

    keyChainFree(keyChain_5, origin);

    if (keyChain_4->next != keyChain_6)
    {
        valid_link = 0;
    }

    if (keyChain_6->index != 5 || keyChain_8->index != 6 || keyChain_9->index != 7)
    {
        valid_index = 0;
    }

    keyChainFree(keyChain_8, origin);

    if (keyChain_6->next != keyChain_9)
    {
        valid_link = 0;
    }

    if (keyChain_9->index != 6)
    {
        valid_index = 0;
    }

    keyChainFree(keyChain_9, origin);

    if (keyChain_6->next != NULL)
    {
        valid_link = 0;
    }

    keyChainFree(keyChain_6, origin);

    if (keyChain_4->next != NULL)
    {
        valid_link = 0;
    }

    if (keyChain_4->index != 4)
    {
        valid_index = 0;
    }

    keyChainFree(keyChain_4, origin);

    if (origin->next != keyChain_1 || keyChain_1->next != keyChain_2 || keyChain_2->next != keyChain_3 || keyChain_3->next != NULL)
    {
        valid_link = 0;
    }

    if (valid_link)
    {
        marks += 2;
    }

    if (valid_index)
    {
        marks += 3;
    }

    keyChainFree(keyChain_3, NULL);

    printf(" %d/%d\n", marks, 5);

    return marks;
}

int testStoreAccess(KeyChain *keyChain_1, KeyChain *keyChain_2, KeyChain *keyChain_3)
{
    int marks = 0;
    char p1[] = "HelloWorld";
    float p2 = (float)rand() / (float)RAND_MAX;
    double p3[] = {(double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX};

    keyChainStoreData(keyChain_1, &p1);
    keyChainStoreData(keyChain_2, &p2);
    keyChainStoreData(keyChain_3, &p3);

    if (!strcmp(p1, ((char *)getLocker(keyChain_1->key))) && *((float *)getLocker(keyChain_2->key)) == p2 && (((double *)getLocker(keyChain_3->key))[0] == p3[0] && ((double *)getLocker(keyChain_3->key))[1] == p3[1]))
    {
        marks += 1;
    }

    char p1_access[11];
    float p2_access;
    double p3_access[2];

    keyChainAccessData(keyChain_1, p1_access);
    keyChainAccessData(keyChain_2, &p2_access);
    keyChainAccessData(keyChain_3, p3_access);

    if (!strcmp(p1_access, p1) && p2_access == p2 && (p3_access[0] == p3[0] && p3_access[1] == p3[1]))
    {
        marks += 1;
    }

    printf(" %d/%d\n", marks, 2);

    return marks;
}

int testClearData(KeyChain *origin)
{
    int marks = 0;

   keyChainClearData(origin);
    if (origin->units == 0 && origin->next->units == 0 && origin->next->next->units == 0 && origin->next->next->next->units == 0)
    {
        marks += 2;
    }
    printf(" %d/%d\n", marks, 2);
    return marks;
}

int testMoveData(KeyChain* origin,KeyChain* keyChain_1, KeyChain* keyChain_2, KeyChain* keyChain_3, DataType *types)
{
    int marks = 0;

    KeyChain *keyChain_t = keyChainMalloc(types[1], 15, origin);
    keyChainMoveData(keyChain_1, keyChain_t);

    Key* key1 = getKey(keyChain_1);
    Key* keyt = getKey(keyChain_t);

    if(!strcmp(((char*)getLocker(keyChain_t->key)), ((char *)getLocker(keyChain_1->key)))){
        marks += 1;
    }

    KeyChain *keyChain_a = keyChainMalloc(types[2], 15, origin);
    keyChainMoveData(keyChain_2, keyChain_a);

    Key* key2 = getKey(keyChain_2);
    Key* keya = getKey(keyChain_a);

    
    if(!strcmp(((char*)getLocker(keyChain_a->key)), ((char *)getLocker(keyChain_2->key)))){
        marks += 1;
    }

    KeyChain *keyChain_z = keyChainMalloc(types[3], 15, origin);
    keyChainMoveData(keyChain_3, keyChain_z);

    Key* key3 = getKey(keyChain_3);
    Key* keyz = getKey(keyChain_z);

    
    if(!strcmp(((char*)getLocker(keyChain_z->key)), ((char *)getLocker(keyChain_3->key)))){
        marks +=2;
    }



    printf(" %d/%d\n", marks, 4);
    return marks;
}

int testFind(KeyChain* origin, KeyChain* keyChain_2, KeyChain *keyChain_3){
    int marks = 0;

    int a = getIndex(keyChain_2);
    int b = getIndex(keyChain_3);
    
    KeyChain *keyChain_a = findKeyChain(origin, a);
    KeyChain *keyChain_b = findKeyChain(origin, b);
    KeyChain *keyChain_c = findKeyChain(origin, 10);

    if (keyChain_a == keyChain_2){
        marks ++;
    }

    if (keyChain_b == keyChain_3){
        marks ++;
    }
    if (keyChain_c){
        marks --;
    }
    if (marks == -1){
        marks ++;
    }
    printf(" %d/%d\n", marks, 2);
    return marks;
}


int testNextPrev(KeyChain *origin, KeyChain *keyChain_1, KeyChain *keyChain_2, KeyChain *keyChain_3)
{
    int marks = 0;

    KeyChain *origin_next = getNext(origin);
    KeyChain *p1_next = getNext(keyChain_1);
    KeyChain *p2_next = getNext(keyChain_2);
    KeyChain *p3_next = getNext(keyChain_3);

    if (origin_next == keyChain_1 && p1_next == keyChain_2 && p2_next == keyChain_3 && p3_next == NULL)
    {
        marks += 2;
    }

    KeyChain *origin_prev = getPrevious(origin, origin);
    KeyChain *p1_prev = getPrevious(keyChain_1, origin);
    KeyChain *p2_prev = getPrevious(keyChain_2, origin);
    KeyChain *p3_prev = getPrevious(keyChain_3, origin);

    if (origin_prev == NULL && p1_prev == origin && p2_prev == keyChain_1 && p3_prev == keyChain_2)
    {
        marks += 2;
    }

    printf(" %d/%d\n", marks, 4);

    return marks;
}

int main()
{

    printf("\033[1m\033[36m\nTesting Key Chain:\n\n\033[0m");

    int total = 0;
    DataType types[10] = {RED, RED, GREEN, BLUE, BLACK, BLACK, RED, BLUE, GREEN, RED};

    printf("\033[35mTesting initialization:\033[0m");
    char *data = "CS200";
    int units = 6;
    KeyChain *origin = initializeKeyChain(types[0], units, data);
    total += testInitialization(origin, types[0], units, data);

    KeyChain *keyChain_1 = keyChainMalloc(types[1], 11, origin);
    KeyChain *keyChain_2 = keyChainMalloc(types[2], 1, origin);
    KeyChain *keyChain_3 = keyChainMalloc(types[3], 2, origin);

    printf("\033[35mTesting malloc:\033[0m");
    total += testMalloc(origin, keyChain_1, keyChain_2, keyChain_3, types);

    printf("\033[33mkey_free() will be used from now on\033[0m\n");

    printf("\033[35mTesting free:\033[0m");
    total += testFree(origin, keyChain_1, keyChain_2, keyChain_3, types);

    printf("\033[35mTesting store & access data:\033[0m");
    total += testStoreAccess(keyChain_1, keyChain_2, keyChain_3);

    printf("\033[35mTesting get next & previous:\033[0m");
    total += testNextPrev(origin, keyChain_1, keyChain_2, keyChain_3);

    printf("\033[35mTesting move data:\033[0m");
    total += testMoveData(origin, keyChain_1,keyChain_2, keyChain_3, types);

    printf("\033[35mTesting find:\033[0m");
    total += testFind(origin, keyChain_2,keyChain_3);

    printf("\033[35mTesting clear & release data:\033[0m");
    total += testClearData(origin);

    keyChainCompleteRelease(origin);

    FILE *file = fopen("test/temporary.txt", "w");
    if (file == NULL)
    {
        perror("Runtime error - rerun program");
        return 1;
    }

    fprintf(file, "%d\n%d", total, 30);
    fclose(file);
}