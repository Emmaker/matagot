#ifndef _AUXV_H
#define _AUXV_H

// elf.h defines the *_auxv_t types and AT_* constants
#include <elf.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
extern unsigned long getauxval(unsigned long) __noexcept;
__END_DECLS

#endif /* _AUXV_H */
