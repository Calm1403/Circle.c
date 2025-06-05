#ifndef MEM_H
#define MEM_H

typedef unsigned long long size_t;

void* obj_manager(const int behaviour, const size_t number, const size_t size, void** objs);

#endif