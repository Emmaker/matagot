#include <dlfcn.h>
#include <sys/cdefs.h>

__protected int dlclose(void *handle) {}

__protected char *dlerror(void) {}

__protected void *dlopen(void) {}

__protected void *dlsym(void *__restrict handle, const char *__restrict name) {}

__protected int
dlinfo(void *__restrict handle, int request, void *__restrict p) {}
