#include <errno.h>
#include <sys/auxv.h>
#include <sys/cdefs.h>

const Elf64_auxv_t *_auxv;

__exported unsigned long getauxval(unsigned long type) {
  if (type == AT_NULL)
    goto fail;

  const Elf64_auxv_t *auxv = _auxv;

  while (auxv->a_type != AT_NULL)
    if (auxv->a_type == type)
      return auxv->a_un.a_val;

fail:
  errno = ENOENT;
  return 0;
}
