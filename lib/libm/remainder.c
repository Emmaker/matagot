/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* remainder, remainderf, remainderl - remainder function

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall return the floating-point remainder r=x-ny when y 
   is non-zero. The value n is the integral value nearest the exact value x/y.
   When |n-x/y|=1/2, the value n is chosen to be even.

   The behavior of remainder() shall be independent of the rounding mode.

   RETURN VALUE:

   Upon successful completion, these functions shall return the floating-
   point remainder r=x-ny when y is non-zero.

   On systems that do not support the IEC 60559 Floating-Point option, if y 
   is zero, it is implementation-defined whether a domain error occurs or 
   zero is returned.

   If x or y is NaN, a NaN shall be returned.

   If x is infinite or y is 0 and the other is non-NaN, a domain error shall 
   occur, and a NaN shall be returned.

   ERRORS:

   These functions shall fail if:
   Domain Error
   The x argument is +/-Inf, or the y argument is +/-0 and the other argument 
   is non-NaN. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised. 

   These functions may fail if:
   Domain Error
   The y argument is zero. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.
*/

#include "xmath.h"

double (remainder) (double x, double y)
{
  int errx, erry;
  double n, z;

  errx = _Fpclassify (x);
  erry = _Fpclassify (y);
  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;
  if (errx == FP_INFINITE || erry == FP_ZERO)
    {
      _Matherr (EDOM, FE_INVALID);
      return _Dbl->_Nan._D;
    }
  z = x / y;
  n = round (z);
  if ((n - z == 0.5 || z - n == 0.5) && ldexp (trunc (ldexp (n, -1)), 1) != n)
    n += (z > n) - (z < n);
  return x - n * y;
}

float (remainderf) (float x, float y)
{
  int errx, erry;
  float n, z;

  errx = _Fpclassifyf (x);
  erry = _Fpclassifyf (y);
  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;
  if (errx == FP_INFINITE || erry == FP_ZERO)
    {
      _Matherr (EDOM, FE_INVALID);
      return _Flt->_Nan._F;
    }
  z = x / y;
  n = roundf (z);
  if ((n - z == 0.5F || z - n == 0.5F)
      && ldexpf (truncf (ldexpf (n, -1)), 1) != n)
    n += (z > n) - (z < n);
  return x - n * y;
}

long double (remainderl) (long double x, long double y)
{
  int errx, erry;
  long double n, z;

  errx = _Fpclassifyl (x);
  erry = _Fpclassifyl (y);
  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;
  if (errx == FP_INFINITE || erry == FP_ZERO)
    {
      _Matherr (EDOM, FE_INVALID);
      return _Ldbl->_Nan._L;
    }
  z = x / y;
  n = roundl (z);
  if ((n - z == 0.5L || z - n == 0.5L)
      && ldexpl (truncl (ldexpl (n, -1)), 1) != n)
    n += (z > n) - (z < n);
  return x - n * y;
}

/* END OF FILE */
