#ifndef DYNVEC_H
#define DYNVEC_H

#include <stddef.h>
#include <stdbool.h>

// Definição opaca do tipo
typedef struct Dynvec dynvec;

// Funções principais
dynvec* dynvec_create(size_t elem_size);
void dynvec_free(dynvec *v);
void dynvec_push(dynvec *v, void *elem);
size_t dynvec_length(dynvec *v);
void* dynvec_get(dynvec *v, size_t index);

// Funções do Exercício 5 (Busca, Iteradores e Filtros)
bool dynvec_contains(dynvec *v, void *elem, int (*cmp)(const void *, const void *));
size_t dynvec_index(dynvec *v, void *elem, int (*cmp)(const void *, const void *));
void dynvec_fold_left(dynvec *v, void *acc, void (*func)(void *acc, void *elem));
bool dynvec_forall(dynvec *v, bool (*predicate)(void *));
bool dynvec_exists(dynvec *v, bool (*predicate)(void *));
size_t dynvec_exists_index(dynvec *v, bool (*predicate)(void *));
dynvec* dynvec_filter(dynvec *v, bool (*predicate)(void *));

#endif