#ifndef _SYS_STAT_H
#define _SYS_STAT_H

struct stat {
  unsigned long st_dev;
  unsigned long st_ino;
  unsigned int st_mode;
  unsigned int st_nlink;
  unsigned int st_uid;
  unsigned int st_gid;
  unsigned long st_rdev;
  unsigned long __pad1;
  long st_size;
  int st_blksize;
  int __pad2;
  long st_blocks;
  int st_atime;
  unsigned int st_atime_nsec;
  int st_mtime;
  unsigned int st_mtime_nsec;
  int st_ctime;
  unsigned int st_ctime_nsec;
  unsigned int __unused4;
  unsigned int __unused5;
};

#endif