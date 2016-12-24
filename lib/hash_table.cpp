#include <iostream>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cinttypes>
#include <cctype>
#include <vector>

#include "xalloc.h"
#include "contracts.h"
#include "list.h"
#include "hash_table.h"
#include "../product.h"

using namespace std;

//template class Hash<int, int>;
/*template Hash<int, int>::Hash();
template Hash<int, int>::~Hash();
template Hash<struct A, int>::Hash();
template Hash<struct A, int>::~Hash();*/

template <typename product_id, typename product>
Hash<product_id, product>::Hash() {
    size = 100;
    num_elems = 0;
    v.assign(100, nullptr);
    free_elem = NULL;
    print_elem = NULL;
    hash_id = NULL;
    id_equiv = NULL;
    elem_equiv = NULL;
    cout << "Constructor Called" << endl;
}

template <typename product_id, typename product>
Hash<product_id, product>::Hash(list_elem_free_fn *F, print_elem_fn *P, hash_fn<product_id> *H, product_id_equiv_fn<product_id> *ID, elem_equiv_fn *EQ) {
    size = 100;
    num_elems = 0;
    v.assign(100, nullptr);
    free_elem = F;
    print_elem = P;
    hash_id = H;
    id_equiv = ID;
    elem_equiv = EQ;
    cout << "Constructor Called" << endl;

}

template <typename product_id, typename product>
Hash<product_id, product>::Hash(size_t capacity, list_elem_free_fn *F, print_elem_fn *P, hash_fn<product_id> *H, product_id_equiv_fn<product_id> *ID, elem_equiv_fn *EQ) {
    size = capacity;
    num_elems = 0;
    v.assign(size, nullptr);
    free_elem = F;
    print_elem = P;
    hash_id = H;
    id_equiv = ID;
    elem_equiv = EQ;
    cout << "Constructor Called" << endl;
}

template <typename product_id, typename product>
Hash<product_id, product>::~Hash() {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == NULL) {
            continue;
        }
        list_t L = v[i];
        set_free_fn(L, free_elem);
        free_list(L);
    }
    cout << "Destructor Called" << endl;
}

template <typename product_id, typename product>
size_t Hash<product_id, product>::get_size() {
    return size;
}

template <typename product_id, typename product>
size_t Hash<product_id, product>::get_num_elems() {
    return num_elems;
}

template <typename product_id, typename product>
int Hash<product_id, product>::hash(product_id P) {
    int h = (*hash_id)(P);
    return abs(h) % size;
}


template <typename product_id, typename product>
elem Hash<product_id, product>::lookup(product_id P) {
    
    size_t index = (size_t)(hash(P));
    assert(index < size);
    
    if (v[index] == NULL) return NULL;
    list_t L = v[index];
    //elem dat = is_id_in_list<product_id>(L, P, id_equiv);
    //return dat;
    return is_id_in_list(L, P, id_equiv);
    //return NULL;
    
}

template <typename product_id, typename product>
elem Hash<product_id, product>::delete_elem(product_id P) {
    
    size_t index = (size_t)(hash(P));
    assert(index < size);
    
    if (v[index] == NULL) return NULL;
    list_t L = v[index];

    elem rem = is_id_in_list(L, P, id_equiv);
    if (rem == NULL) {
        cout << "This element doesn't exist. Can't delete." << endl;
        return NULL;
    }
    
    return remove_elem(L, rem);
}

template <typename product_id, typename product>
void Hash<product_id, product>::insert(product_id P, product x) {
    elem E = (elem)x;
    size_t index = (size_t)(hash(P));
    assert(index < size);
    if (v[index] == NULL) {
        v[index] = new_list(E, free_elem, print_elem, elem_equiv);
    }
    else {
        node_t N = new_node(E);
        add_bottom(v[index], N);
    }
    
}

template <typename product_id, typename product>
void Hash<product_id, product>::print_hash_table() {
    for (size_t i = 0; i < size; i++) {
        if (v[i] == NULL) continue;
        assert(v[i] != NULL);
        print_list(v[i]);
    }
}



/*template class Hash<int, int>;
template class Hash<struct A, int>;
template class Hash<struct B, int>;
template class Hash<struct product*, int>;
template class Hash<string, struct product*>;
template class Hash<int, struct product*>;
template class Hash<string, Product<string> >;
template class Hash<int, Product<int> >;
template class Hash<long, Product<long> >;
template class Hash<int64_t, Product<int64_t> >;*/

template class Hash<string, Product<string>* >;
template class Hash<int, Product<int>* >;
template class Hash<long, Product<long>* >;
template class Hash<int64_t, Product<int64_t>* >;


/*template <typename product_id, typename product>
product Hash<product_id, product>::lookup(product_id P) {
    int index = (*hash_id)(P) % ((int)(size));
    
    ASSERT(index >= 0);
    ASSERT(index < (int)(size));
    
    if (v[index] == NULL)
        return NULL;
    
}*/


