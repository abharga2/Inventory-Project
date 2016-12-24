#include <iostream>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cinttypes>
#include <cctype>


#include "xalloc.h"
#include "contracts.h"
#include "list.h"

using namespace std;

typedef struct list_node node;
typedef struct list_header list;

//Need typedef to free elems
//Need to complete remove functions


//enum type_elem { INT32, INT64, PTR, STR, UNKNOWN };

struct list_node {
    elem data;
    node *next;
    node *prev;
    //enum type_elem node_type;
};

struct list_header {
    node *top;
    node *bottom;
    size_t size;
    list_elem_free_fn *free_elem;
    print_elem_fn *print_elem;
    elem_equiv_fn *elem_equiv;
    //enum type_elem type;
};


void add(list *L, node *N) {
    add_top(L, N);
}

void add_top(list *L, node *N) {
    REQUIRES(L != NULL);
    REQUIRES(N != NULL);
    REQUIRES(L->top != NULL);
    
    if (L->size == 0) {
        L->top = N;
        L->bottom = N;
        L->size += 1;
        return;
    }
    
    N->next = L->top;
    L->top->prev = N;
    L->top = N;
    
    L->size += 1;
    
}

/*void add_elem_bottom(list *L, elem e) {
    node *N = new_node(e);
    add_bottom(L, N);
}*/

void add_bottom(list *L, node *N) {
    REQUIRES(L != NULL);
    REQUIRES(N != NULL);
    REQUIRES(L->bottom != NULL);
    
    if (L->size == 0) {
        L->top = N;
        L->bottom = N;
        L->size += 1;
        return;
    }
    
    N->prev = L->bottom;
    L->bottom->next = N;
    L->bottom = N;
    
    L->size += 1;
    
}

elem remove_top(list *L) {
    REQUIRES(L->size >= 1);
    REQUIRES(L != NULL);
    
    elem E;
    if (L->size == 1) {
        E = L->top->data;
        node *N = L->top;
        
        L->top = NULL;
        L->bottom = NULL;
        
        free(N);
        
        L->size -= 1;
        return E;
    }
    
    ASSERT(L->size > 1);
    
    E = L->top->data;
    node *N = L->top;
    L->top = L->top->next;
    
    ASSERT(L->top != NULL);
    
    L->top->prev = NULL;
    L->size -= 1;
    
    free(N);
    return E;
}

elem remove_bottom(list *L) {
    REQUIRES(L->size >= 1);
    REQUIRES(L != NULL);
    
    elem E;
    if (L->size == 1) {
        E = L->bottom->data;
        node *N = L->bottom;
        
        L->top = NULL;
        L->bottom = NULL;
        
        free(N);
        
        L->size -= 1;
        return E;
    }
    
    ASSERT(L->size > 1);
    
    E = L->bottom->data;
    node *N = L->bottom;
    L->bottom = L->bottom->prev;
    ASSERT(L->bottom != NULL);
    L->bottom->next = NULL;
    L->size -= 1;
    free(N);
    
    return E;
}


elem remove(list *L) {
    return remove_top(L);
}






/*Creating new lists*/

//Use with caution; generally don't want N->data to be NULL
list_t new_list(list_elem_free_fn *F, print_elem_fn *P,elem_equiv_fn *E) {
    list *L = (list*)xmalloc(sizeof(list));
    /*node *N = (node*)xmalloc(sizeof(node));
    
    N->data = NULL;
    N->next = NULL;
    N->prev = NULL;*/
    //N->node_type = UNKNOWN;
    
    L->top = NULL;
    L->bottom = NULL;
    L->size = 0;
    L->free_elem = F;
    L->print_elem = P;
    L->elem_equiv = E;
    //L->type = UNKNOWN;
    
    return L;
}

list_t new_list(elem E, list_elem_free_fn *F, print_elem_fn *P, elem_equiv_fn *G) {
    list *L = (list*)xmalloc(sizeof(list));
    node *N = (node*)xmalloc(sizeof(node));
    
    N->data = E;
    N->next = NULL;
    N->prev = NULL;
    //N->node_type = PTR;
    
    L->top = N;
    L->bottom = N;
    L->size = 1;
    L->free_elem = F;
    L->print_elem = P;
    L->elem_equiv = G;

    //L->type = PTR;
    
    return L;


}

list_t new_list(node *N, list_elem_free_fn *F, print_elem_fn *P, elem_equiv_fn *E) {
    list *L = (list*)xmalloc(sizeof(list));
    
    L->top = N;
    L->bottom = N;
    L->size = 1;
    L->free_elem = F;
    L->print_elem = P;
    L->elem_equiv = E;

    //L->type = N->node_type;
    
    return L;

}

