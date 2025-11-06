/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* remquo, remquof, remquol - remainder functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The remquo(), remquof(), and remquol() functions shall compute the same 
   remainder as the remainder(), remainderf(), and remainderl() functions, 
   respectively. In the object pointed to by quo, they store a value whose 
   sign is the sign of x/y and whose magnitude is congruent modulo 2^n to the 
   magnitude of the integral quotient of x/y, where n is an implementation-
   defined integer greater than or equal to 3. If y is zero, the value stored 
   in the object pointed to by quo is unspecified.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   These functions shall return x REM y.

   On systems that do not support the IEC 60559 Floating-Point option, if y 
   is zero, it is implementation-defined whether a domain error occurs or 
   zero is returned.

   If x or y is NaN, a NaN shall be returned.

   If x is +/-Inf or y is zero and the other argument is non-NaN, a domain 
   error shall occur, and a NaN shall be returned.

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

double (remquo) (double x, double y, int *quo)
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
  *quo = (int) z;
  return x - n * y;
}

float (remquof) (float x, float y, int *quo)
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
  *quo = (int) z;
  return x - n * y;
}

long double (remquol) (long double x, long double y, int *quo)
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
  *quo = (int) z;
  return x - n * y;
}

/* END OF FILE */
