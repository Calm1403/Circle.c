#include "mem.h"

void* obj_manager(const int behaviour, const size_t number, const size_t size, void** objs)
{
    static void* allocation;
    
    if ( behaviour == 1 )
    {
        if ( allocation != 0 || (allocation = calloc(number, size)) == NULL )
            goto fail;

        return ( *objs = allocation );
    }

    if ( allocation == 0 )
        goto fail;

    free(allocation);

    allocation = 0; if ( objs != NULL ) *objs = NULL;

    return *objs;
fail:
    errno = ENOMEM;
    
    return NULL;
}

/*
NOTE:

1. The behaviour isn't binary; there may
be other behaviours in the future (reall-
oc behaviour, for e.g.). Hence why I don-
t use the bool type.

2. I know that malloc (and calloc too I-
'd imagine) is implemented using memory 
mapping functionality; it refers to the
program's virtual memory address space, 
which means that memory is represented 
congruently. Consequently I should be a-
ble to use this to manage the memory th
at I allocate quite nicely.

3. The reason why I use ENOMEM for a de-
allocation (when the specification stat-
es that it's used to indicate an inabil-
ity to allocate memory) is because I su-
ppose there's NOMEM to deallocate. This
may be poor practice.

4. Calloc is safer, because it performs 
overflow checking and initialisation; i-
t's slightly slower, but that's fine be-
cause you're not going to be calling th-
is rapidly.
*/
