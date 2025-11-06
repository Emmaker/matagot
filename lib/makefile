all: crt libc libm .PHONY

crt: .PHONY
	${MAKE} -C crt

libc: .PHONY
	${MAKE} -C libc

libm: libc .PHONY
	${MAKE} -C libm

clean: .PHONY
	${MAKE} -C crt clean
	${MAKE} -C libc clean
	${MAKE} -C libm clean