#ifndef doublevector
#define doublevector
// ----------------------------- <doublevector> -----------------------------------
#include <stdlib.h>

#define KB                1024
#define MB                1024*1024
#define DEFAULT_DATA_SIZE MB*1
#define UNDEFINE  -1
#define SUCCESS 0

#define CAPACITY_FACTOR   1

typedef struct doubleVector{
    void* data;
    size_t size;
    size_t __capacity;
}DoubleVector;

DoubleVector* CreateDoubleVector(size_t size);
void DestroyDoubleVector(DoubleVector* dv);
int InitializeDoubleVector(DoubleVector* dv, size_t size);
void DeallocateDoubleVector(DoubleVector* dv);
void ResizeDoubleVector(DoubleVector* dv, size_t new_size);
void AppendDoubleVector(DoubleVector* dv, int element);
size_t AtDoubleVector(DoubleVector* dv, size_t index);
void PrintDoubleVectorReverse(DoubleVector* dv);
/*
// vector in c language
// https://stackoverflow.com/questions/4694401/how-to-replicate-vector-in-c
// https://aticleworld.com/implement-vector-in-c/
typedef struct sVector vector;
struct sVector{
    sVectorList vectorList;
    //function pointers
    int (*pfVectorTotal)(vector *);
    int (*pfVectorResize)(vector *, int);
    int (*pfVectorAdd)(vector *, void *);
    int (*pfVectorSet)(vector *, int, void *);
    void *(*pfVectorGet)(vector *, int);
    int (*pfVectorDelete)(vector *, int);
    int (*pfVectorFree)(vector *);
};

void vector_init(vector *v)
{
    //init function pointers
    v->pfVectorTotal = vectorTotal;
    v->pfVectorResize = vectorResize;
    v->pfVectorAdd = vectorPushBack;
    v->pfVectorSet = vectorSet;
    v->pfVectorGet = vectorGet;
    v->pfVectorFree = vectorFree;
    v->pfVectorDelete = vectorDelete;
    //initialize the capacity and allocate the memory
    v->vectorList.capacity = VECTOR_INIT_CAPACITY;
    v->vectorList.total = 0;
    v->vectorList.items = malloc(sizeof(void *) * v->vectorList.capacity);
}

int vectorResize(vector *v, int capacity)
{
    int  status = UNDEFINE;
    if(v)
    {
        void **items = realloc(v->vectorList.items, sizeof(void *) * capacity);
        if (items)
        {
            v->vectorList.items = items;
            v->vectorList.capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}
*/


// ----------------------------- </doublevector> -----------------------------------
#endif /* doublevector */
