#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <libft.h>

#include "../common/inspect.h"
#include "../common/colors.h"
#include "../common/macros.h"
#include "../common/sighandle.h"

int count = 0;

void *f(void *elem)
{
    count++;
    return (void *)elem;
}

void del(void *elem)
{
    count--;
}

int main(void) {
    t_list *ret, a = {.content = "AH!"}, b  = {.content = " '-' "}, c = {.content = "what is this bro"};

    a.next = &b;
    b.next = &c;

    setup_sighandle();

    STDOUT_WRITE(CLR_RST"ft_lstmap      : ");

    /* 1. check for allocation failure */
    SET_MMX(0);
    ret = ft_lstmap(&a, f, del);
    UNSET_MMX();
    if (ret)
        STDOUT_WRITE(CLR_RED"1.KO (non-null return) ");
    else
        STDOUT_WRITE(CLR_GRN"1.OK ");

    /* 2. check for allocation failure during iteration */
    SET_MMX(2);
    ret = ft_lstmap(&a, f, del);
    UNSET_MMX();
    if (ret)
        STDOUT_WRITE(CLR_RED"1.KO (non-null return) ");
    else if (count > 0)
        STDOUT_WRITE(CLR_RED"2.KO (del() not called) ");
    else if (count < 0)
        STDOUT_WRITE(CLR_RED"2.KO (del() called too much) ");
    else
        STDOUT_WRITE(CLR_GRN"2.OK ");

    STDOUT_WRITE(CLR_RST"\n");
    return 0;
}