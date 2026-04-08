#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "dynvec.h"

struct Dynvec {
    void *data;
    size_t length;
    size_t capacity;
    size_t elem_size;
};

//Privada: Redimensiona
static void dynvec_resize(dynvec *v, size_t new_capacity) {
    void *new_data = realloc(v->data, new_capacity * v->elem_size);
    if (new_data) {
        v->data = new_data;
        v->capacity = new_capacity;
    }
}

//Principais 
dynvec* dynvec_create(size_t elem_size) {
    dynvec *v = malloc(sizeof(dynvec));
    if (!v) return NULL;
    v->elem_size = elem_size;
    v->length = 0;
    v->capacity = 4;
    v->data = malloc(v->capacity * v->elem_size);
    return v;
}

void dynvec_push(dynvec *v, void *elem) {
    if (v->length == v->capacity) dynvec_resize(v, v->capacity * 2);
    memcpy((char *)v->data + (v->length * v->elem_size), elem, v->elem_size);
    v->length++;
}

size_t dynvec_length(dynvec *v) { return v->length; }

void* dynvec_get(dynvec *v, size_t index) {
    if (index >= v->length) return NULL;
    return (char *)v->data + (index * v->elem_size);
}

void dynvec_free(dynvec *v) {
    if (v) { free(v->data); free(v); }
}


bool dynvec_contains(dynvec *v, void *elem, int (*cmp)(const void *, const void *)) {
    for (size_t i = 0; i < v->length; i++) {
        if (cmp(dynvec_get(v, i), elem) == 0) return true;
    }
    return false;
}

size_t dynvec_index(dynvec *v, void *elem, int (*cmp)(const void *, const void *)) {
    for (size_t i = 0; i < v->length; i++) {
        if (cmp(dynvec_get(v, i), elem) == 0) return i;
    }
    errno = ENOENT;
    return v->length;
}

void dynvec_fold_left(dynvec *v, void *acc, void (*func)(void *acc, void *elem)) {
    for (size_t i = 0; i < v->length; i++) func(acc, dynvec_get(v, i));
}

bool dynvec_forall(dynvec *v, bool (*predicate)(void *)) {
    for (size_t i = 0; i < v->length; i++) {
        if (!predicate(dynvec_get(v, i))) return false;
    }
    return true;
}

bool dynvec_exists(dynvec *v, bool (*predicate)(void *)) {
    for (size_t i = 0; i < v->length; i++) {
        if (predicate(dynvec_get(v, i))) return true;
    }
    return false;
}

size_t dynvec_exists_index(dynvec *v, bool (*predicate)(void *)) {
    for (size_t i = 0; i < v->length; i++) {
        if (predicate(dynvec_get(v, i))) return i;
    }
    return (size_t)-1;
}

dynvec* dynvec_filter(dynvec *v, bool (*predicate)(void *)) {
    dynvec *novo = dynvec_create(v->elem_size);
    for (size_t i = 0; i < v->length; i++) {
        void *item = dynvec_get(v, i);
        if (predicate(item)) dynvec_push(novo, item);
    }
    return novo;
}
