all: crt1.o Scrt1.o ${MACHINE}/crti.o ${MACHINE}/crtn.o

crt1.o: crt1.c
	cc -c crt1.c -o ${.TARGET} 

Scrt1.o: Scrt1.c
	cc -c Scrt1.c -o ${.TARGET}

${MACHINE}/crti.o: ${MACHINE}/crti.S
	cc -c ${MACHINE}/crti.S -o ${.TARGET}

${MACHINE}/crtn.o: ${MACHINE}/crtn.S
	cc -c ${MACHINE}/crtn.S -o ${.TARGET}

clean: .PHONY
	rm -rf crt1.o Scrt1.o ${MACHINE}/crti.o ${MACHINE}/crtn.o