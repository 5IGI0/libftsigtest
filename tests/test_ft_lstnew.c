#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <libft.h>

#include "../common/inspect.h"
#include "../common/colors.h"
#include "../common/macros.h"
#include "../common/sighandle.h"

int main(void) {
    t_list *str;

    setup_sighandle();

    STDOUT_WRITE(CLR_RST"ft_lstnew      : ");

    /* 1. check for allocation failure */
    SET_MMX(0);
    str = ft_lstnew("qu'est-ce qui est jaune et qui attend ?");
    UNSET_MMX();
    if (str)
        STDOUT_WRITE(CLR_RED"1.KO (non-null return) ");
    else
        STDOUT_WRITE(CLR_GRN"1.OK ");

    STDOUT_WRITE(CLR_RST"\n");
    return 0;
}