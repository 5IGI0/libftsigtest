#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <libft.h>

#include "../common/inspect.h"
#include "../common/colors.h"
#include "../common/macros.h"
#include "../common/sighandle.h"


int main(void) {
    void *ptr;

    setup_sighandle();
    
    STDOUT_WRITE(CLR_RST"ft_calloc\t: ");

    /* 1. malloc error */
    SET_MMX(0);
    ptr = ft_calloc(1, 1);
    UNSET_MMX();
    if (ptr)
        STDOUT_WRITE(CLR_RED"1.KO (non-null return) ");
    else
        STDOUT_WRITE(CLR_GRN"1.OK ");

    /* 2. integer overflow */
    SET_MMX(1);
    ptr = ft_calloc((((size_t)-1)>>(sizeof(size_t)>>2)) + 1, (((size_t)-1)>>(sizeof(size_t)>>2)) + 1);
    UNSET_MMX();
    if (ptr)
        STDOUT_WRITE(CLR_RED"2.KO (non-null return) ");
    else
        STDOUT_WRITE(CLR_GRN"2.OK ");

    STDOUT_WRITE(CLR_RST"\n");
}