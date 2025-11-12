#include <sys/cdefs.h>
#include <sys/syscall.h>

__BEGIN_DECLS
long _syscall(long, ...);
#define exit(e) _syscall(SYS_exit, e)
__END_DECLS
