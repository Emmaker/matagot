#!/bin/bash

# This program processes the asm/unistd_64.h kernel header
# and generates a matching sys/syscall.h UAPI header.
#
# UAPI is supposed to include linux/unistd.h, since the
# actual location of the defines can change. However, I do
# not feel like replicating #include functionality in a
# shell script, so it will simply be easier to change the
# path of the header being read if a kernel update changes
# the actual location of the defines.
ASM_UNISTD_H=$PWD/asm/unistd_64.h
SYS_SYSCALL_H=$PWD/sys/syscall.h

if [ ! -f "$ASM_UNISTD_H" ]; then
    echo "ERROR: $ASM_UNISTD_H not found. Please install kernel headers first."
    exit 1
fi
# remove the existing generated header if present
rm -f "$SYS_SYSCALL_H"

write() {
    echo "$1">> "$SYS_SYSCALL_H"
    echo "$1"
}

write "/* Generated via script. DO NOT MODIFY */"
write "#ifndef _SYS_SYSCALL_H"
write "#define _SYS_SYSCALL_H"
write ""
write "#include <linux/unistd.h>"
write ""

while IFS= read -r LINE; do
    if [[ "$LINE" =~ ^#define[[:space:]]+__NR_[a-zA-Z0-9_]+ ]]; then
        SYMBOL=$(echo "$LINE" | awk '{print $2}')

        write "#ifdef $SYMBOL"
        write "#define SYS_${SYMBOL#__NR_} $SYMBOL"
        write "#endif"
        write ""
    fi
done < "$ASM_UNISTD_H"

write ""
write "#endif /* _SYS_SYSCALL_H */"
