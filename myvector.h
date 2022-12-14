#ifndef myvector
#define myvector
// ----------------------------- <myvector> -----------------------------------
/*
Usage:

int i;
 
    vector v;
    vector_init(&v);
 
    vector_add(&v, "Bonjour");
    vector_add(&v, "tout");
    vector_add(&v, "le");
    vector_add(&v, "monde");
 
    for (i = 0; i < vector_total(&v); i++)
        printf("%s ", (char *) vector_get(&v, i));
    printf("\n");
 
    vector_delete(&v, 3);
    vector_delete(&v, 2);
    vector_delete(&v, 1);
 
    vector_set(&v, 0, "Hello");
    vector_add(&v, "World");
 
    for (i = 0; i < vector_total(&v); i++)
        printf("%s ", (char *) vector_get(&v, i));
    printf("\n");
 
    vector_free(&v);
*/
#include <stdio.h>
#include <stdlib.h>
 
#ifndef MYVECTOR_H
#define MYVECTOR_H
 
#define VECTOR_INIT_CAPACITY 4
 
#define VECTOR_INIT(vec) vector vec; vector_init(&vec)
#define VECTOR_ADD(vec, item) vector_add(&vec, (void *) item)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, (void *) item)
#define VECTOR_GET(vec, type, id) (type) vector_get(&vec, id)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_TOTAL(vec) vector_total(&vec)
#define VECTOR_FREE(vec) vector_free(&vec)
 
struct vector {
    void **items;
    int capacity;
    int total;
};

typedef struct vector vector;
 
#endif
 
void vector_init(vector *v);
int vector_total(vector *v);
static void vector_resize(vector *v, int capacity);
void vector_add(vector *v, void *item); 
void vector_set(vector *v, int index, void *item); 
void *vector_get(vector *v, int index); 
void vector_delete(vector *v, int index); 
void vector_free(vector *v);
//void print_vector_reverse(vector *v);

// ----------------------------- </myvector> -----------------------------------
#endif
