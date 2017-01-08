//  Created by Abhishek Bhargava on 1/7/17.
//  Copyright © 2017 Abhishek Bhargava. All rights reserved.

#include <iostream>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cinttypes>
#include <cctype>
#include <vector>

#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "lib/list.h"
#include "lib/hash_table.h"

//Product interface

#ifndef _PRODUCT_H
#define _PRODUCT_H

using namespace std;


template <class p_id>
class Product {
    
    private:
        string product_name;
        p_id product_id;
        size_t num_product;
        double product_price;
        string product_category;
    
    public:
        string get_name();
        p_id get_id();
        size_t get_num();
        double get_price();
        string get_category();
        void add_prod(); //Add 1 to quantity
    
        Product(p_id prod_id);
        Product(string name, p_id prod_id, size_t num, double price, string category);
        ~Product();
};






#endif
