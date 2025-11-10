#ifndef _SCHED_H
#define _SCHED_H

#include <sys/cdefs.h>
#include <time.h>
#include <sys/types.h>
// for SCHED_* defines
#include <linux/sched.h>

struct sched_param {
  int sched_priority;
};

#define CPU_SETSIZE 1024
typedef struct {
  char _bits[CPU_SETSIZE];
} cpu_set_t;

__BEGIN_DECLS
extern int sched_get_priority_min(int algorithm) __noexcept;
extern int sched_get_priority_max(int algorithm) __noexcept;

extern int sched_getparam(pid_t, struct sched_param *) __noexcept;
extern int sched_setparam(pid_t, const struct sched_param *) __noexcept;

extern int sched_getscheduler(pid_t) __noexcept;
extern int
sched_setscheduler(pid_t, int, const struct sched_param *) __noexcept;

extern int sched_rr_get_interval(pid_t, struct timespec *) __noexcept;

#if defined(__GNU_VISIBLE) || defined(__BSD_VISIBLE)
extern int sched_getaffinity(pid_t, size_t, cpu_set_t *) __noexcept;
extern int sched_setaffinity(pid_t, size_t, const cpu_set_t *) __noexcept;
#endif
#ifdef __BSD_VISIBLE
extern int sched_getcpu(void) __noexcept;
#endif
extern int sched_yield(void) __noexcept;
__END_DECLS

#endif /* _SCHED_H */
