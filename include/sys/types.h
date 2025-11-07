#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

// __kernel_* types are defined here
#include <linux/types.h>

#ifndef _MODE_T_DECLARED
typedef __kernel_mode_t mode_t;
#define _MODE_T_DECLARED
#endif

#ifndef _SSIZE_T_DECLARED
typedef __kernel_ssize_t ssize_t;
#define _SSIZE_T_DECLARED
#endif

#ifndef _DEV_T_DECLARED
typedef __kernel_old_dev_t dev_t;
#define _DEV_T_DECLARED
#endif

#endif /* _SYS_TYPES_H */