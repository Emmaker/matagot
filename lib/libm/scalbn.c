/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* scalbln, scalblnf, scalblnl, scalbn, scalbnf, scalbnl - 
   compute exponent using FLT_RADIX

   AUTHOR: Gregory Pietsch
   
   DESCRIPTION

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2017 defers 
   to the ISO C standard.

   These functions shall compute x * FLT_RADIX^n efficiently, not normally 
   by computing FLT_RADIX^n explicitly.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return x * FLT_RADIX^n.

   If the result would cause overflow, a range error shall occur and these 
   functions shall return +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL 
   (according to the sign of x) as appropriate for the return type of the 
   function.

   If the correct value would cause underflow, and is not representable, 
   a range error may occur, and scalbln(), scalblnf(), scalblnl(), scalbn(), 
   scalbnf(), and scalbnl() shall return 0.0, or (if IEC 60559 Floating-Point 
   is not supported) an implementation-defined value no greater in magnitude 
   than DBL_MIN, FLT_MIN, LDBL_MIN, DBL_MIN, FLT_MIN, and LDBL_MIN, 
   respectively.

   If x is NaN, a NaN shall be returned.

   If x is +/-0 or +/-Inf, x shall be returned.

   If n is 0, x shall be returned.

   If the correct value would cause underflow, and is representable, a range 
   error may occur and the correct value shall be returned.

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
   The result underflows.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

static long double
intpow (long double x, long n)
{
  long double y = 1.0L;
  unsigned long u;

  if (n < 0L)
    u = -n;
  else
    u = n;
  while (u)
    {
      if (u & 1)
	y *= x;
      u >>= 1;
      x *= x;
    }
  if (n < 0L)
    y = 1.0L / y;
  return y;
}

double
(scalbln) (double x, long n)
{
#if FLT_RADIX == 2
  return ldexp (x, (int) n);
#else
  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      if (n != 0)
	x *= intpow ((long double) FLT_RADIX, n);
      return x;
    }
#endif
}

float (scalblnf) (float x, long n)
{
#if FLT_RADIX == 2
  return ldexpf (x, (int) n);
#else
  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      if (n != 0)
	x *= intpow ((long double) FLT_RADIX, n);
      return x;
    }
#endif
}

long double (scalblnl) (long double x, long n)
{
#if FLT_RADIX == 2
  return ldexpl (x, (int) n);
#else
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      if (n != 0)
	x *= intpow ((long double) FLT_RADIX, n);
      return x;
    }
#endif
}

double (scalbn) (double x, int n)
{
#if FLT_RADIX == 2
  return ldexp (x, n);
#else
  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      if (n != 0)
	x *= intpow ((long double) FLT_RADIX, (long) n);
      return x;
    }
#endif
}

float 
(scalbnf) (float x, int n)
{
#if FLT_RADIX == 2
  return ldexpf (x, n);
#else
  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      if (n != 0)
	x *= intpow ((long double) FLT_RADIX, (long) n);
      return x;
    }
#endif
}

long double 
(scalbnl) (long double x, int n)
{
#if FLT_RADIX == 2
  return ldexpl (x, n);
#else
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      if (n != 0)
	x *= intpow ((long double) FLT_RADIX, (long) n);
      return x;
    }
#endif
}

/* END OF FILE */
