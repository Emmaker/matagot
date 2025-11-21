#include <sys/stat.h>

#include "private.h"

static char *ld_conf;

void parse_ld_conf() {
  int Ld_conf_fd = open("/etc/ld.so.conf", 0 /* O_RDONLY */, 0);
  expect(Ld_conf_fd);

  struct stat statbuf;
  int ret = fstat(Ld_conf_fd, &statbuf);
  expect(ret);

  size_t pagesz = _getauvxal(AT_PAGESZ);
  size_t mapsz = (statbuf.st_size + pagesz - 1) & ~(pagesz - 1);

  ld_conf = (char *)mmap(0, mapsz, PROT_READ, MAP_PRIVATE, Ld_conf_fd, 0);
  expect((uintptr_t)ld_conf);

  ret = read(Ld_conf_fd, ld_conf, statbuf.st_size);
  expect(ret);
  close(Ld_conf_fd);
}
