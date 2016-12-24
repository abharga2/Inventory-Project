# Inventory-Project
Keeping track of inventory

lib
    contains memory allocation wrapper (xalloc) and contract statements (contracts.h)
    doubly linked list implementation in list.h, list.cpp


    need hash tables, automatically resizing, keep load factor below 0.5
    then classes of products (use misc as one thingy: misc, electronics, etc.)
    then main class to get all info and store
    then figure out database stuff and gui stuff
        maybe associate with account?


To compile: g++ -Wc++11-extensions -std=c++0x lib/xalloc.cpp lib/list.cpp lib/hash_table.cpp product.cpp test_hash.cpp


