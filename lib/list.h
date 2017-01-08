//  Created by Abhishek Bhargava on 1/7/17.
//  Copyright © 2017 Abhishek Bhargava. All rights reserved.

#include <iostream>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdint>

/*Doubly linked list interface*/


#ifndef _LIST_H
#define _LIST_H

/******************/
/*Client Interface*/
/******************/

using namespace std;

typedef void *elem;
typedef void list_elem_free_fn(elem x);
typedef void print_elem_fn(elem x);
typedef bool elem_equiv_fn(elem x, elem y);

//To search for product using product id, generic function typedef
template <class product_id>
using product_id_equiv_fn = bool(elem x, product_id P);

/*******************/
/*Library Interface*/
/*******************/

typedef struct list_node *node_t;
typedef struct list_header *list_t;

//Add to top of linked list
void add_top(list_t L, node_t N);

//Add to bottom (end) of linked list
void add_bottom(list_t L, node_t N);

//Default: add to top of list
void add(list_t L, node_t N);

//Default: remove from top of list
elem remove(list_t L);

//Remove from top of list
elem remove_top(list_t L);

//Remove from bottom of list
elem remove_bottom(list_t L);

//Get new, empty list
list_t new_list(list_elem_free_fn *F, print_elem_fn *P, elem_equiv_fn *E);

//Get new list whose first node contains elem E
list_t new_list(elem E, list_elem_free_fn *F, print_elem_fn *P, elem_equiv_fn *G);

//Get new list whose first node is N
list_t new_list(node_t N, list_elem_free_fn *F, print_elem_fn *P, elem_equiv_fn *E);

//Get new node whose data field is E
node_t new_node(elem E);


/*Additional functions*/

//True if the list is empty, false otherwise
bool is_empty(list_t L);

//Print elements of list from top to bottom
void print_list(list_t L);

//Free list
void free_list(list_t L);

//Set free function
void set_free_fn(list_t L, list_elem_free_fn *F);

//Returns number of nodes in list
size_t get_size(list_t L);

//Lookup to see if elem is in list
bool is_in_list(list_t L, elem x);

//Lookup with product id
template <typename product_id>
elem is_id_in_list(list_t L, product_id P, product_id_equiv_fn<product_id> *func);

//Remove element from list
elem remove_elem(list_t L, elem x);


#endif
