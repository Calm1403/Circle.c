#include "mem.h"

/*
NOTE / DOCUMENTATION:

Errors affecting return type:

Null on allocation (behaviour == 1) imp-
lies that the function failed due to a 
few reasons:

1. An allocation was already made prior 
to current allocation attempt.

2. The obj manager couldn't perform the
nessesary means to ensure memory is de-
allocated on program termination.

3. There's not enough memory to perform
the required allocation; calloc fails.  

The return type on deallocation (behavi-
our == 0) doesn't matter; it doesn't re-
turn anything deterministically, and nu-
ll can either mean that the function fa-
iled because no deallocation attempt wa-
s made prior to call or the function su-
ceeded without error.

Formal parameter and return value usage:

On allocation (behaviour == 0), the for-
mal parameter objs, and the return valu-
e of the function, may be used to assig-
n dynamic memory to a pointer. This was
intended for differing code styles.

On deallocation (behaviour == 1), the f-
ormal parameters don't impact the deall-
ocation. However, Objs may be used to a-
ssign the previous memory pointer to nu-
ll if required.

Function behaviour:

The function behaviour determines the f-
unction's functionality; the first para-
meter is an interface for this.

For behaviour == 1, an allocation is in-
effect. The interface is much like that 
of calloc, but accomodates for various 
coding styles with function arguments (
see formal parameter and return value u-
sage). 

For behaviour == 0, a deallocation is i-
n effect; the interface is much like fr-
ee (again, see formal parameter and ret-
urn value usage).

The behaviour isn't binary; there may be 
other behaviours in the future (realloc 
behaviour, for e.g.).

The nessesity for it:

I thought it would be an interesting id-
ea to write a private memory interface.
It enforces a less strict memory manage-
ment option, and encourages large alloc-
ations as opposed to smaller ones.

There are a few downsides to using this: 

1. There is wasted memory; the peramete-
rs. However, this is function local mem-
ory so it doesn't matter too much.

2. Larger allocations don't guarantee a
better runtime; this may be down to the
callee of the interface.
*/

static void deallocate(void);

void* obj_manager(const int behaviour, const size_t number, const size_t size, void** objs)
{
    static void* allocation;
    
    // Calloc; allocation behaviour.
    if ( behaviour == 1 )
    {
        // NOTE: The precedence of these operations should be noted; do some testing.
        if ( allocation != 0 || atexit(deallocate) != 0 || (allocation = calloc(number, size)) == NULL )
            return NULL;

        if ( objs != NULL ) *objs = allocation;
    
        return allocation;
    }

    // Free; deallocation behaviour.
    if ( allocation == 0 )
        return NULL;

    free(allocation);

    allocation = 0; if ( objs != NULL ) *objs = NULL;

    return NULL;
}

static void deallocate(void)
{
    obj_manager(0, 0, 0, NULL);
}