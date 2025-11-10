.include <sys.args.mk>

.if !defined(LIBNAME)
.error "LIBNAME must be defined"
.endif
.if !defined(SRCS)
.error "SRCS must be defined"
.endif

LIBSUFFIX?= .so

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
