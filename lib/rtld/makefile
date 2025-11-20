.include <sys.args.mk>
CFLAGS+= -fvisibility=internal -nostdlib -ffreestanding
CCFLAGS+= -fno-rtti -fno-exceptions

LIBNAME= ld-elf
SRCS+= _start.c dlfcn.c _dlmain.cc dl_object.cc
SRCS+= ${TARGET}/_syscall.S

.include <sys.lib.mk>
