#ifndef _ERRNO_H
#define _ERRNO_H

#include <sys/cdefs.h>
#include <asm-generic/errno.h>

extern
#ifdef __cplusplus
    "C"
#endif
    int *
    __errno_location(void) __noexcept;

#define errno (*__errno_location())

#endif /* _ERRNO_H */