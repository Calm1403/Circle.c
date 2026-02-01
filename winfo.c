#include "winfo.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <sys/ioctl.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

static int
winfo_get_terminal_dimensions(winfo_t* window_info)
{
#ifdef __linux__
  struct winsize ws;
  if ((ioctl(0, TIOCGWINSZ, &ws)) != 0)
  {
    fprintf(stderr, "Couldn't determine terminal size!\n");

    return 1;
  }
  window_info->ccols = (int)(ws.ws_col * 0.5);
  window_info->crows = (int)(ws.ws_row * 0.5);
#endif

#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if ((GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) == 0)
  {
    fprintf(stderr, "Couldn't determine terminal size!\n");

    return 1;
  }
  window_info->ccols =
    (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1) * 0.5;
  window_info->crows =
    (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1) * 0.5;
#endif

  return 0;
}

// NOTE: 'Creation' implies both allocation and initialisation.
winfo_t*
winfo_create(void)
{
  winfo_t* window_info;

  if ((window_info = malloc(sizeof *window_info)) == NULL)
    return NULL;

  // You could give a damn about zeroing the padding of a structure.
  *window_info = (winfo_t){ .ccols = 0, .crows = 0 };

  if (winfo_get_terminal_dimensions(window_info) == 1)
  {
    free(window_info);

    return NULL;
  }

  return window_info;
}
