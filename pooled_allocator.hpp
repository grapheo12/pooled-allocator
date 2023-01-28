#pragma once

#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string>
#include <cstring>

#define ARENA_USE_HUGEPAGES
#define ARENA_HUGEPAGE_SIZE (1 << 21)                   // 2 MiB hugepage

class Arena
{
    private:
        char *data;
        size_t sz;

    public:
        Arena(size_t sz)
            :sz(sz)
        {
            #ifdef ARENA_USE_HUGEPAGES
                posix_memalign((void **)&data, ARENA_HUGEPAGE_SIZE, sz);
                madvise(data, sz, MADV_HUGEPAGE);                   // Specific to Linux only
            #else
                data = new char[sz];
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