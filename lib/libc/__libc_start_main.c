#include <elf.h>
#include <stdnoreturn.h>
#include <sys/auxv.h>
#include <sys/cdefs.h>
#include <stdlib.h>

const char *__progname;

extern char **environ;
extern const Elf64_auxv_t *_auxv;

void handle_argv(int argc, char **argv) {
  char **env = argv + argc;
  if (!environ)
    environ = env;

  char **auxv = env;
  while (*++auxv != 0)
    ;
  _auxv = (const Elf64_auxv_t *)auxv;

  __progname =
      (argc > 0 && argv[0] != 0) ? argv[0] : (const char *)getauxval(AT_EXECFN);
  for (const char *s = __progname; *s != '\0'; s++)
    if (*s == '/')
      __progname = s + 1;
}

__exported noreturn void
__libc_start_main(int (*main)(int, char **, char **), int argc, char **argv) {
  handle_argv(argc, argv);
  exit(main(argc, argv, environ));
}
