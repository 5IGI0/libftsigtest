#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <libft.h>

#include "../common/inspect.h"
#include "../common/colors.h"
#include "../common/macros.h"
#include "../common/sighandle.h"

int main(void)
{
    size_t start, still_alive;
    char **strs;

    setup_sighandle();
    
    STDOUT_WRITE(CLR_RST"ft_split\t: ");

    /* 1. first malloc crashes */
    SET_MMX(0);
    start = GET_MALIVE();
    strs = ft_split("a a  a a  a a a  a     aa a  a a a    a a a  a a   a ", ' ');
    UNSET_MMX();
    still_alive = GET_MALIVE() - start;
    if (still_alive == 0)
        STDOUT_WRITE(CLR_GRN"1.OK ");
    else
    {
        printf(CLR_RED"1.KO (%zd) ", GET_MALIVE() - start);
        fflush(stdout);
    }

    /* 2. x malloc crashes */
    SET_MMX(7);
    start = GET_MALIVE();
    strs = ft_split("a a  a a  a a a  a     aa a  a a a    a a a  a a   a ", ' ');
    UNSET_MMX();
    still_alive = GET_MALIVE() - start;
    if (still_alive == 0)
        STDOUT_WRITE(CLR_GRN"2.OK ");
    else
    {
        printf(CLR_RED"2.KO (%zd) ", GET_MALIVE() - start);
        fflush(stdout);
    }

    STDOUT_WRITE(CLR_RST"\n");
}