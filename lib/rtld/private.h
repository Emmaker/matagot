#include <elf.h>
#include <link.h>
#include <new>
#include <sys/cdefs.h>
#include <sys/syscall.h>
// for mmap flags
#include <linux/mman.h>

__BEGIN_DECLS
long _syscall(long, ...);
#define exit(e) _syscall(SYS_exit, e)
#define mmap(addr, len, prot, flags, fd, offset)                               \
  _syscall(SYS_mmap, addr, len, prot, flags, fd, offset)

void _dlmain(Elf64_auxv_t *);
__END_DECLS

#if TARGET == x86_64
  #define R_TARGET_RELATIVE R_X86_64_RELATIVE
#else
  #error "Unsupported architecture"
#endif

#ifdef __cplusplus
/*
 * Since we don't have malloc in a freestanding environment, this template
 * provides a method for allocating rarely-freed equal size objects.
 *
 * Things like metadata for loaded objects should be allocated with this, since
 * they are many and equally sized.
 */
template <int object_size> class dl_pool {
public:
  void *alloc() {
    // a null head means it's full
    if (this->head == 0)
      expand();

    pool_free_object *obj = this->head;
    this->head = obj->next;

    return (void *)(obj);
  }

  void expand() {
  #define region_size 0x2000
    unsigned long region = mmap(
        // any address, 2 pages, rw, only for this process
        0, region_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,
        0);
    // indicative of an error
    if (region & -4095)
      exit(region);

    struct pool_free_object head = (void *)region;
    if (this->head == 0)
      this->head = head;
    else
      this->head->next = head;
    head = &head + object_size;

    do {
      head->next = &head + object_size;
      head = &head + object_size;
    } while (&head < (region + region_size));
  #undef region_size
  }

  void free(void *obj) {
    pool_free_object *free_obj = (pool_free_object *)obj;

    free_obj->next = this->head;
    this->head = free_obj;
  }

private:
  // one-way linked list of free objects
  struct pool_free_object {
    pool_free_object *next;
  };
  pool_free_object *head;

  // objects must be large enough to store the linked list
  _Static_assert(object_size >= sizeof(pool_free_object));
};
#endif /* __cplusplus */

struct dl_object {
  struct link_map map;
  struct dl_object_dep *dep;

#ifdef __cplusplus
  dl_object() {}
  // new operator does not support quantities greater than 1
  void *operator new(unsigned long);

  void add_dependency(dl_object *);
#endif /* __cplusplus */
};

struct dl_object_dep {
  struct dl_object_dep *next;
  struct dl_object *obj;

#ifdef __cplusplus
  dl_object_dep(dl_object_dep *next, dl_object *obj) : next(next), obj(obj) {}
  // new operator does not support quantities greater than 1
  void *operator new(unsigned long);
#endif /* __cplusplus */
};
