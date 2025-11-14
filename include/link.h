#ifndef _LINK_H
#define _LINK_H

#include <elf.h>
#include <sys/types.h>
/*
 * Linked list of dynamically linked objects in program's memory.
 * Identical layout to the one in SRV4.
 */
struct link_map {
  unsigned long l_base;             // Base address of shared object
  const char *l_name;               // Absolute path of shared object
  const void *l_ld;                 // .dynamic table of shared object
  struct link_map *l_next, *l_prev; // Double linked list pointers
};

struct r_debug {
  int r_version;
  struct link_map *r_map;
  void (*r_brk)(struct r_debug *, struct link_map *);
  enum {
    RT_CONSISTENT,
    RT_ADD,
    RT_DELETE
  } r_state;
  void *r_ldbase;
};

struct dl_phdr_info {
  unsigned long dlpi_addr;
  const char *dlpi_name;
  const Elf64_Phdr *dlpi_phdr;
  unsigned short dlpi_phnum;
  unsigned long long int dlpi_adds;
  unsigned long long int dlpi_subs;
  size_t dlpi_tls_modid;
  void *dlpi_tls_data;
};

#endif
