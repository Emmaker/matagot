int main(int, char **, char **);
/*
 * This signature is only compatible with newer-than-old glibc versions and, of
 * course, this libc. Older glibc versions expect a few more values to be passed
 * on, which in this situation will end up being junk data. Still, some
 * compatibility is better than none.
 */
[[noreturn]] extern void __libc_start_main(int (*)(int, char **, char **), int,
                                           char **);

void _start() {
  register volatile long *sp __asm__("sp");
  __libc_start_main(main, sp[0], (char **)sp + 1);
}