#pragma once

#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <mimalloc.h>

#define USE_MIMALLOC

class Arena
{
    private:
        char *data;
        size_t sz;

    public:
        Arena(size_t sz)
            :sz(sz)
        {
            #ifdef USE_MIMALLOC
                data = (char *)mi_malloc(sz * sizeof(char));
            #else
                data = (char *)malloc(sz * sizeof(char));
            #endif
        }

        size_t Read(off_t offset, char *dst, size_t n)
        {
            size_t limit = n;
            if (offset + n > sz){
                limit = sz - offset;
            }

            memcpy(dst, data + offset, limit);
            return limit;
        }

        size_t Write(off_t offset, char *src, size_t n)
        {
            size_t limit = n;
            if (offset + n > sz){
                limit = sz - offset;
            }

            memcpy(data + offset, src, limit);
            return limit;
        }

        
};