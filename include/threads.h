#ifndef _THREADS_H
#define _THREADS_H

#include <sys/cdefs.h>
// #include <time.h>

typedef struct _thread *thrd_t;
typedef struct _mutex mtx_t;
typedef struct _thread_condition cnd_t;
typedef struct _tss *tss_t;
typedef void (*tss_dtor_t)(void *);
typedef int (*thrd_start_t)(void *);
enum { thrd_success = 0, thrd_busy, thrd_error, thrd_nomem, thrd_timedout };
enum { mtx_plain = 0, mtx_recursive = 1, mtx_timed = 2 };
typedef struct {
  int done;
} once_flag;

#define ONCE_FLAG_INIT                                                         \
  { 0 }
// may already be compiler defined
#ifndef THREAD_LOCAL
  #define THREAD_LOCAL _Thread_local
#endif

__BEGIN_DECLS
extern int thrd_create(thrd_t *thr, thrd_start_t func, void *arg);
extern int thrd_equal(thrd_t lhs, thrd_t rhs);
extern thrd_t thrd_current(void);
extern int
thrd_sleep(const struct timespec *time_point, struct timespec *remaining);
extern void thrd_yield(void);
extern void thrd_exit(int res);
extern void thrd_join(thrd_t thr, int *res);
extern int thrd_detach(thrd_t thr);

extern int mtx_init(mtx_t *mutex, int type);
extern void mtx_destroy(mtx_t *mutex);
extern int mtx_lock(mtx_t *mutex);
extern int mtx_trylock(mtx_t *mutex);
extern int mtx_timedlock(
    mtx_t *restrict mutex, const struct timespec *restrict time_point);
extern int mtx_unlock(mtx_t *mutex);

extern int cnd_init(cnd_t *cond);
extern void cnd_destroy(cnd_t *COND);
extern int cnd_signal(cnd_t *cond);
extern int cnd_broadcast(cnd_t *cond);
extern int cnd_wait(cnd_t *cond, mtx_t *mutex);
extern int cnd_timedwait(
    cnd_t *restrict cond, mtx_t *restrict mutex,
    const struct timespec *restrict time_point);

extern int tss_create(tss_t *tss_id, tss_dtor_t destructor);
extern void tss_delete(tss_t tss_id);
extern int tss_set(tss_t tss_id, void *val);
extern void *tss_get(tss_t key);

extern void call_once(once_flag *flag, void (*func)(void));

#ifdef __BSD_VISIBLE
extern int mtx_is_locked(mtx_t *mtx);
#endif
__END_DECLS

#endif /* _THREADS_H */
