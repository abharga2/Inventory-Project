//  Created by Abhishek Bhargava on 1/7/17.
//  Copyright © 2017 Abhishek Bhargava. All rights reserved.


# Inventory-Project
Keep track of inventory! Interactive user-specific inventory management system, stores sets of products in database based on user ID. Uses a hash table implementation with separate chaining for quick lookup, insertion, and deletion.

lib
    contains memory allocation wrapper (xalloc) and contract statements (contracts.h)
    doubly linked list implementation in list.h, list.cpp


    need hash tables, automatically resizing, keep load factor below 0.5
    then classes of products (use misc as one thingy: misc, electronics, etc.)
    then main class to get all info and store
    then figure out database stuff and gui stuff
        maybe associate with account?


To compile: g++ -Wc++11-extensions -std=c++0x lib/xalloc.cpp lib/list.cpp lib/hash_table.cpp product.cpp test_hash.cpp -lsqlite3

Dependencies: sqlite3
To install: brew install sqlite3


