#ifndef SIGHANDLE_H
# define SIGHANDLE_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>

# include "colors.h"
# include "macros.h"

static void mdr_sighandle(int sig) {
    STDOUT_WRITE(CLR_RED" ?.KO (SEGFAULT)\n");
    exit(0);
}

static void setup_sighandle(void) {
    signal(SIGSEGV, mdr_sighandle);
}

#endif