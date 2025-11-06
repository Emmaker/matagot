/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fenv.h - floating-point environment

   AUTHOR: Gregory Pietsch
*/

#ifndef __FENV_H__
#define __FENV_H__

#include <sys/cdefs.h>

/* DESCRIPTION:

   The functionality described on this reference page is aligned with the
   ISO C standard. Any conflict between the requirements described here and
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers
   to the ISO C standard.

   The <fenv.h> header shall define the following data types through typedef:

   fenv_t

   Represents the entire floating-point environment. The floating-point
   environment refers collectively to any floating-point status flags and
   control modes supported by the implementation.

   fexcept_t

   Represents the floating-point status flags collectively, including any
   status the implementation associates with the flags. A floating-point
   status flag is a system variable whose value is set (but never cleared)
   when a floating-point exception is raised, which occurs as a side-effect
   of exceptional floating-point arithmetic to provide auxiliary information.
   A floating-point control mode is a system variable whose value may be set
   by the user to affect the subsequent behavior of floating-point arithmetic.
*/

typedef int fexcept_t;
typedef struct
{
  int _FErounding;
  fexcept_t _FEexcepts;
} fenv_t;


/* The <fenv.h> header shall define each of the following macros if and only
   if the implementation supports the floating-point exception by means of
   the floating-point functions feclearexcept(), fegetexceptflag(),
   feraiseexcept(), fesetexceptflag(), and fetestexcept(). The defined macros
   shall expand to integer constant expressions with values that are
   bitwise-distinct.
*/
#define FE_DIVBYZERO	(1)
#define FE_INEXACT	(2)
#define FE_INVALID	(4)
#define FE_OVERFLOW	(8)
#define FE_UNDERFLOW	(0x10)

/* If the implementation supports the IEC 60559 Floating-Point option, all
   five macros shall be defined.  Additional implementation-defined floating-
   point exceptions with macros beginning with FE_ and an uppercase letter
   may also be specified by the implementation.

   The <fenv.h> header shall define the macro FE_ALL_EXCEPT as the bitwise-
   inclusive OR of all floating-point exception macros defined by the
   implementation, if any. If no such macros are defined, then the macro
   FE_ALL_EXCEPT shall be defined as zero.
*/
#define FE_ALL_EXCEPT	(0x1F)

/* The <fenv.h> header shall define each of the following macros if and only
   if the implementation supports getting and setting the represented rounding
   direction by means of the fegetround() and fesetround() functions. The
   defined macros shall expand to integer constant expressions whose values
   are distinct non-negative values.
*/
#define FE_DOWNWARD	(1)
#define FE_TONEAREST	(2)
#define FE_TOWARDZERO	(3)
#define FE_UPWARD	(4)

/* If the implementation supports the IEC 60559 Floating-Point option, all
   four macros shall be defined. Additional implementation-defined rounding
   directions with macros beginning with FE_ and an uppercase letter may also
   be specified by the implementation.

   The <fenv.h> header shall define the following macro, which represents the
   default floating-point environment (that is, the one installed at program
   startup) and has type pointer to const-qualified fenv_t. It can be used as
   an argument to the functions within the <fenv.h> header that manage the
   floating-point environment.
*/

__BEGIN_DECLS

  extern const fenv_t _FEdefault;
#define FE_DFL_ENV	(&_FEdefault)
  extern fenv_t _FEcurrent;

/* The following shall be declared as functions and may also be defined as
   macros. Function prototypes shall be provided.
*/
  int feclearexcept (int);
  int fegetenv (fenv_t *);
  int fegetexceptflag (fexcept_t *, int);
  int fegetround (void);
  int feholdexcept (fenv_t *);
  int feraiseexcept (int);
  int fesetenv (const fenv_t *);
  int fesetexceptflag (const fexcept_t *, int);
  int fesetround (int);
  int fetestexcept (int);
  int feupdateenv (const fenv_t *);

__END_DECLS

/* The FENV_ACCESS pragma provides a means to inform the implementation when
   an application might access the floating-point environment to test floating-
   point status flags or run under non-default floating-point control modes.
   The pragma shall occur either outside external declarations or preceding
   all explicit declarations and statements inside a compound statement. When
   outside external declarations, the pragma takes effect from its occurrence
   until another FENV_ACCESS pragma is encountered, or until the end of the
   translation unit. When inside a compound statement, the pragma takes effect
   from its occurrence until another FENV_ACCESS pragma is encountered
   (including within a nested compound statement), or until the end of the
   compound statement; at the end of a compound statement the state for the
   pragma is restored to its condition just before the compound statement.
   If this pragma is used in any other context, the behavior is undefined.
   If part of an application tests floating-point status flags, sets floating-
   point control modes, or runs under non-default mode settings, but was
   translated with the state for the FENV_ACCESS pragma off, the behavior is
   undefined. The default state (on or off) for the pragma is implementation-
   defined. (When execution passes from a part of the application translated
   with FENV_ACCESS off to a part translated with FENV_ACCESS on, the state of
   the floating-point status flags is unspecified and the floating-point
   control modes have their default settings.)
*/

#endif /* __FENV_H__ */