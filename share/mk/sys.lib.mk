.if !defined(LIBNAME)
.error "LIBNAME must be defined"
.endif
.if !defined(SRCS)
.error "SRCS must be defined"
.endif

LIBSUFFIX?= .so

# TODO: modularize as needed
# we explicitly use clang in this household
CC!= which clang
LD!= which ld.lld

CFLAGS= -nostdlib
CFLAGS+= -MD -fPIC
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

OBJS= ${SRCS:S/.cc/.o/:S/.c/.o/:S/.S/.o/}
_OUT= ${LIBNAME}${LIBSUFFIX}

${_OUT}: ${OBJS}
	${LD} -shared -o ${.TARGET} ${OBJS}

_ALL= ${OBJS} ${OBJS:S/.o/.d/} ${_OUT}
clean:
	rm -rf ${_ALL}
