#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct Dynvec {
    
    void *data;
    size_t length;
    size_t capacity;
    size_t elem_size;
}dynvec;

typedef struct {
    
    int x;
    int y;
} Ponto;

typedef struct {
    
    Ponto p1;
    Ponto p2;
} Aresta;

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

void swap(void *a, void *b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);      
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

int partition(dynvec *v, int menor, int maior, int (*cmp)(const void *, const void *)) {

    char *base = (char *)v->data;
    size_t size = v->elem_size;

    void *pivot = base + maior * size;

    int indice = menor - 1;

    for (int j = menor; j < maior; j++) {

        void *elem_j = base + j * size;

        if (cmp(elem_j, pivot) < 0) {
            indice++;
            void *elem_i = base + indice * size;   // lado dos menores que o pivo
            swap(elem_i, elem_j, size);
        }
    }

    void *elem_i1 = base + (indice + 1) * size;
    swap(elem_i1, pivot, size);

    return indice + 1;
}

void quicksort_rec(dynvec *v, int menor, int maior, int (*cmp)(const void *, const void *)) {

    if (menor < maior) {

        int pi = partition(v, menor, maior, cmp);

        quicksort_rec(v, menor, pi - 1, cmp);
        quicksort_rec(v, pi + 1, maior, cmp);
    }
}

void quicksort_dynvec(dynvec *v, int (*cmp)(const void *, const void *)){

   if (v->length > 1) {
        quicksort_rec(v, 0, v->length - 1, cmp);
    } 
}

int cmp_lexicografico(const void *a, const void *b){

    const Ponto *pa = (const Ponto *)a;
    const Ponto *pb = (const Ponto *)b;
    
    if (pa->x != pb->x) {
        return pa->x - pb->x;
    }
    return pa->y - pb->y;
}

int calcula_det(Ponto A, Ponto B, Ponto P){

    return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
}

void processa_regiao(Ponto A, Ponto B, dynvec *candidatos, dynvec *arestas_finais){

     int    maior_det = 0;
    Ponto *melhor    = NULL;
 
    for (size_t i = 0; i < dynvec_length(candidatos); i++) {
        Ponto *P   = (Ponto *)dynvec_get(candidatos, i);
        int    det = calcula_det(A, B, *P);
        if (det > maior_det ||
            (det == maior_det && melhor != NULL &&
             cmp_lexicografico(P, melhor) < 0)) {
            maior_det = det;
            melhor    = P;
        }
    }

    if (melhor == NULL) {
        Aresta e = { A, B };
        dynvec_push(arestas_finais, &e);
        return;
    }
 
    Ponto C = *melhor;
 
    dynvec *candid_AC = dynvec_create(sizeof(Ponto));
    dynvec *candid_CB = dynvec_create(sizeof(Ponto));
 
    for (size_t i = 0; i < dynvec_length(candidatos); i++) {
        Ponto *P = (Ponto *)dynvec_get(candidatos, i);
        if (calcula_det(A, C, *P) > 0) dynvec_push(candid_AC, P);
        if (calcula_det(C, B, *P) > 0) dynvec_push(candid_CB, P);
    }

    processa_regiao(A, C, candid_AC, arestas_finais);
    processa_regiao(C, B, candid_CB, arestas_finais);
 
    dynvec_free(candid_AC);
    dynvec_free(candid_CB);
}

int main(){

    dynvec *v = dynvec_create(sizeof(Ponto));

    Ponto p;
    while (scanf("%d %d", &p.x, &p.y) == 2){
        dynvec_push(v, &p);
    }

    quicksort_dynvec(v, cmp_lexicografico);

    for (size_t i = 0; i < dynvec_length(v); i++) {
        Ponto *pt = (Ponto *)dynvec_get(v, i);
        printf("%d %d\n", pt->x, pt->y);
    }

    size_t n = dynvec_length(v);
    Ponto  A = *(Ponto *)dynvec_get(v, 0);
    Ponto  B = *(Ponto *)dynvec_get(v, n - 1);
 
    dynvec *arestas_finais  = dynvec_create(sizeof(Aresta));
    dynvec *candidatos_cima = dynvec_create(sizeof(Ponto));
    dynvec *candidatos_baixo= dynvec_create(sizeof(Ponto));

    for (size_t i = 0; i < n; i++) {
        Ponto *P = (Ponto *)dynvec_get(v, i);
        int detAB = calcula_det(A, B, *P);
        int detBA = calcula_det(B, A, *P);
        if (detAB > 0) dynvec_push(candidatos_cima,  P);
        if (detBA > 0) dynvec_push(candidatos_baixo, P);
    }

    processa_regiao(A, B, candidatos_cima,  arestas_finais);
    processa_regiao(B, A, candidatos_baixo, arestas_finais);
 
    size_t E = dynvec_length(arestas_finais);
    printf("%zu\n", E);
 
    double perimetro = 0.0;
    for (size_t i = 0; i < E; i++) {
        Aresta *e = (Aresta *)dynvec_get(arestas_finais, i);
        printf("%d %d %d %d\n", e->p1.x, e->p1.y, e->p2.x, e->p2.y);
        double dx = e->p2.x - e->p1.x;
        double dy = e->p2.y - e->p1.y;
        perimetro += sqrt(dx * dx + dy * dy);
    }

    printf("%.2f\n", perimetro);
 
    dynvec_free(candidatos_cima);
    dynvec_free(candidatos_baixo);
    dynvec_free(arestas_finais);
    dynvec_free(v);
    return 0;
}
