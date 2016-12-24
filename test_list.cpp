#include <iostream>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cinttypes>
#include <cctype>


#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "lib/list.h"

using namespace std;

void int_free(void *ptr) {
    free(ptr);
}

void print_int(void *ptr) {
    int *a = (int*)ptr;
    cout << *a;
}


int main() {
    list_t L = new_list(&int_free, &print_int);
    int *a = (int*)xmalloc(sizeof(int));
    *a = 5;
    node_t N = new_node((void*)a);
    add(L, N);
    int *b = (int*)xmalloc(sizeof(int));
    *b = 10;
    node_t M = new_node((void*)b);
    add_bottom(L, M);
    remove_top(L);
    remove_top(L);
    M = new_node((void*)b);
    add(L, M);
    N = new_node((void*)a);
    add_bottom(L, N);
    cout << get_size(L) << endl;
    print_list(L);
    free_list(L);
    
    
    
    return 0;
}
