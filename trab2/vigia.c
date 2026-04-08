#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef struct Dynvec {
    
    void *data;
    size_t length;
    size_t capacity;
    size_t elem_size;
}dynvec;

static void dynvec_resize(dynvec *v, size_t new_capacity) {
    
    void *new_data = realloc(v->data, new_capacity * v->elem_size);
    
    if (new_data) {
        v->data = new_data;
        v->capacity = new_capacity;
    }
}

dynvec* dynvec_create(size_t elem_size) {
    
    dynvec *v = malloc(sizeof(dynvec));
    if (!v) {
        return NULL;
    }
    v->elem_size = elem_size;
    v->length = 0;
    v->capacity = 4;
    v->data = malloc(v->capacity * v->elem_size);
    return v;
}

void dynvec_push(dynvec *v, void *elem) {
    
    if (v->length == v->capacity){ 
        dynvec_resize(v, v->capacity * 2);
    }
    
    memcpy((char *)v->data + (v->length * v->elem_size), elem, v->elem_size);
    v->length++;
}

void* dynvec_get(dynvec *v, size_t index) {
    
    if (index >= v->length){
        return NULL;
    }
    return (char *)v->data + (index * v->elem_size);
}

size_t dynvec_length(dynvec *v) { 
    return v->length; 
}

void dynvec_free(dynvec *v) {
    
    if (v) { 
        free(v->data);
        free(v); 
    }
}

dynvec* dynvec_filter(dynvec *v, bool (*predicate)(void *)) {
    
    dynvec *novo = dynvec_create(v->elem_size);
    
    for (size_t i = 0; i < v->length; i++) {
        void *item = dynvec_get(v, i);
            if (predicate(item)){ 
            dynvec_push(novo, item);
            }
    }
    return novo;
}

typedef struct {
    
    int x;
    int y;
} Ponto;

typedef struct {
    
    Ponto p1;
    Ponto p2;
} Aresta;

int cmp_lexicografico(const void *a, const void *b){

}

int calcula_det(Ponto A, Ponto B, Ponto P){

}

void processa_regiao(Ponto A, Ponto B, dynvec *candidatos, dynvec *arestas_finais){
    
}

int main(){

}
