/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* asin, asinf, asinl - arc sine function

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the principal value of the arc sine of their 
   argument x. The value of x should be in the range [-1,1].

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the arc sine of x, 
   in the range [-pi/2,pi/2] radians.

   For finite values of x not in the range [-1,1], a domain error shall occur, 
   and either a NaN (if supported), or an implementation-defined value shall 
   be returned.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, x shall be returned.

   If x is +/-Inf, a domain error shall occur, and a NaN shall be returned.

   If x is subnormal, a range error may occur and x should be returned.

   If x is not returned, asin(), asinf(), and asinl() shall return an 
   implementation-defined value no greater in magnitude than DBL_MIN, 
   FLT_MIN, and LDBL_MIN, respectively.

   ERRORS:

   These functions shall fail if:

   Domain Error

   The x argument is finite and is not in the range [-1,1], or is +/-Inf.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   These functions may fail if:

   Range Error 
   
   The value of x is subnormal. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.

   ALGORITHM:
   1. Handle special cases.
   2. Pick off the sign since asin(-x) = -asin(x).
   3. Use a series to calculate asin(x).
*/

#include "xmath.h"

double (asin) (double x)
{
  double c, d, p, t, w, y;
  unsigned long i;
  int s;

  switch (_Fpclassify (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      /* FALL THROUGH */
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Dbl->_Nan._D;
    default:
      if (x < -1.0 || x > 1.0)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      /* asin(z) = z + (1/2)z^3/3 + (1*3)/(2*4)z^5/5 + (1*3*5)/(2*4*6)z^7/7 
                     + ... */
      s = _Getsign ((unsigned char *) &x, _Dbl);
      _Setsign ((unsigned char *) &x, _Dbl, 0);
      w = x * x;
      p = y = x;
      c = 1.0;
      i = 3;
      do
	{
	  d = y;
	  p *= w;
	  c *= i - 2UL;
	  c /= i - 1UL;
	  y += c * p / i;
	  d -= y;
	  i += 2UL;
	}
      while (d != 0.0);
      _Setsign ((unsigned char *) &y, _Dbl, s);
      return y;
    }
}

float (asinf) (float x)
{
  float c, d, p, t, w, y;
  unsigned long i;
  int s;

  switch (_Fpclassifyf (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      /* FALL THROUGH */
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Flt->_Nan._F;
    default:
      if (x < -1.0F || x > 1.0F)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      /* asin(z) = z + (1/2)z^3/3 + (1*3)/(2*4)z^5/5 + (1*3*5)/(2*4*6)z^7/7 
                     + ... */
      s = _Getsign ((unsigned char *) &x, _Flt);
      _Setsign ((unsigned char *) &x, _Flt, 0);
      w = x * x;
      p = y = x;
      c = 1.0F;
      i = 3UL;
      do
	{
	  d = y;
	  p *= w;
	  c *= i - 2UL;
	  c /= i - 1UL;
	  y += c * p / i;
	  d -= y;
	  i += 2UL;
	}
      while (d != 0.0F);
      _Setsign ((unsigned char *) &y, _Flt, s);
      return y;
    }
}

long double (asinl) (long double x)
{
  long double c, d, p, t, w, y;
  unsigned long i;
  int s;

  switch (_Fpclassifyl (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      /* FALL THROUGH */
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Ldbl->_Nan._L;
    default:
      if (x < -1.0L || x > 1.0L)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      /* asin(z) = z + (1/2)z^3/3 + (1*3)/(2*4)z^5/5 + (1*3*5)/(2*4*6)z^7/7 
                   + ... */
      s = _Getsign ((unsigned char *) &x, _Ldbl);
      _Setsign ((unsigned char *) &x, _Ldbl, 0);
      w = x * x;
      p = y = x;
      c = 1.0L;
      i = 3UL;
      do
	{
	  d = y;
	  p *= w;
	  c *= i - 2UL;
	  c /= i - 1UL;
	  y += c * p / i;
	  d -= y;
	  i += 2UL;
	}
      while (d != 0.0L);
      _Setsign ((unsigned char *) &y, _Ldbl, s);
      return y;
    }
}

/* END OF FILE */
