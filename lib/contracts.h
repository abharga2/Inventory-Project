/* Debugging with contracts; simulating cc0 -d
 * Enable with gcc -DDEBUG ...
 *
 * 15-122 Principles of Imperative Computation
 * Frank Pfenning
 */

/* Unlike typical header files, "contracts.h" may be
 * included multiple times, with and without DEBUG defined.
 */

/*This file was originally written in C by Frank Pfenning for 15-122 - the Carnegie Mellon University data structures course. I adapted it and rewrote in C++.*/

#include <cassert>

#ifdef DEBUG

#define ASSERT(COND) assert(COND)
#define REQUIRES(COND) assert(COND)
#define ENSURES(COND) assert(COND)

#else

#define ASSERT(COND) ((void)0)
#define REQUIRES(COND) ((void)0)
#define ENSURES(COND) ((void)0)

#endif
