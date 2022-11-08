#ifndef doublevector
#define doublevector
// ----------------------------- <doubleVector> -----------------------------------
#include <stdlib.h>

struct doubleVector{
    char* data;
    size_t size;
    size_t __capacity;
};

typedef struct doubleVector DoubleVector; 

void initialize(DoubleVector* dv, size_t size);
void deallocate(DoubleVector* dv);
void resize(DoubleVector* dv, int new_size);
void append(char* buffer, size_t size);
void appendPointer(char** buffer, size_t buffer_size);

// ----------------------------- </doubleVector> -----------------------------------
#endif /* doublevector */