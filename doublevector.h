#ifndef doublevector
#define doublevector
// ----------------------------- <doublevector> -----------------------------------
#include <stdlib.h>

#define KB                1024
#define MB                1024*1024
#define DEFAULT_DATA_SIZE MB*1

#define CAPACITY_FACTOR   1

struct doubleVector{
    int* data;
    size_t size;
    size_t __capacity;
};

typedef struct doubleVector DoubleVector; 
DoubleVector* CreateDoubleVector(size_t size);
void DestroyDoubleVector(DoubleVector* dv);
void InitializeDoubleVector(DoubleVector* dv, size_t size);
void DeallocateDoubleVector(DoubleVector* dv);
void ResizeDoubleVector(DoubleVector* dv, size_t new_size);
void AppendDoubleVector(DoubleVector* dv, int element);
size_t AtDoubleVector(DoubleVector* dv, size_t index);
void PrintDoubleVectorReverse(DoubleVector* dv);

// ----------------------------- </doublevector> -----------------------------------
#endif /* doublevector */
