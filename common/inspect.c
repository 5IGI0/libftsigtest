#include <stdlib.h>
#include <stddef.h>

#include "inspect.h"

typedef struct data_struct {
    size_t m;
    size_t f;
    size_t err_at;
} data_type;

#define DATA (*get_data())

static data_type *get_data() {
    static data_type data = {
        .m = 0,
        .f = 0,
        .err_at = (size_t)-1
    };
    return &data;
}


void    *my_malloc(size_t size) {
    if (size & INSPCT_CODE_CHECK)
    {
        int code = size >> INSPCT_CODE_SHIFT;
        if (code == INSPCT_GET_MCOUNT)
            return (void *) DATA.m;
        if (code == INSPCT_GET_FCOUNT)
            return (void *) DATA.f;
        if (code == INSPCT_SET_MMX)
            DATA.err_at = DATA.m + (size & (~INSPCT_CODE_CHECK));
        if (code == INSPCT_UNSET_MMX)
            DATA.err_at = (size_t)-1;
        return 0;
    }
    if (DATA.err_at == DATA.m)
        return NULL;
    void *tmp = malloc(size);
    if (tmp)
        DATA.m++;
    return tmp;
}

void my_free(void *ptr) {
    if (ptr)
        DATA.f++;
    free(ptr);
}

typedef struct interpose_s { void *new_func;
                   void *orig_func; } interpose_t;

__attribute__((used)) static const interpose_t interposing_functions[] \
    __attribute__ ((section("__DATA, __interpose"))) = {
        { (void *)my_malloc,  (void *) malloc  },
        { (void *)my_free,    (void *) free    }
    };