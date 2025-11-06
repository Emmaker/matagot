.if !defined(LIBNAME)
.error "LIBNAME must be defined"
.endif
.if !defined(SRCS)
.error "SRCS must be defined"
.endif

# TODO: modularize as needed
CC!= which cc
LD!= which ld

CFLAGS= -nostdlib
CFLAGS+= -MD
CFLAGS+= -I.
CFLAGS+= -std=gnu23
.ifdef _SYSROOT
CFLAGS+= -nostdlibinc -I${_SYSROOT}/include
CFLAGS+= --sysroot=${_SYSROOT}
.endif

ASFLAGS= ${CFLAGS}
ASFLAGS+= -g

CPPFLAGS= ${CFLAGS}
CPPFLAGS+= -nostdlib++ -nostdinc++
CPPFLAGS+= -std=gnu++98

.SUFFIXES: .c .o
.c.o:
	${CC} ${CFLAGS} ${CFLAGS.${.IMPSRC}} -c ${.IMPSRC} -o ${.TARGET}

.SUFFIXES: .S .o
.S.o:
	${CC} ${ASFLAGS} ${ASFLAGS.${.IMPSRC}} -c ${.IMPSRC} -o ${.TARGET}

.SUFFIXES: .cc .o
.cc.o:
	${CC} ${CPPFLAGS} ${CPPFLAGS.${.IMPSRC}} -c ${.IMPSRC} -o ${.TARGET}

OBJS= $(SRCS:S/.cc/.o/:S/.c/.o/:S/.S/.o/)
${LIBNAME}: ${OBJS}
	${LD} -o ${.TARGET} ${OBJS}
