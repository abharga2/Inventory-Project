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
#include "product.h"

template <typename p_id>
Product<p_id>::Product(p_id prod_id) {
    product_name = "";
    product_id = prod_id;
    num_product = 0;
    product_price = 0;
    product_category = "";
}

template <typename p_id>
Product<p_id>::Product(string name, p_id prod_id, size_t num, double price, string category) {
    
    product_name = name;
    product_id = prod_id;
    num_product = num;
    product_price = price;
    product_category = category;
}

template <typename p_id>
Product<p_id>::~Product() {
    
}

template <typename p_id>
string Product<p_id>::get_name() {
    return product_name;
}

template <typename p_id>
p_id Product<p_id>::get_id() {
    return product_id;
}

template <typename p_id>
size_t Product<p_id>::get_num() {
    return num_product;
}

template <typename p_id>
double Product<p_id>::get_price() {
    return product_price;
}

template <typename p_id>
string Product<p_id>::get_category() {
    return product_category;
}

template <typename p_id>
void Product<p_id>::add_prod() {
    num_product += 1;
}


template class Product<string>;
template class Product<int>;
template class Product<long>;
template class Product<int64_t>;




