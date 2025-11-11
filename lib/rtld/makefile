.include <sys.args.mk>
CFLAGS+= -fvisibility=hidden -nostdlib -nostartfiles -ffreestanding

LIBNAME= "ld-elf"
SRCS+= _start.c
SRCS+= ${TARGET}/_syscall.S

.include <sys.lib.mk>
