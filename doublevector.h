#ifndef doublevector
#define doublevector
// ----------------------------- <doublevector> -----------------------------------
#include <stdlib.h>

#define KB                1024
#define MB                1024*1024
#define DEFAULT_DATA_SIZE MB*1

struct doubleVector{
    char* data;
    size_t size;
    size_t __capacity;
};

typedef struct doubleVector DoubleVector; 

void initialize(DoubleVector* dv, size_t size);
void deallocate(DoubleVector* dv);
void resize(DoubleVector* dv, size_t new_size);
void append(DoubleVector* dv, char element);
void appendPointer(DoubleVector** dv_pointer, DoubleVector* dv);

// ----------------------------- </doublevector> -----------------------------------
#endif /* doublevector */
