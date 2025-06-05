#include "board.h"
#include "winfo.h"

#include <stdlib.h>
#include <string.h>

board_t* board_create(const int width, const int height, const winfo_t* const window_info)
{
    board_t* board;

    if ( (board = malloc(sizeof *board)) == NULL ) 
        return NULL;

    board->size = (height + 2) * (width + 1);

    // NOTE: If we couldn't allocate the board or the board size was too big.
    if ( (board->data = malloc(sizeof(char) * board->size)) == NULL || board->size > window_info->ccols * window_info->crows) 
        return NULL;

    memset(board->data, ' ', sizeof(char) * board->size);

    // NOTE: Adding one continously doesn't actually do much to the runtime (ignoring the occational arithmetic overflow).
    for ( int i = 0; i < height; i++ )
    {
        // NOTE: This is a formula to get the zero index position of the end of the rows, again, pulled out of my ass. 
        board->data[(width + 1) * i + ((width + 1) + i)] = '\n';
    }

    board->data[board->size - 1] = '\0';

    return board;
}

/*
NOTE: 

I think it's better practice to isolate the board's
allocation as much as possible for a respective pro-
cedural gain and loss of cohesion and coupling; we 
make the board create function's signature dependen-
t on winfo_t to achieve this. If the user/callee of 
the function decides to lie about the window info, 
providing their own erronious data, that's their fu-
ckin' problem. This is discoraged though use of the 
winfo_t type, acompanied by it's own interface (the 
worry here is that the user/callee could quite easi-
ly fuck off the interface, manually allocate their 
own winfo struct, and use nonsense values). And by 
user/callee I mean programmer, not the end user.
*/
