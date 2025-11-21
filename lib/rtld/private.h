#include <elf.h>
#include <link.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/syscall.h>
// for mmap flags
#include <linux/mman.h>

__BEGIN_DECLS
long _syscall(long, ...);
#define exit(e) _syscall(SYS_exit, e)
#define mmap(addr, len, prot, flags, fd, offset) \
  _syscall(SYS_mmap, addr, len, prot, flags, fd, offset)
#define open(path, flag, mode) _syscall(SYS_open, path, flag, mode)
#define read(fd, buf, len) _syscall(SYS_read, fd, buf, len)
#define close(fd) _syscall(SYS_close, fd)
#define fstat(fd, buf) _syscall(SYS_fstat, fd, buf)

void _dlmain(Elf64_auxv_t *);
void parse_ld_conf(void);
unsigned long _getauvxal(unsigned long);

extern Elf64_auxv_t *_auxv;
__END_DECLS

// Checks for possible errno and exits if true
#define expect(var) if (var & -4095) exit(-var);

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
    uintptr_t region = mmap(
        // any address, 2 pages, rw, only for this process
        0, region_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,
        0);
    // indicative of an error
    expect(region);

    pool_free_object *head = (pool_free_object *)region;
    if (this->head == 0)
      this->head = head;
    else
      this->head->next = head;
    head = (pool_free_object *)((uintptr_t)head + object_size);

    do {
      pool_free_object *next =
          (pool_free_object *)((uintptr_t)head + object_size);
      head->next = next;
      head = next;
    } while ((uintptr_t)head < (region + region_size));
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
  _Static_assert(
      object_size >= sizeof(pool_free_object),
      "Pooled object is larger than linked list");
};

/*
 * Utility iterator class for iterating through ELF binary headers (Phdr, Shdr).
 */
template <typename T> class ElfHdrIterator {
public:
  // we have to use some *awkward* values so we don't have to include <iterator>
  typedef struct forward_iterator_tag {
  } iterator_category;
  typedef T value_type;
  typedef intptr_t difference_type;
  typedef T *pointer;
  typedef T &reference;

  ElfHdrIterator(T *ptr, size_t size, size_t count, size_t current = 0)
      : size(size), count(count) {
    ptr = (T *)((uintptr_t)ptr + size * current);
  }

  reference operator*() const { return *ptr; }
  pointer operator->() const { return ptr; }

  ElfHdrIterator &operator++() {
    ptr = (T *)((uintptr_t)ptr + size);
    return *this;
  }
  ElfHdrIterator operator++(int) {
    ElfHdrIterator tmp = *this;
    ptr = (T *)((uintptr_t)ptr + size);
    return tmp;
  }

  bool operator==(const ElfHdrIterator &other) const {
    return ptr == other.ptr;
  }
  bool operator!=(const ElfHdrIterator &other) const { return !this == other; }

private:
  T *ptr;
  size_t size;
  size_t count;
};
#endif /* __cplusplus */

/*
 * Struct representing a dynamically loaded "object" (exe, .so). The structure
 * of this is freely modifiable, as it should never be accessed outside the
 * dynamic linker.
 */
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

/*
 * To keep a consistent memory footprint, and preventing the need for resizeable
 * arrays so we can use the dl_pool allocator for dl_objects, object
 * dependencies (i.e. NEEDED objects in the dynamic table) will be tracked via
 * linked list.
 *
 * This also permits reuse of dl_objects as dependencies, preventing duplication
 * or weird logic to account for duplicates.
 */
struct dl_object_dep {
  struct dl_object_dep *next;
  struct dl_object *obj;

#ifdef __cplusplus
  dl_object_dep(dl_object_dep *next, dl_object *obj) : next(next), obj(obj) {}
  // new operator does not support quantities greater than 1
  void *operator new(unsigned long);
#endif /* __cplusplus */
};
