// ----------------------------- <doublevector> -----------------------------------
#include "doublevector.h"

void initialize(DoubleVector* dv, size_t size){
    dv->data = (char*)malloc(sizeof(char)*size);
    dv->size = size;
    dv->__capacity = size;
}

void deallocate(DoubleVector* dv){
    free(dv->data);
    dv->data = NULL; // TODO: ???
    dv->size = 0;
    dv->__capacity = 0;
}

void resize(DoubleVector* dv, size_t new_size){
    // https://cplusplus.com/forum/general/263662/
    if (new_size + 1 > dv->__capacity){
        // if data is not empty then resize otherwise allocate for it.
        char* new_data = dv->data ? 
            (char*)realloc( dv->data, new_size + 1 )
            : (char*)malloc( new_size + 1 );
        if (new_data){
            dv->__capacity = new_size + 1;
            dv->size     = new_size;
            dv->data     = new_data;
        }
    }
    else
        dv->size = new_size;
}

void append(DoubleVector* dv, char element){
    size_t buffer_size = dv->__capacity * CAPACITY_FACTOR + 1;
    size_t element_index = buffer_size - 1;
    resize(dv, buffer_size);
    dv->data[element_index] = element;
}

void appendPointer(DoubleVector** dv_pointer, DoubleVector* dv){
    DoubleVector* dv_temp = *dv_pointer; // TODO: ???
    size_t buffer_size = dv_temp->__capacity * CAPACITY_FACTOR + 1;
    size_t element_index = buffer_size - 1;
    resize(*dv_pointer, buffer_size);
    dv->data[element_index] = element;
    
}


// ----------------------------- </doublevector> -----------------------------------
