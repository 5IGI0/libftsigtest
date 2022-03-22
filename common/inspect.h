/**
 * author: 5IGI0
 * 
 * README
 * if you use file-related code (fopen, fread, etc.) you use them before.
 * for example if you use printf, the malloc count will be wrong.
 * because printf seems to malloc a buffer or something.
 * 
 */
#ifndef INSPECT_H
#define INSPECT_H

#include <stddef.h>

#define INSPCT_CODE_SIZE 3 // tailles des codes en bits
#define INSPCT_CODE_SHIFT ((sizeof(void *)*8)-INSPCT_CODE_SIZE)
#define INSPCT_CODE_CHECK (((size_t)-1)<<INSPCT_CODE_SHIFT)
#define INSPCT_GET_MCOUNT 1 // nombre de malloc executé
#define INSPCT_GET_FCOUNT 2 // nombre de free executé
#define INSPCT_SET_MMX    3 // nombre de malloc avant une fausse erreur
#define INSPCT_UNSET_MMX  4 // enlever la limite de malloc

#define MCMD(code, arg) (((size_t)code)<<INSPCT_CODE_SHIFT|arg)
#define GET_MCOUNT() ((size_t)malloc(MCMD(INSPCT_GET_MCOUNT, 0)))
#define GET_FCOUNT() ((size_t)malloc(MCMD(INSPCT_GET_FCOUNT, 0)))
#define SET_MMX(count) ((void)malloc(MCMD(INSPCT_SET_MMX, count)))
#define UNSET_MMX() ((void)malloc(MCMD(INSPCT_UNSET_MMX, 0)))
#define GET_MALIVE() (GET_MCOUNT() - GET_FCOUNT())

#endif