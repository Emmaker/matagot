#ifndef _ELF_H
#define _ELF_H

#include <stdint.h>

typedef struct {
  uint32_t a_type;
  union {
    uint32_t a_val;
    /*
     * We do not define a ptr here as on 64 bit platforms it will inflate the
     * union to 64 bits
     */
  } a_un;
} Elf32_auxv_t;

typedef struct {
  uint64_t a_type;
  union {
    uint64_t a_val;
    void *a_ptr;
  } a_un;
} Elf64_auxv_t;

// linux/auxvec.h defines the AT_* constants
#include <linux/auxvec.h>

#endif /* _ELF_H */