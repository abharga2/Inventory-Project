#include <iostream>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cstddef>

#include "lib/xalloc.h"
#include "lib/contracts.h"

using namespace std;

/*Generic Linked list*/
typedef void *elem;
typedef struct list_node node;
typedef struct list_header list;

struct list_node {
	elem data;
	node *left;
	node *right;
};

struct list_header {
	node *top;
	node *bottom;
};

list *new_list() {
	list *L = (list*)xmalloc(sizeof(list));
	node *N = (node*)xmalloc(sizeof(node));
	N->data = NULL;
	N->left = NULL;
	N->right = NULL;

	L->top = N;
	L->bottom = N;

	return L;
}

void list_add(list *L, node *N) {

	//Add to bottom of list
	/*L->bottom->right = N;
	L->bottom->right->left = L->bottom;
	L->bottom = L->bottom->right;*/

	//Add to top of list
	L->top->left = N;
	L->top->left->right = L->top;
	L->top = L->top->left;
}

void list_add(list *L, int a) {
	int *b = (int*)xmalloc(sizeof(int));
	*b = a;
	elem E = (elem)b;
	node *N = (node*)xmalloc(sizeof(node));
	N->data = E;
	N->right = NULL;
	N->left = NULL;
	list_add(L, N);
}

void print_list(list *L) {
	ASSERT(L != NULL);

	node *N = L->top;

	while (N->right != NULL) {
		int *d = (int*)(N->data);
		cout << *d << endl;
		N = N->right;
	}

}



int main() {

	list *L = new_list();
	print_list(L);


	/*int *a = (int*)xmalloc(sizeof(int));
	*a = 5;
	elem E = (elem)a;
	node *N = (node*)xmalloc(sizeof(node));
	N->data = E;
	N->right = NULL;
	N->left = NULL;*/

	list_add(L, 5);
	list_add(L, 3);
	list_add(L, 4);


	print_list(L);

	return 0;
}