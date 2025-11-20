#include <fcntl.h>
#include <sys/stat.h>

#include "private.h"

static char *ld_conf;

void parse_ld_conf() {
  int Ld_conf_fd = open("/etc/ld.so.conf", 0 /* O_RDONLY */, 0);
  expect(Ld_conf_fd);

  struct stat statbuf;
  expect(fstat(Ld_conf_fd, &statbuf));
}