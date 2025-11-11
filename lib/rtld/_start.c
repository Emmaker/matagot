void _start() {
  register volatile long *sp __asm__("%sp");
  // store the stack register pointer
  volatile long *store_sp = sp;

  // obtain the auxv from the stack pointer without handling args
  char **auxv = (char **)store_sp + store_sp[0];
  while (*++auxv != 0)
    ;
  auxv++;

  sp = store_sp;
}
