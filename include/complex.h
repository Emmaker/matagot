/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* complex.h - complex arithmetic

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the
   ISO C standard. Any conflict between the requirements described here and
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers
   to the ISO C standard.
*/

#ifndef _COMPLEX_H
#define _COMPLEX_H

#include <sys/cdefs.h>

/* The <complex.h> header shall define the following macros:

   complex              Expands to _Complex.
   _Complex_I           Expands to a constant expression of type
                        const float _Complex, with the value of the
                        imaginary unit (that is, a number i such that
                        i^2=-1).
   imaginary            Expands to _Imaginary.
   _Imaginary_I         Expands to a constant expression of type
                        const float _Imaginary with the value of the
                        imaginary unit.
   I                    Expands to either _Imaginary_I or _Complex_I.
                        If _Imaginary_I is not defined, I expands to
                        _Complex_I.

The macros imaginary and _Imaginary_I shall be defined if and only if the
implementation supports imaginary types.  */

extern const float _C_I[2];

#define complex         _Complex
#define _Complex_I      (*((const float _Complex *)_C_I))
#define imaginary       _Imaginary
#define _Imaginary_I    (*((const float _Imaginary *)(_C_I + 1)))
#define I               _Imaginary_I

/* An application may undefine and then, perhaps, redefine the complex,
   imaginary, and I macros.  */

/* The following macros were defined in C11:  */
/*
#define CMPLX(x, y)     ((double _Complex)((double)(x) \
                          + _Imaginary_I * (double)(y)))
#define CMPLXF(x, y)    ((float _Complex)((float)(x) \
                          + _Imaginary_I * (float)(y)))
#define CMPLXL(x, y)    ((long double _Complex)((long double)(x) \
                          + _Imaginary_I * (long double)(y)))
*/
#define CMPLX(x, y)	\
(*(double _Complex *)&((double[]){[0] = (double)x, [1] = (double)y}))
#define CMPLXF(x, y)	\
(*(float _Complex *)&((float[]){[0] = (float)x, [1] = (float)y}))
#define CMPLXL(x, y)	\
(*(long double _Complex *)&((long double[]){[0] = (long double)x, \
[1] = (long double)y}))

/* The following shall be declared as functions and may also be defined as
   macros. Function prototypes shall be provided.  */
__BEGIN_DECLS

  double cabs (double _Complex);
  float cabsf (float _Complex);
  long double cabsl (long double _Complex);
  double _Complex cacos (double _Complex);
  float _Complex cacosf (float _Complex);
  double _Complex cacosh (double _Complex);
  float _Complex cacoshf (float _Complex);
  long double _Complex cacoshl (long double _Complex);
  long double _Complex cacosl (long double _Complex);
  double carg (double _Complex);
  float cargf (float _Complex);
  long double cargl (long double _Complex);
  double _Complex casin (double _Complex);
  float _Complex casinf (float _Complex);
  double _Complex casinh (double _Complex);
  float _Complex casinhf (float _Complex);
  long double _Complex casinhl (long double _Complex);
  long double _Complex casinl (long double _Complex);
  double _Complex catan (double _Complex);
  float _Complex catanf (float _Complex);
  double _Complex catanh (double _Complex);
  float _Complex catanhf (float _Complex);
  long double _Complex catanhl (long double _Complex);
  long double _Complex catanl (long double _Complex);
  double _Complex ccos (double _Complex);
  float _Complex ccosf (float _Complex);
  double _Complex ccosh (double _Complex);
  float _Complex ccoshf (float _Complex);
  long double _Complex ccoshl (long double _Complex);
  long double _Complex ccosl (long double _Complex);
  double _Complex cexp (double _Complex);
  float _Complex cexpf (float _Complex);
  long double _Complex cexpl (long double _Complex);
  double cimag (double _Complex);
  float cimagf (float _Complex);
  long double cimagl (long double _Complex);
  double _Complex clog (double _Complex);
  float _Complex clogf (float _Complex);
  long double _Complex clogl (long double _Complex);
  double _Complex conj (double _Complex);
  float _Complex conjf (float _Complex);
  long double _Complex conjl (long double _Complex);
  double _Complex cpow (double _Complex, double _Complex);
  float _Complex cpowf (float _Complex, float _Complex);
  long double _Complex cpowl (long double _Complex, long double _Complex);
  double _Complex cproj (double _Complex);
  float _Complex cprojf (float _Complex);
  long double _Complex cprojl (long double _Complex);
  double creal (double _Complex);
  float crealf (float _Complex);
  long double creall (long double _Complex);
  double _Complex csin (double _Complex);
  float _Complex csinf (float _Complex);
  double _Complex csinh (double _Complex);
  float _Complex csinhf (float _Complex);
  long double _Complex csinhl (long double _Complex);
  long double _Complex csinl (long double _Complex);
  double _Complex csqrt (double _Complex);
  float _Complex csqrtf (float _Complex);
  long double _Complex csqrtl (long double _Complex);
  double _Complex ctan (double _Complex);
  float _Complex ctanf (float _Complex);
  double _Complex ctanh (double _Complex);
  float _Complex ctanhf (float _Complex);
  long double _Complex ctanhl (long double _Complex);
  long double _Complex ctanl (long double _Complex);

__END_DECLS

#endif /* _COMPLEX_H */