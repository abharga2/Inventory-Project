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

using namespace std;
/*typedef struct product *prod;

struct product {
    string product_id;
    int num;
};*/


/*int hash_string(string a) {
    
}*/

//Note that elem is just a void* which is Product<string>* in this case
void str_free(void *x) {
    Product<string>* P = (Product<string>*)x;
    delete P;
    cout << "Deleting" << endl;
}

void print_str(void *x) {
    Product<string>* P = (Product<string>*)x;
    string p_id = P->get_id();
    //cout << p_id << endl;
    cout << P->get_name() << "\t" << P->get_id() << "\t" << P->get_num() << "\t" << P->get_price() << "\t" << P->get_category() << endl;
}

int hash_str(string id) {
    int hash_val = 1;
    size_t len = id.length();
    for (size_t i = 0; i < len; i++) {
        char a = id.at(i);
        int b = (int)a;
        hash_val = hash_val * b + 166462;
    }
    return hash_val % 122949823;
}

bool product_equiv(void *x, string id) {
    Product<string>* P = (Product<string>*)x;
    if (P->get_id() == id)
        return true;
    return false;
}

bool elem_equiv(void *x, void *y) {
    Product<string>* P = (Product<string>*)x;
    Product<string>* Q = (Product<string>*)y;
    return P->get_id() == Q->get_id();
}

int main() {
    //Hash<int, int> H;
    //prod = new(struct product);
    //prod P = new(struct product);
    //Hash<string, struct product*> H;
    //Hash<int, struct product*> G;
    
    //Note the product ids must be the same
    Hash<string, Product<string>* > H(&str_free, &print_str, &hash_str, &product_equiv, &elem_equiv);

    //Product<string> *P = new Product<string>("Product 1");
    
    Product<string> *P1 = new Product<string>("Teddy Bear", "A01123945", 5, 12.99, "Toddler Toys");
    Product<string> *P2 = new Product<string>("Row Boat", "B66223451", 23, 3.59, "Marine Toys");
    
    H.insert("A01123945", P1);
    H.insert("B66223451", P2);
    //elem x = H.lookup("A01123945");
    //print_str(x);
    //elem y = H.delete_elem("A01123945");
    //print_str(y);
    //H = new Hash<int, int>();
    H.print_hash_table();
    //str_free(x);
    //delete P;
    
    return 0;
    
}
