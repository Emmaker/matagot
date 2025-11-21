#include "private.h"

Elf64_auxv_t *_auxv;

unsigned long _getauxval(unsigned long key) {
  Elf64_auxv_t *auxv = _auxv;
  while (auxv->a_type != AT_NULL) {
    if (auxv->a_type == key) {
      return auxv->a_un.a_val;
    }
    auxv++;
  }
  return 0;
}
