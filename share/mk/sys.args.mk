.ifnmake __<sys.args.mk>__
__<sys.args.mk>__: .NOTMAIN

# for TARGET and TARGET_ARCH
.include <sys.mach.mk>

# We explicitly use clang in this household
CC!= which clang
LD!= which ld.lld

.ifndef CFLAGS
CFLAGS= -I. -std=gnu23 -fPIC -DTARGET=${TARGET} -DTARGET_ARCH=${TARGET_ARCH}
.ifdef SYSROOT
CFLAGS+= --sysroot=${SYSROOT} -I${SYSROOT}/include
.endif ## SYSROOT ##
.endif ## CFLAGS ##

.ifndef CCFLAGS
CCFLAGS= ${CFLAGS} -std=gnu++98
.endif ## CCFLAGS ##

.endif ## __<sys.args.mk>__ ##
