#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>

#define __GNU_VISIBLE
#define __BSD_VISIBLE
#include <sched.h>

__exported int sched_get_priority_min(int policy) {
#ifdef SYS_sched_get_priority_min
  return scall(SYS_sched_get_priority_min, policy);
#else
  errno = ENOSYS;
  return -1;
#endif
}

__exported int sched_get_priority_max(int policy) {
#ifdef SYS_sched_get_priority_max
  return scall(SYS_sched_get_priority_max, policy);
#else
  errno = ENOSYS;
  return -1;
#endif
}

__exported int sched_getparam(pid_t pid, struct sched_param *param) {
#ifdef SYS_sched_getparam
  return scall(SYS_sched_getparam, pid, param);
#else
  errno = ENOSYS;
  return -1;
#endif
}

__exported int sched_setparam(pid_t pid, const struct sched_param *param) {
#ifdef SYS_sched_setparam
  return scall(SYS_sched_setparam, pid, param);
#else
  errno = ENOSYS;
  return -1;
#endif
}

__exported int sched_getscheduler(pid_t pid) {
#ifdef SYS_sched_getscheduler
  return scall(SYS_sched_getscheduler, pid);
#else
  errno = ENOSYS;
  return -1;
#endif
}

__exported int
sched_setscheduler(pid_t pid, int policy, const struct sched_param *param) {
#ifdef SYS_sched_setscheduler
  return scall(SYS_sched_setscheduler, pid, policy, param);
#else
  errno = ENOSYS;
  return -1;
#endif
}

__exported int sched_rr_get_interval(pid_t pid, struct timespec *t) {
#ifdef SYS_sched_rr_get_interval
  return scall(SYS_sched_setscheduler, pid, t);
#else
  errno = ENOSYS;
  return -1;
#endif
}

__exported int
sched_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *cpuset) {
#ifdef SYS_sched_getaffinity
  return scall(SYS_sched_getaffinity, cpusetsize, cpuset);
#else
  errno = ENOSYS;
  return -1;
#endif
}

__exported int
sched_setaffinity(pid_t pid, size_t cpusetsize, const cpu_set_t *cpuset) {
#ifdef SYS_sched_setaffinity
  return scall(SYS_sched_setaffinity, cpusetsize, cpuset);
#else
  errno = ENOSYS;
  return -1;
#endif
}

__exported int sched_getcpu(void) {
#ifdef SYS_getcpu
  return scall(SYS_getcpu);
#else
  errno = ENOSYS;
  return -1;
#endif
}

__exported int sched_yield(void) {
#ifdef SYS_sched_yield
  return scall(SYS_sched_yield);
#else
  errno = ENOSYS;
  return -1;
#endif
}
