// ----------------------------- <doublevector> -----------------------------------
#include "doublevector.h"
#include <stdio.h>

DoubleVector* CreateDoubleVector(size_t size){
    DoubleVector* initialization = (DoubleVector*)malloc(sizeof(DoubleVector)*1);
    InitializeDoubleVector(initialization, size);
    return initialization;
}

void DestroyDoubleVector(DoubleVector* dv){
    DeallocateDoubleVector(dv);
    free(dv);
    dv = NULL;
}

void InitializeDoubleVector(DoubleVector* dv, size_t size){
    dv->data = (int*)malloc(sizeof(int)*size);
    dv->size = size;
    dv->__capacity = size;
}

void DeallocateDoubleVector(DoubleVector* dv){
    free(dv->data);
    dv->data = NULL;
    dv->size = 0;
    dv->__capacity = 0;
}

void ResizeDoubleVector(DoubleVector* dv, size_t new_size){
    // https://cplusplus.com/forum/general/263662/
    if (new_size + 1 > dv->__capacity){
        // if data is not empty then resize otherwise allocate for it.
        int* new_data = dv->data ? 
            (int*)realloc( dv->data, new_size + 1 )
            : (int*)malloc( new_size + 1 );
        if (new_data){
            dv->__capacity = new_size + 1;
            dv->size     = new_size;
            dv->data     = new_data;
        }
    }
    else
        dv->size = new_size;
}

void AppendDoubleVector(DoubleVector* dv, int element){
    size_t buffer_size = dv->__capacity * CAPACITY_FACTOR + 1;
    size_t element_index = buffer_size - 1;
    ResizeDoubleVector(dv, buffer_size);
    dv->data[element_index] = element;
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
