#ifndef _ERRNO_H_
#define _ERRNO_H_

#include <sys/cdefs.h>
#include <linux/errno.h>

extern
#ifdef __cplusplus
    "C"
#endif
    int *
    __errno_location(void) __noexcept;

#define errno (*__errno_location())

#endif /* _ERRNO_H_ */