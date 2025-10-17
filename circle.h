#ifndef CIRCLE_H
#define CIRCLE_H

#ifdef _WIN32
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#endif

typedef struct board_s board_t;

void
draw_circle(board_t* B, const int R, const int D, const int C, const int phi);

#endif
