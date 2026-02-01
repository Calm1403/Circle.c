#include "board.h"
#include "circle.h"
#include "winfo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned
compute_integer(const char* integer)
{
  unsigned result = 0;

  for (int i = 0; i < strlen(integer); i++)
  {
    if ((unsigned)integer[i] < '0' || (unsigned)integer[i] > '9')
      return 0;

    result = (result * 10) + (unsigned)(integer[i] - '0');
  }

  return result;
}

static int
start_up(const char** argv)
{
  int R = compute_integer(argv[1]);   // Radius.
  int D = compute_integer(argv[2]);   // Denominator in precision; accuracy.
  int C = compute_integer(argv[3]);   // Colour.
  int phi = compute_integer(argv[4]); // Three space rotation.

  winfo_t* window_info;
  board_t* board;

  if ((window_info = winfo_create()) == NULL)
    return 1;

  if ((board = board_create(2 * R, 2 * R, window_info)) == NULL)
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

int
main(const int argc, const char** argv)
{
  puts("\x1b[2J\x1B[H");

  if (argc != 5)
  {
    const char* size;

    (argc < 5) ? (size = "few") : (size = "many");

    fprintf(stderr,
            "Too %s arguments; format is ./circle <radius>, "
            "<accuracy>, <colour>, <3D rotation>\n",
            size);

    return 1;
  }

  return start_up(argv);
}
