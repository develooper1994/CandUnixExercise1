// ----------------------------- <doublevector> -----------------------------------
#include "doublevector.h"
#include <stdio.h>
#include <stdlib.h>

DoubleVector* CreateDoubleVector(size_t size){
    DoubleVector* initialization = (DoubleVector*)malloc(sizeof(DoubleVector)*1);
    if (!initialization) {
        return NULL;
    }
    int ret = InitializeDoubleVector(initialization, size);
    if(ret == EXIT_FAILURE){
        free(initialization);
        return NULL;
    }

    return initialization;
}

void DestroyDoubleVector(DoubleVector* dv){
    DeallocateDoubleVector(dv);
    free(dv);
    dv = NULL;
}

int InitializeDoubleVector(DoubleVector* dv, size_t size){
    dv->data = (int*)malloc(sizeof(int)*size);
    if (!dv->data) 
        return EXIT_FAILURE;
    dv->size = 0;
    dv->__capacity = size;

    return EXIT_SUCCESS;
}

void DeallocateDoubleVector(DoubleVector* dv){
    free(dv->data);
    dv->data = NULL;
    dv->size = 0;
    dv->__capacity = 0;
}

int ResizeDoubleVector(DoubleVector* dv, size_t new_size){
    // https://cplusplus.com/forum/general/263662/
    if (new_size + 1 > dv->__capacity){
        // if data is not empty then resize otherwise allocate for it.
        int* new_data = dv->data ? 
            (int*)realloc(dv->data, new_size + 1) :
            (int*)malloc(sizeof(int)*(new_size + 1));
        if (new_data){
            dv->__capacity = new_size + 1;
            dv->size     = new_size;
            dv->data     = new_data;
        }
        else
            return EXIT_FAILURE;
    }
    else
        dv->size = new_size;

    return EXIT_SUCCESS;
}

int AppendDoubleVector(DoubleVector* dv, int element){
    // TODO: doesn't enter t the function due to "DoubleVector* dv"
    puts("<buffer_size>"); // debug
    size_t new_capacity = dv->__capacity * CAPACITY_FACTOR + 1;
    puts("<element_index>"); // debug
    size_t element_index = new_capacity - 1;
    puts("<ResizeDoubleVector>"); // debug
    int ret = ResizeDoubleVector(dv, new_capacity);

    if(ret == EXIT_FAILURE) return EXIT_FAILURE;

    puts("</ResizeDoubleVector>"); // debug
    dv->data[element_index] = element;
    puts("</dv->data[element_index] = element;>"); // debug

    return EXIT_SUCCESS;
}

size_t AtDoubleVector(DoubleVector* dv, size_t index){
    return dv->data[index];
}

void PrintDoubleVectorReverse(DoubleVector* dv){
    size_t buffer_size = dv->size;
    for (size_t index=buffer_size; index < buffer_size; --index) {
        putchar(AtDoubleVector(dv, index));
    }
}


// ----------------------------- </doublevector> -----------------------------------
