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


//Automatically resizing hash table interface (header file)
//Abstract class


#ifndef _HASH_H
#define _HASH_H

using namespace std;

template <class product_id>
using hash_fn = int(product_id P);
//typedef int hash_fn(product_id P);

//Product id is what is used for lookup
//Product is the actual element stored in linked lists - pointer to instance of Product class
template <class product_id, class product>
class Hash {
    
    private:
        size_t size; //Size of hash table (v)
        size_t num_elems; //Number elements in hash table
        vector<list_t> v;
        list_elem_free_fn *free_elem;
        print_elem_fn *print_elem;
        //void resize(); //Resize when load factor gets above 0.5
        hash_fn<product_id> *hash_id;
        product_id_equiv_fn<product_id> *id_equiv;
        elem_equiv_fn *elem_equiv;
        int hash(product_id P);
    
    public:
    
        size_t get_size(); //size of hash table (v)
        size_t get_num_elems(); //number of elements in hash table
        elem lookup(product_id P); //lookup
        elem delete_elem(product_id P); //delete product
        void insert(product_id P, product x); //add product
        void print_hash_table();
        //void set_capacity(size_t capacity); //set size of vector, don't want
    
    
        Hash(); //Constructor
        Hash(list_elem_free_fn *F, print_elem_fn *P, hash_fn<product_id> *H, product_id_equiv_fn<product_id> *ID, elem_equiv_fn *EQ); //Constructor
        Hash(size_t capacity, list_elem_free_fn *F, print_elem_fn *P, hash_fn<product_id> *H, product_id_equiv_fn<product_id> *ID, elem_equiv_fn *EQ); //Constructor

        ~Hash(); //Destructor
    
};








#endif
