#ifndef _STD_STDLIB_H
#define _STD_STDLIB_H

#include "fslc/fslc_stdlib.h"

#define malloc __qtum_malloc
#define free __qtum_free
#define realloc __qtum_realloc
#define calloc __qtum_calloc

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

//implemented in libqtum
void* __qtum_malloc(unsigned int sz);
void* __qtum_calloc(unsigned int sz);
void __qtum_free(void* mem);
void* __qtum_realloc(void* mem, unsigned int newsz);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* _STD_STDLIB_H */
