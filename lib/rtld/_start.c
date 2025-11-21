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

  // the dynamic table itself
  Elf64_Dyn *dyn_table = (Elf64_Dyn *)((char *)ehdr + dynamic->p_offset);

  // calculate the number of rel symbols from total size (sz) and entry size
  int rel_num =
      dyn_table[DT_RELSZ].d_un.d_val / dyn_table[DT_RELENT].d_un.d_val;
  // calculate rel table address and perform relocations
  Elf64_Rel *rel_table =
      (Elf64_Rel *)((char *)ehdr + dyn_table[DT_REL].d_un.d_ptr);
  for (int i = 0; i < rel_num; i++) {
    switch (rel_table[i].r_info) {
    case R_TARGET_RELATIVE:
      rel_table[i].r_offset += (unsigned long)ehdr;
      break;
    default:
      break;
    }
  }

  // dito but for rela (rel with addends)
  int rela_num =
      dyn_table[DT_RELASZ].d_un.d_val / dyn_table[DT_RELENT].d_un.d_val;
  Elf64_Rela *rela_table =
      (Elf64_Rela *)((char *)ehdr + dyn_table[DT_RELA].d_un.d_val);
  for (int i = 0; i < rela_num; i++) {
    switch (rela_table[i].r_info) {
    case R_TARGET_RELATIVE:
      rela_table[i].r_offset = (unsigned long)ehdr + rela_table[i].r_addend;
      break;
    default:
      break;
    }
  }

  // jump to main linker routine
  _dlmain(auxv);

  // retrieve the entry point, restore stack to original value, and call
  volatile register void (*entry)() = (void *)auxv[AT_ENTRY].a_un.a_val;
  sp = store_sp;
  entry();
  __unreachable();
}
