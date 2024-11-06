#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *RandomHashFun(int M, int n) {
    int *fnTable = (int *)malloc(M * sizeof(int));
    if (fnTable == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int x = 0; x < M; x++) {
        fnTable[x] = rand() % n;
    }

    return fnTable;
}

int randomFn(int *fnTable, int x) {
    return fnTable[x];
}

int main() {
    srand(time(NULL));

    int M = 5;
    int n = 10;
    int *fnTable = RandomHashFun(M, n);

    printf("randomFn(0) = %d\n", randomFn(fnTable, 0));
    printf("randomFn(1) = %d\n", randomFn(fnTable, 1));
    printf("randomFn(2) = %d\n", randomFn(fnTable, 2));
    printf("randomFn(3) = %d\n", randomFn(fnTable, 3));
    printf("randomFn(4) = %d\n", randomFn(fnTable, 4));
    printf("randomFn(0) = %d\n", randomFn(fnTable, 0));


    free(fnTable);

    return 0;
}
