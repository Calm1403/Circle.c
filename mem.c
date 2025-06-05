#include "mem.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

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

2. I know that malloc is implemented us-
ing memory mapping functionality; it re-
fers to the program's virtual memory ad-
dress space, which means that memory is 
represented congruently. Consequently I 
should be able to use this to manage th-
e memory that I allocate.

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
