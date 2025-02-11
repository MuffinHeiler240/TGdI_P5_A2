//
// Created by jonat on 30.12.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ZEILEN 4
#define SPALTEN 4

typedef struct matrix_struct {
    unsigned short n;
    unsigned short m;
    int **data;
} matrix_struct;
typedef struct matrix_struct *matrix;

matrix createMatrix(unsigned short n, unsigned short m) {
    unsigned short i;
    matrix a = (matrix) malloc(sizeof(matrix_struct));
    a->n = n;
    a->m = m;
    a->data = (int **) calloc(n, sizeof(int *));
    for (i = 0; i < n; i++) {
        a->data[i] = (int *) calloc(m, sizeof(int));
    }
    return a;
}

unsigned short rows(matrix a) {
    return a->n;
}

unsigned short cols(matrix a) {
    return a->m;
}

int getEntry(matrix a, unsigned short r, unsigned short c) {
    if (r >= a->n || c >= a->m) {
        printf("Error: index out of bounds\n");
        exit(-1);
    }
    return a->data[r][c];
}

void setEntry(matrix a, unsigned short r, unsigned short c, int v) {
    if (r >= a->n || c >= a->m) {
        printf("Error: index out of bounds\n");
        exit(-1);
    }
    a->data[r][c] = v;
}

typedef struct vector_struct {
    unsigned short n;
    int *data;
} vector_struct;
typedef struct vector_struct *vector;

vector createVector(unsigned short n) {
    vector v = (vector) malloc(sizeof(vector_struct));
    v->n = n;
    v->data = (int *) calloc(n, sizeof(int));
    return v;
}

unsigned short size(vector v) {
    return v->n;
}

vector createVectorWithOne(unsigned short n) {
    vector v = createVector(n);
    unsigned short i;
    for (i = 0; i < n; i++) {
        setValue(v,i,1);
    }
    return v;
}

int getValue(vector v, unsigned short j) {
    if( j >= v->n) {
        printf("Error: index out of bounds\n");
        exit(-1);
    }
    return v->data[j];
}

void setValue(vector v, unsigned short j, int value) {
    if( j >= v->n) {
        printf("Error: index out of bounds\n");
        exit(-1);
    }
    v->data[j] = value;
}

vector matrixDotVector(matrix a, vector x) {
    unsigned short i,j;
    if (a->m != size(x)) {
        printf("Error: matrix dimensions do not match\n");
        exit(-1);
    }
    vector y = createVectorWithOne(a->n);
    for (i = 0; i < a->n; i++) {
        for (j = 0; j < a->m; j++) {
            setValue(y,i, (a->data[i][j] * getValue(x,j)+getValue(y,i)));
        }
    }
    return y;
}

vector matrixDotVectorWithTempVar(matrix a, vector x) {
    unsigned short i,j;
    int temp = 0;
    if (a->m != size(x)) {
        printf("Error: matrix dimensions do not match\n");
        exit(-1);
    }
    vector y = createVectorWithOne(a->n);
    for (i = 0; i < a->n; i++) {
        for (j = 0; j < a->m; j++) {
            temp += a->data[i][j] * getValue(x,j);
        }
        setValue(y,i,temp);
        temp = 0;
    }
    return y;
}

matrix random_matrix(matrix m) {
    unsigned short i,j;
    for ( i = 0; i < rows(m); i++) {
        for (j= 0; j < cols(m); j++) {
            setEntry(m,i,j,(rand() % 65)-32);
        }
    }
    return m;
}

vector random_vector(vector v) {
    unsigned short i;
    for (i = 0; i < size(v); i++) {
        setValue(v,i, (rand() % 65)-32);
    }
    return  v;
}

void print_matrix(matrix m) {
    unsigned short i,j;
    for ( i = 0; i < rows(m); i++) {
        for (j= 0; j < cols(m); j++) {
            printf("%4.0d |", getEntry(m,i,j));
        }
        printf("\n");
    }
}

void print_vector(vector v) {
    unsigned short i;
    for (i = 0; i < size(v); i++) {
        printf("%4.0d \n", getValue(v,i));
    }
    printf("\n");
}

int main(void) {
    unsigned short i, print = 0;
    srand((unsigned int)time(NULL));

    for (i = 2; i <= 200; i++) {
        matrix m = createMatrix(i, i);
        random_matrix(m);

        vector v = createVector(i);
        random_vector(v);

        clock_t start, end;
        double time_req, time_reqVar;

        // Timing first function
        start = clock();
        vector result = matrixDotVector(m, v);
        end = clock();
        time_req = (double)(end - start) / CLOCKS_PER_SEC;

        // Timing second function
        start = clock();
        result = matrixDotVectorWithTempVar(m, v);
        end = clock();
        time_reqVar = (double)(end - start) / CLOCKS_PER_SEC;

        if (print != 0) {
            printf("Matrix A:\n");
            print_matrix(m);
            printf("\n");
            printf("Vector b:\n");
            print_vector(v);
            printf("Matrix A * Vector b:\n");
            print_vector(result);
        }

        printf("%d;", i);
        printf("%.6f;", time_req);
        printf("%.6f\n", time_reqVar);


        //printf("i = %d\n", i);
        //printf("Time     : %.6f seconds\n", time_req);
        //printf("Time Temp: %.6f seconds\n\n", time_reqVar);
    }


    return 0;

}


