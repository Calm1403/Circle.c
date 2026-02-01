#include "circle.h"
#include "board.h"

#include <math.h>
#include <stdio.h>

void
draw_circle(board_t* B, const int R, const int D, const int C, const int phi)
{
  double cos_phi = cos((phi * M_PI) / 180), rad_incr = (M_PI / D);

  for (double theta_r = 0; theta_r < (2 * M_PI + rad_incr); theta_r += rad_incr)
  {
    int y = R + (int)(round(R * sin(theta_r)));

    int x = R + (int)(round(R * cos(theta_r) * cos_phi));

    // Increment x if the x in question is at a NEWL position; intuitive if you
    // consider format of board_t.
    x = x + (x == R * 2 + 1);

    // NOTE: This is weird, elaborate logic that I pulled out of Narnia, because
    // I'm magic.

    // NOTE: B->data[(2 * R + 1) * y + (x + y)] = '@' is algebraically
    // equivelent to:

    B->data[(2 * y) * (R + 1) + x] = '@';
  }

  printf("| R: %i | D: %i | C: %i | PHI: %i |\n\x1b[38;5;%im%s\x1b[0m\n",
         R,
         D,
         C,
         phi,
         C,
         B->data);
}
