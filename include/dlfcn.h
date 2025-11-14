#ifndef _DLFCN_H
#define _DLFCN_H

/*
 * Note about Matagot's dlfcn implementation:
 *
 * These functions are not part of the C standard library, or of any shared
 * object except for ld.so, the runtime dynamic linker itself. Static binaries
 * that do not use the runtime dynamic linker cannot have dynamic linking
 * capabilities. This should not be an issue, as I do not foresee any binaries
 * dynamic linking without being dynamically linked.
 */
#include <sys/cdefs.h>

#define RTLD_LAZY 0
#define RTLD_NOW 1
#define RTLD_GLOBAL 2
#define RTLD_LOCAL 3

__BEGIN_DECLS
int dlclose(void *);
char *dlerror(void);
void *dlopen(void);
void *dlsym(void *__restrict, const char *__restrict);
#if defined(__GNU_VISIBLE) || defined (__BSD_VISIBLE)
int dlinfo(void *__restrict, int, void *__restrict);
#endif
__END_DECLS

#endif
