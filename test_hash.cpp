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
#include <string.h>

#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "lib/list.h"
#include "lib/hash_table.h"
#include "product.h"
#include "/usr/local/Cellar/sqlite/3.16.1/include/sqlite3.h"

using namespace std;


//Free function
void str_free(void *x) {
    Product<string>* P = (Product<string>*)x;
    delete P;
    cout << "Deleting" << endl;
}

//Print all relevant information for a product
void print_str(void *x) {
    Product<string>* P = (Product<string>*)x;
    string p_id = P->get_id();

    cout << P->get_name() << "\t" << P->get_id() << "\t" << P->get_num() << "\t" << P->get_price() << "\t" << P->get_category() << endl;
}

//Hash function (hashing on product ID)
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

//Determines if a product has a given ID
bool product_equiv(void *x, string id) {
    Product<string>* P = (Product<string>*)x;
    if (P->get_id() == id)
        return true;
    return false;
}

//Determines if 2 products are the same
bool elem_equiv(void *x, void *y) {
    Product<string>* P = (Product<string>*)x;
    Product<string>* Q = (Product<string>*)y;
    return P->get_id() == Q->get_id();
}


int main() {

    //Create database if it doesn't exist; connect otherwise
    sqlite3 *database;
    sqlite3_open("Products.db", &database);
    
    
    //Get user ID from user.
    string user_ID;
    cout << "Please enter User ID: ";
    getline(cin, user_ID);
    user_ID = "'" + user_ID + "'";
    
    
    //Create table in database for user if it does not already exist
    string sql = "CREATE TABLE IF NOT EXISTS ";
    sql = sql + user_ID;
    string values = "(Name TEXT, ID TEXT, Number INT, Price REAL, Category TEXT)";
    sql = sql+values;
    char *sql_comm = new char[sql.length() + 1];
    strcpy(sql_comm, sql.c_str());
    sqlite3_exec(database, sql_comm, 0, 0, NULL);
    
    
    //Create hash table (instance of Hash class)
    //The functions must be passed because Hash is a generic class, so I, as a client, need to provide information about how I want to implement products.
    Hash<string, Product<string>* > J(&str_free, &print_str, &hash_str, &product_equiv, &elem_equiv);
    
    
    //If there is already information in the database for this user, store it in the hash table
    sqlite3_stmt* t_statement;
    sql = "SELECT * FROM " + user_ID;
    delete[] sql_comm;
    sql_comm = new char[sql.length() + 1];
    strcpy(sql_comm, sql.c_str());
    size_t t_len = strlen(sql_comm);
    int rc = sqlite3_prepare_v2(database, sql_comm, t_len, &t_statement, NULL);
    rc = sqlite3_step(t_statement);
    
    size_t conv;
    string pr_name;
    string pr_id;
    size_t num_pr;
    double pr_price;
    string pr_category;
    
    cout << endl;
    while (rc == SQLITE_ROW) {
        pr_name = string(reinterpret_cast<const char*>(sqlite3_column_text(t_statement, 0)));
        pr_id = string(reinterpret_cast<const char*>(sqlite3_column_text(t_statement, 1)));
        num_pr = (size_t)(stoi(string(reinterpret_cast<const char*>(sqlite3_column_text(t_statement, 2))), &conv));
        pr_price = stod(string(reinterpret_cast<const char*>(sqlite3_column_text(t_statement, 3))), &conv);
        pr_category = string(reinterpret_cast<const char*>(sqlite3_column_text(t_statement, 4)));
        
        Product<string> *new_prod = new Product<string>(pr_name, pr_id, num_pr, pr_price, pr_category);
        J.insert(pr_id, new_prod);

        rc = sqlite3_step(t_statement);
    }
    
    
    
    //Interactive part of program. Allows user to add, remove, and lookup products in database
    string command;
    cout << "Please enter command (I for insert, L for lookup, D for delete, P to print all products, Q for quit: ";
    cin >> command;
    cin.ignore();
    while (command != "Q" && command != "q") {
        
        //Insert product into hash table and database
        if (command == "I" || command == "i") {
            
            string prod_name;
            string prod_id;
            string num;
            string price;
            string category;
            size_t convert;
            string name_db;
            string id_db;
            string category_db;
            
            cout << "Enter product name: ";
            getline(cin, prod_name);
            cout << "Enter product ID: ";
            getline(cin, prod_id);
            cout << "Enter number available: ";
            cin >> num;
            cin.ignore();
            cout << "Enter price: ";
            cin >> price;
            cin.ignore();
            cout << "Enter category: ";
            getline(cin, category);
            
            //If the product ID already exists
            if (J.lookup(prod_id) != NULL) {
                string rep;
                cout << "A product with this ID already exists. Would you like to replace it? (Y/N): ";
                cin >> rep;
                cin.ignore();
                
                if (rep == "Y" || rep == "y") {
                    
                    string del = "DELETE FROM " + user_ID + " WHERE ID = '" + prod_id + "'";
                    
                    delete[] sql_comm;
                    sql_comm = new char[del.length() + 1];
                    strcpy(sql_comm, del.c_str());
                    sqlite3_exec(database, sql_comm, 0, 0, NULL);
                    
                    J.delete_elem(prod_id);

                }
                else {
                    cout << "Command: ";
                    cin >> command;
                    cin.ignore();
                    continue;
                }
            }
            
            
            name_db = "'" + prod_name + "'";
            id_db = "'" + prod_id + "'";
            category_db = "'" + category + "'";
            
            
            //Insert into database
            string ins = "INSERT INTO ";
            ins = ins + user_ID + " " + "Values(" + name_db + ", " + id_db + ", " + num + ", " + price + ", " + category_db + ")";
            delete[] sql_comm;
            
            sql_comm = new char[ins.length() + 1];
            strcpy(sql_comm, ins.c_str());
            
            sqlite3_exec(database, sql_comm, 0, 0, NULL);
            
            
            //Insert into hash table
            Product<string> *prod = new Product<string>(prod_name, prod_id, (size_t)(stoi(num, &convert)), stod(price, &convert), category);

            J.insert(prod_id, prod);
            
        }
        
        //Lookup product by product ID:
        //Lookup is done via hash table rather than database (more efficient)
        else if (command == "L" || command == "l") {
            string prod_id;
            cout << "Enter product ID: ";
            getline(cin, prod_id);
            
            elem product = J.lookup(prod_id);
            if (product != NULL) {
                print_str(product);
            }
            else {
                cout << "This product doesn't exist!" << endl;
            }
        }
        
        //Delete product from hash table and database
        else if (command == "D" || command == "d") {
            string prod_id;
            cout << "Enter product ID: ";
            getline(cin, prod_id);
            
            elem product = J.delete_elem(prod_id);
            if (product != NULL) {
                string undo;
                cout << "You have deleted the following product: " << endl;
                print_str(product);
                cout << "Would you like to undo this? (Y/N): " << endl;
                cin >> undo;
                cin.ignore();
                if (undo == "Y" || undo == "y") {
                    J.insert(prod_id, (Product<string>*)product);
                    cout << "You have undeleted this product!" << endl;
                }
                else {
                    string del = "DELETE FROM " + user_ID + " WHERE ID = '" + prod_id + "'";
                    
                    delete[] sql_comm;
                    sql_comm = new char[del.length() + 1];
                    strcpy(sql_comm, del.c_str());
                    sqlite3_exec(database, sql_comm, 0, 0, NULL);
                }
            }
            else {
                cout << "There is no product with this ID! Nothing can be deleted." << endl;
            }
        }
        
        //Print all products in inventory
        else if (command == "P" || command == "p") {
            J.print_hash_table();
        }
        else {
            cout << "Invalid command." << endl;
        }
        
        cout << "Command: ";
        cin >> command;
        cin.ignore();
    }
    

    
    
    delete[] sql_comm;
    
    return 0;
    
}
