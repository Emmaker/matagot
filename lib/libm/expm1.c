/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* expm1, expm1f, expm1l - compute exponential functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute e^x-1.0.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions return e^x-1.0.

   If the correct value would cause overflow, a range error shall occur and 
   expm1(), expm1f(), and expm1l() shall return the value of the macro 
   HUGE_VAL, HUGE_VALF, and HUGE_VALL, respectively.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, +/-0 shall be returned.

   If x is -Inf, -1 shall be returned.

   If x is +Inf, x shall be returned.

   If x is subnormal, a range error may occur and x should be returned.

   If x is not returned, expm1(), expm1f(), and expm1l() shall return an 
   implementation-defined value no greater in magnitude than DBL_MIN, 
   FLT_MIN, and LDBL_MIN, respectively.

   ERRORS

   These functions shall fail if:
   Range Error
   The result overflows. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.

   These functions may fail if:
   Range Error
   The value of x is subnormal. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

double (expm1) (double x)
{
  double y, t, z;
  unsigned i = 2U;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Dbl) ? -1.0 : x;
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return x;
    default:
      /* exp(x) = 1 + x + x^2/2! + x^3/3! ... Just subtract the first addend. */
      y = t = x;
      do
	{
	  z = y;
	  t *= t / i;
	  y += t;
	  ++i;
	  z -= y;
	}
      while (_Fpclassify (z) != FP_ZERO);
      return y;
    }
}

float (expm1f) (float x)
{
  float y, t, z;
  unsigned i = 2U;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Flt) ? -1.0F : x;
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return x;
    default:
      /* exp(x) = 1 + x + x^2/2! + x^3/3! ... Just subtract the first addend. */
      y = t = x;
      do
	{
	  z = y;
	  t *= t / i;
	  y += t;
	  ++i;
	  z -= y;
	}
      while (_Fpclassifyf (z) != FP_ZERO);
      return y;
    }
}

long double (expm1l) (long double x)
{
  long double y, t, z;
  unsigned i = 2U;
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Ldbl) ? -1.0L : x;
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return x;
    default:
      /* exp(x) = 1 + x + x^2/2! + x^3/3! ... Just subtract the first addend. */
      y = t = x;
      do
	{
	  z = y;
	  t *= t / i;
	  y += t;
	  ++i;
	  z -= y;
	}
      while (_Fpclassifyl (z) != FP_ZERO);
      return y;
    }
}

/* END OF FILE */
