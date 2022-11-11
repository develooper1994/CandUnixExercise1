// ----------------------------- <myvector> -----------------------------------

// https://www.sanfoundry.com/c-program-implement-vector/
#include "myvector.h"
void vector_init(vector *v) {
    v->capacity = VECTOR_INIT_CAPACITY;
    v->total = 0;
    v->items = (void**)malloc(sizeof(void *) * v->capacity);
}
 
int vector_total(vector *v) {
    return v->total;
}
 
static void vector_resize(vector *v, int capacity) {
#ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", v->capacity, capacity);
#endif
 
    void **items = (void**)realloc(v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

void vector_add(vector *v, void *item) {
    if (v->capacity == vector_total(v))
        vector_resize(v, v->capacity * 2);
    v->items[v->total++] = item;
}

void vector_set(vector *v, int index, void *item) {
    if (index >= 0 && index < vector_total(v))
        v->items[index] = item;
}

void* vector_get(vector *v, int index) {
    if (index >= 0 && index < vector_total(v))
        return v->items[index];
    return NULL;
}

void vector_delete(vector *v, int index) {
    if (index < 0 || index >= vector_total(v))
        return;
 
    v->items[index] = NULL;
    int i;
    for (i = 0; i < vector_total(v) - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }
 
    v->total--;
 
    if (vector_total(v) > 0 && vector_total(v)== v->capacity / 4)
        vector_resize(v, v->capacity / 2);
}
 
void vector_free(vector *v) {
    free(v->items);
}

/*
void print_vector_reverse(vector *v){
    puts("vector_reverse");
    int total = vector_total(v);
    for (int reverse_index = total - 1; reverse_index >= 0; --reverse_index){
        void* element = vector_get(&v, reverse_index);
        //printf("%s", (char*)element);
        putchar(*(int*)element);
    }
    printf("\n");
}
*/

// ----------------------------- </myvector> -----------------------------------
