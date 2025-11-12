#include <complex.h>
#include <elf.h>
#include <sys/cdefs.h>

#include "private.h"

__exported void _start() {
  register volatile long *sp __asm__("%sp");
  // store the stack register pointer
  volatile long *store_sp = sp;

  /*
   * obtain the auxv from the stack pointer without handling args and skipping
   * through envp
   */
  char **envp = (char **)store_sp + store_sp[0];
  while (*++envp != 0)
    ;
  Elf64_auxv_t *auxv = (Elf64_auxv_t *)++envp;

  /*
   * after calculating the auxv, obtain the ELF header from AT_BASE (base
   * address of the dynamic linker)
   */
  Elf64_Ehdr *ehdr = (void *)auxv[AT_BASE].a_un.a_val;
  // get program headers address from ehdr
  char *phdrs = (char *)ehdr + ehdr->e_phoff;

  // iterate through program headers
  Elf64_Phdr *dynamic = 0;
  for (int i = ehdr->e_phnum; i != 0; i--) {
    Elf64_Phdr *phdr = (Elf64_Phdr *)phdrs;

    // the PT_DYNAMIC dynamic table contains info on relocations
    if (phdr->p_type == PT_DYNAMIC) {
      dynamic = (void *)((char *)ehdr + phdr->p_offset);
      break;
    }

    phdrs += ehdr->e_phentsize;
  }

  // if there is no dynamic table, something is VERY wrong
  if (dynamic == 0)
    exit(1);

  Elf64_Rel *rels;   // relocation table
  Elf64_Rela *relas; // relocation table with addends
  // total size (sz) and individual entry size (ent) of rel and rela
  long rel_sz, rel_ent, rela_sz, rela_ent;
  // the dynamic table itself
  Elf64_Dyn *dyn_table = (Elf64_Dyn *)((char *)ehdr + dynamic->p_offset);

  // iterate through the dynamic table, and apply relocations
  int dyn_num = dynamic->p_memsz / sizeof(Elf64_Dyn);
  for (int i = 0; i < dyn_num; i++) {
    Elf64_Dyn *dyn = &dyn_table[dyn_num];
  }

  sp = store_sp;
}
