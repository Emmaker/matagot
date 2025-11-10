.ifnmake __<sys.args.mk>__
__<sys.args.mk>__: .NOTMAIN

# We explicitly use clang in this household
CC!= which clang
LD!= which ld.lld

.ifndef CFLAGS
CFLAGS= -I. -std=gnu23 -fPIC
.ifdef SYSROOT
CFLAGS+= --sysroot=${SYSROOT} -I${SYSROOT}/include
.endif ## SYSROOT ##
.endif ## CFLAGS ##

.ifndef CCFLAGS
CCFLAGS= ${CFLAGS} -std=gnu++98
.endif ## CCFLAGS ##

.endif ## __<sys.args.mk>__ ##
