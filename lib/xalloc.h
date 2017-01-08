/* Allocation utilities
 * Implement versions of malloc and free that abort
 * when allocation fails instead of returning NULL.
 *
 * 15-122 Principles of Imperative Computation, Fall 2010
 * Frank Pfenning
 */

/*This file was originally written in C by Frank Pfenning for 15-122 - the Carnegie Mellon University data structures course. I adapted it and rewrote in C++.*/

#include <cstdlib>
#include <cstddef>

#ifndef _C0LIB_H
#define _C0LIB_H

/* xcalloc(nobj, size) returns a non-NULL pointer to
 * array of nobj objects, each of size size and
 * exits if the allocation fails.  Like calloc, the
 * array is initialized with zeroes.
 */
void* xcalloc(size_t nobj, size_t size);
/* rename to xcalloc, xmalloc */

/* xmalloc(size) returns a non-NULL pointer to
 * an object of size size and exits if the allocation
 * fails.  Like malloc, no initialization is guaranteed.
 */
void* xmalloc(size_t size);

#endif
