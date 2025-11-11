all: rtld crt libc libm .PHONY

crt: .PHONY
	${MAKE} -C crt

libc: .PHONY
	${MAKE} -C libc

libm: libc .PHONY
	${MAKE} -C libm

rtld: .PHONY
	${MAKE} -C rtld

clean: .PHONY
	${MAKE} -C crt clean
	${MAKE} -C libc clean
	${MAKE} -C libm clean
	${MAKE} -C rtld clean
