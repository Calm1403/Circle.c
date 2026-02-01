#ifndef WINFO_H
#define WINFO_H

typedef struct winfo_s
{
  int ccols;
  int crows;
} winfo_t;

winfo_t*
winfo_create(void);

#endif
