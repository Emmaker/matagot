.include <sys.args.mk>
CFLAGS+= -fvisibility=hidden -nostdlibinc -I./private

LIBNAME= libc
SRCS= ${TARGET}/longjmp.S ${TARGET}/setjmp.S ${TARGET}/siglongjmp.S ${TARGET}/sigsetjmp.S ${TARGET}/syscall.S
SRCS+= __libc_start_main.c sys/auxv.c environ.c sched.c

#.include "string/makefile.inc"

.include <sys.lib.mk>
