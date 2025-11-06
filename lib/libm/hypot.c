/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* hypot, hypotf, hypotl - Euclidean distance function

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the value of the square root of x^2+y^2 
   without undue overflow or underflow.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the length of the 
   hypotenuse of a right-angled triangle with sides of length x and y.

   If the correct value would cause overflow, a range error shall occur and 
   hypot(), hypotf(), and hypotl() shall return the value of the macro 
   HUGE_VAL, HUGE_VALF, and HUGE_VALL, respectively.

   If x or y is +/-Inf, +Inf shall be returned (even if one of x or y is NaN).

   If x or y is NaN, and the other is not +/-Inf, a NaN shall be returned.

   If both arguments are subnormal and the correct result is subnormal, a 
   range error may occur and the correct result shall be returned. 

   ERRORS:

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

double (hypot) (double x, double y)
{
  double z;
  int errx, erry, errz;

  errx = _Fpclassify (x);
  erry = _Fpclassify (y);
  if (errx == FP_INFINITE || erry == FP_INFINITE)
    return _Dbl->_Inf._D;
  if (errx == FP_NAN || erry == FP_NAN)
    return errx == FP_NAN ? x : y;
  _Setsign ((unsigned char *) &x, _Dbl, 0);
  _Setsign ((unsigned char *) &y, _Dbl, 0);
  if (errx == FP_ZERO)
    return y;
  if (erry == FP_ZERO)
    return x;
  if (x > y)
    {
      z = x;
      x = y;
      y = z;
    }
  z = x / y;
  z = sqrt (1.0 + z * z);
  z *= y;
  errz = _Fpclassify (z);
  if (errz == FP_INFINITE)
    _Matherr (ERANGE, FE_OVERFLOW);
  else if (errx == FP_SUBNORMAL && erry == FP_SUBNORMAL
	   && errz == FP_SUBNORMAL)
    _Matherr (ERANGE, FE_UNDERFLOW);
  return z;
}

float (hypotf) (float x, float y)
{
  float z;
  int errx, erry, errz;

  errx = _Fpclassifyf (x);
  erry = _Fpclassifyf (y);
  if (errx == FP_INFINITE || erry == FP_INFINITE)
    return _Flt->_Inf._F;
  if (errx == FP_NAN || erry == FP_NAN)
    return errx == FP_NAN ? x : y;
  _Setsign ((unsigned char *) &x, _Flt, 0);
  _Setsign ((unsigned char *) &y, _Flt, 0);
  if (errx == FP_ZERO)
    return y;
  if (erry == FP_ZERO)
    return x;
  if (x > y)
    {
      z = x;
      x = y;
      y = z;
    }
  z = x / y;
  z = sqrtf (1.0F + z * z);
  z *= y;
  errz = _Fpclassifyf (z);
  if (errz == FP_INFINITE)
    _Matherr (ERANGE, FE_OVERFLOW);
  else if (errx == FP_SUBNORMAL && erry == FP_SUBNORMAL
	   && errz == FP_SUBNORMAL)
    _Matherr (ERANGE, FE_UNDERFLOW);
  return z;
}

long double (hypotl) (long double x, long double y)
{
  long double z;
  int errx, erry, errz;

  errx = _Fpclassifyl (x);
  erry = _Fpclassifyl (y);
  if (errx == FP_INFINITE || erry == FP_INFINITE)
    return _Ldbl->_Inf._L;
  if (errx == FP_NAN || erry == FP_NAN)
    return errx == FP_NAN ? x : y;
  _Setsign ((unsigned char *) &x, _Ldbl, 0);
  _Setsign ((unsigned char *) &y, _Ldbl, 0);
  if (errx == FP_ZERO)
    return y;
  if (erry == FP_ZERO)
    return x;
  if (x > y)
    {
      z = x;
      x = y;
      y = z;
    }
  z = x / y;
  z = sqrtl (1.0L + z * z);
  z *= y;
  errz = _Fpclassifyl (z);
  if (errz == FP_INFINITE)
    _Matherr (ERANGE, FE_OVERFLOW);
  else if (errx == FP_SUBNORMAL && erry == FP_SUBNORMAL
	   && errz == FP_SUBNORMAL)
    _Matherr (ERANGE, FE_UNDERFLOW);
  return z;
}

/* END OF FILE */
