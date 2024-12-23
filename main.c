#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ZEILEN 4
#define SPALTEN 4
#include "matrix.h"
#include "vector.h"

matrix random_matrix(matrix m) {
    int i,j;
    for ( i = 0; i < rows(m); i++) {
        for (j= 0; j < cols(m); j++) {
            setEntry(m,i,j,(rand() % 65)-32);
        }
    }
    return m;
}

vector random_vector(vector v) {
    int i;
    for (i = 0; i < rows(v); i++) {
        setValue(v,i, (rand() % 65)-32);
    }
    return  v;
}

void print_matrix(matrix m) {
    int i,j;
    for ( i = 0; i < rows(m); i++) {
        for (j= 0; j < cols(m); j++) {
            printf("%4.0f |", getEntry(m,i,j));
        }
        printf("\n");
    }
}

void print_vector(vector v) {
    int i;
    for (i = 0; i < rows(v); i++) {
        printf("%4.0f \n", getValue(v,i));
    }
    printf("\n");
}

int main(void) {
    int i,print = 0;

    for(i = 2; i <=200;i++) {
        srand(time(NULL));

        matrix m = createMatrix(i, i);
        random_matrix(m);

        vector v = createVector(i);
        random_vector(v);

        clock_t time_req, time_reqEnd;
        time_req = clock();
        vector result = matrixDotVector(m,v);
        time_reqEnd = clock();

        clock_t time_reqVar, time_reqVarEnd;
        time_reqVar = clock();
        result = matrixDotVectorWithTempVar(m,v);
        time_reqVarEnd = clock();


        if(print != 0){
            printf("Matrix A:\n");
            print_matrix(m);
            printf("\n");
            printf("Vektor b:\n");
            print_vector(v);
            printf("Matrix A * Vektor b:\n");
            print_vector(result);
        }
        printf("Time     : %15ld\n", (time_req - time_reqEnd)/CLOCKS_PER_SEC);
        printf("Time Temp: %15ld\n", (time_reqVar- time_reqVarEnd)/CLOCKS_PER_SEC);
    }

    return 0;

}
