#include "private.h"

extern "C" void _dlmain(Elf64_auxv_t *auxv) {
  dl_object* bin = new dl_object();
}
