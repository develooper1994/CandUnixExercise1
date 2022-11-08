// ----------------------------- <doubleVector> -----------------------------------
#include "doublevector.h"

void initialize(DoubleVector* dv, size_t size){
    dv->data = (char*)malloc(sizeof(char)*size);
    dv->size = size;
    dv->__capacity = size;
}

void deallocate(DoubleVector* dv){
    free(dv->data);
    dv->data = NULL;
    dv->size = 0;
    dv->__capacity = 0;
}

void resize(DoubleVector* dv, int new_size){
    if (new_size + 1 > dv->__capacity){
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

void append(char* buffer, size_t buffer_size){
    char* buffer_new = (char*)realloc(buffer, sizeof(char)*buffer_size);
    for (size_t index = 0; index < buffer_size; ++index) {
        buffer_new[index] = buffer[index];
        //buffer[index] = NULL;
    }
    buffer = buffer_new;
}

void appendPointer(char** buffer, size_t buffer_size){
    char** buffer_new = (char**)realloc(buffer, sizeof(char)*buffer_size);
    for (size_t index = 0; index < buffer_size; ++index) {
        buffer_new[index] = buffer[index];
        //buffer[index] = NULL;
    }
    buffer = buffer_new;
}


// ----------------------------- </doubleVector> -----------------------------------