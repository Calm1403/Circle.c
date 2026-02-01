#ifndef BOARD_H
#define BOARD_H

typedef struct board_s
{
  int size;
  char* data;
} board_t;

typedef struct winfo_s winfo_t;

board_t*
board_create(const int width,
             const int height,
             const winfo_t* const window_info);

#endif
