#include "board.h"
#include "winfo.h"
#include "circle.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static unsigned compute_integer(const char* integer)
{
    unsigned result = 0;

    for ( int i = 0; i < strlen(integer); i++ )
    {        
        if ( (unsigned)integer[i] < '0' || (unsigned)integer[i] > '9' )
            return 0;

        result = (result * 10) + (unsigned)(integer[i] - '0');
    }

    return result;
}

static int start_up(const char** argv)
{ 
    /*
    NOTE: 
    You could generalise this segment here and write a proceedure that assigns
    positions in an array (of some arbitrary storage specification, to be dec-
    ided) to the respective circle's properties.     
    */
    
    int   R = compute_integer(argv[1]);      // Radius.
    int   D = compute_integer(argv[2]);      // Denominator in precision; accuracy. 
    int   C = compute_integer(argv[3]);      // Colour.
    int phi = compute_integer(argv[4]);	     // Three space rotation.

    winfo_t* window_info; 
    board_t* board;
    
    if ( (window_info = winfo_create()) == NULL )
        return 1;

    if ( (board = board_create(2 * R, 2 * R, window_info)) == NULL ) 
    {
        free(window_info);

        return 1;
    }

    draw_circle(board, R, D, C, phi);

    free(window_info);

    free(board->data);

    free(board);

    return 0;
}
    
int main(const int argc, const char** argv)
{
    puts("\x1b[2J\x1B[H");

    if ( argc != 5 )
    {
        const char* size;
        
        (argc < 5) ? (size = "few") : (size = "many");
        
        fprintf(stderr, "Fuck you! Too %s arguments; format is ./circle <radius>, <accuracy>, <colour>, <3D rotation>\n", size);

        return 1;
    }

    return start_up(argv);
}

/* 
GENERAL TODO:

1. Cleanup startup:
    1.1. Write a better freeing interface; effectively write an interface for a pseudo-garbage collector, make MMM slightly more autonomous (SAMMM).
         1.1.1 Write a part of the interface which assigns 'components' (various objects) to the allocation (respective addresses). Essentially,
               write a mathematically accurate function (a mapping) between various objects to respective addresses.     
    1.2. Isolate allocations.
    1.3. Improve the circle's property mappings (Perhaps write a parser??).

2.  Improve compute integer ad-hoc helper function:
    2.1. Accomodate for integer sign (modular behaviour and overflow).
*/