/*list_t new_list(uint32_t i) {
    list *L = (list*)xmalloc(sizeof(list));
    node *N = (node*)xmalloc(sizeof(node));
    
    uint32_t *int_ptr = xmalloc(sizeof(uint32_t));
    *int_ptr = i;
    
    N->data = (elem)(int_ptr);
    N->next = NULL;
    N->prev = NULL;
    N->node_type = INT32;
    
    L->top = N;
    L->bottom = N;
    L->size = 1;
    L->type = INT32;
    
    return L;
    
}

list_t new_list(uint64_t i) {
    list *L = (list*)xmalloc(sizeof(list));
    node *N = (node*)xmalloc(sizeof(node));
    
    uint64_t *int_ptr = xmalloc(sizeof(uint64_t));
    *int_ptr = i;
    
    N->data = (elem)(int_ptr);
    N->next = NULL;
    N->prev = NULL;
    N->node_type = INT64;
    
    L->top = N;
    L->bottom = N;
    L->size = 1;
    L->type = INT64;
    
    return L;

}

list_t new_list(string s) {
    list *L = (list*)xmalloc(sizeof(list));
    node *N = (node*)xmalloc(sizeof(node));
    
    string *str_ptr = xmalloc(sizeof(string));
    *str_ptr = s;
    
    N->data = (void*)(str_ptr);
    N->next = NULL;
    N->prev = NULL;
    N->node_type = STR;
    
    L->top = N;
    L->bottom = N;
    L->size = 1;
    L->type = STR;
    
    return L;

    
}*/



/*Creating new node*/

node_t new_node(elem E) {
    
    node *N = (node*)xmalloc(sizeof(node));
    
    N->data = E;
    N->next = NULL;
    N->prev = NULL;
    //N->node_type = PTR;
    
    return N;
}


/*node_t new_node(uint32_t i) {

    node *N = (node*)xmalloc(sizeof(node));
    
    uint32_t *int_ptr = xmalloc(sizeof(uint32_t));
    *int_ptr = i;
    
    N->data = (elem)(int_ptr);
    N->next = NULL;
    N->prev = NULL;
    N->node_type = INT32;
    
    return N;
    
}

node_t new_node(uint64_t i) {
    
    node *N = (node*)xmalloc(sizeof(node));
    
    uint64_t *int_ptr = xmalloc(sizeof(uint64_t));
    *int_ptr = i;
    
    N->data = (elem)(int_ptr);
    N->next = NULL;
    N->prev = NULL;
    N->node_type = INT64;
    
    return N;
    
}

node_t new_node(string s) {
    
    node *N = (node*)xmalloc(sizeof(node));
    
    string *str_ptr = xmalloc(sizeof(string));
    *str_ptr = s;
    
    N->data = (void*)(str_ptr);
    N->next = NULL;
    N->prev = NULL;
    N->node_type = STR;
    
    return N;
    
}*/





bool is_empty(list *L) {
    return L->size == 0;
}

void free_list(list *L) {
    REQUIRES(L->free_elem != NULL);
    
    node *N = L->top;
    
    while (N != NULL) {
        node *pre = N;
        N = N->next;
        (*(L->free_elem))(pre->data);
        free(pre);
    }
    free(L);
    
}

void print_list(list *L) {
    if (L->print_elem == NULL)
        return;
    
    node *N = L->top;
    while (N != NULL) {
        (*(L->print_elem))(N->data);
        cout << endl;
        N = N->next;
    }
    
    
}

size_t get_size(list *L) {
    return L->size;
}

void set_free_fn(list *L, list_elem_free_fn *F) {
    L->free_elem = F;
}


bool is_in_list(list *L, elem x) {
    REQUIRES(x != NULL);
    
    if (L == NULL) return false;
        
    node *N = L->top;
    while(N != NULL) {
        if((*(L->elem_equiv))(x, N->data))
            return true;
        N = N->next;
    }
    
    return false;
        
}


elem remove_elem(list *L, elem x) {
    if (L == NULL) return NULL;
    if (x == NULL) return NULL;
    
    node *N = L->top;
    //node *back = L->top;
    
    while (N != NULL) {
        if((*(L->elem_equiv))(x, N->data) && N == L->top) {
            elem d = remove_top(L);
            //(*free_elem)(d);
            return d;
        }
        if((*(L->elem_equiv))(x, N->data) && N != L->top) {
            N->prev->next = N->next;
            N->next->prev = N->prev;
            //(*free_elem)(N->data);
            free(N);
            return x;
        }
        N = N->next;
    }
    return NULL;
}

template <typename product_id>
elem is_id_in_list(list *L, product_id P, product_id_equiv_fn<product_id> *func) {
    if (L == NULL) return NULL;
    
    node *N = L->top;
    while(N != NULL) {
        if((*func)(N->data, P)) return N->data;
        N = N->next;
    }
    return NULL;
}

template elem is_id_in_list<string>(list *L, string P, product_id_equiv_fn<string> *func);
template elem is_id_in_list<int>(list *L, int P, product_id_equiv_fn<int> *func);
template elem is_id_in_list<long>(list *L, long P, product_id_equiv_fn<long> *func);
template elem is_id_in_list<int64_t>(list *L, int64_t P, product_id_equiv_fn<int64_t> *func);






//template elem is_id_in_list<string>;




//template elem is_id_in_list<string>;

/*template <typename product_id>
elem lookup(list_t L, product_id P) {
    if (L == NULL) return NULL;
    
    while (
    
}*/
