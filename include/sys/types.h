#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

// __kernel_* types are defined here
#include <stdint.h>
#include <linux/types.h>

#ifndef _MODE_T_DECLARED
typedef __kernel_mode_t mode_t;
#define _MODE_T_DECLARED
#endif

#ifndef _SIZE_T_DECLARED
typedef __SIZE_TYPE__ size_t;
#define _SIZE_T_DECLARED
#endif

#ifndef _SSIZE_T_DECLARED
typedef __kernel_ssize_t ssize_t;
#define _SSIZE_T_DECLARED
#endif

#ifndef _DEV_T_DECLARED
typedef __kernel_old_dev_t dev_t;
#define _DEV_T_DECLARED
#endif

#ifndef _GID_T_DECLARED
typedef	__kernel_gid_t gid_t;
#define	_GID_T_DECLARED
#endif

#ifndef _UID_T_DECLARED
typedef	__kernel_uid_t uid_t;
#define	_UID_T_DECLARED
#endif

#ifndef _PID_T_DECLARED
typedef __kernel_pid_t pid_t;
#define _PIT_T_DECLARED
#endif

#ifndef _OFF_T_DECLARED
typedef __kernel_off_t off_t;
#define _OFF_T_DECLARED
#endif

#ifndef _USECONDS_T_DECLARED
typedef __kernel_suseconds_t useconds_t;
#define _USECONDS_T_DECLARED
#endif

#ifndef _VM_OFFSET_T_DECLARED
typedef uintptr_t vm_offset_t;
#define _VM_OFFSET_T_DECLARED
#endif

#ifndef _TIME_T_DECLARED
typedef __kernel_time_t time_t;
#define _TIME_T_DECLARED
#endif

#ifndef _CLOCK_T_DEFINED
typedef __kernel_clock_t clock_t;
#define _CLOCK_T_DEFINED
#endif

#ifndef _CLOCKID_T_DECLARED
typedef int clockid_t;
#define _CLOCKID_T_DECLARED
#endif

#ifndef _TIMER_T_DECLARED
typedef __kernel_timer_t timer_t;
#define _TIMER_T_DECLARED
#endif

#if __BSD_VISIBLE
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
#endif

#endif /* _SYS_TYPES_H */
