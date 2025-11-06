/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* acos, acosf, acosl - arc cosine functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the principal value of the arc cosine of 
   their argument x. The value of x should be in the range [-1,1].

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the arc cosine 
   of x, in the range [0,pi] radians.

   For finite values of x not in the range [-1,1], a domain error shall occur, 
   and either a NaN (if supported), or an implementation-defined value shall be 
   returned.

   If x is NaN, a NaN shall be returned.

   If x is +1, +0 shall be returned.

   If x is +/-Inf, a domain error shall occur, and a NaN shall be returned. 

   ERRORS:

   These functions shall fail if:

   Domain Error
   
   The x argument is finite and is not in the range [-1,1], or is +/-Inf.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, then 
   errno shall be set to EDOM. If the integer expression (math_errhandling & 
   MATH_ERREXCEPT) is non-zero, then the invalid floating-point exception shall 
   be raised.

   ALGORITHM:

   Handle special cases, then compute the arcsine and subtract it from pi/2.

*/

#include "xmath.h"

double (acos) (double x)
{
  double y;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Dbl->_Nan._D;
    case FP_ZERO:
      return M_PI_2;
    default:
      if (x < -1.0 || x > 1.0)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      if (x == 1.0)
	return +0.0;
      if (x > 0.5)
	return ldexp (asin (sqrt (0.5 - 0.5 * x)), 1);
      if (x < -0.5)
	return M_PI - ldexp (asin (sqrt (0.5 * (1.0 + x))), 1);
      y = M_PI_2 - asin (x);
      return y;
    }
}

float (acosf) (float x)
{
  float y;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Flt->_Nan._F;
    case FP_ZERO:
      return _M_PI_2F;
    default:
      if (x < -1.0F || x > 1.0F)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      if (x == 1.0F)
	return +0.0F;
      if (x > 0.5F)
	return ldexpf (asinf (sqrtf (0.5F - 0.5F * x)), 1);
      if (x < -0.5F)
	return _M_PIF - ldexpf (asinf (sqrtf (0.5F * (1.0F + x))), 1);
      y = _M_PI_2F - asinf (x);
      return y;
    }
}

long double (acosl) (long double x)
{
  long double y;

  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Ldbl->_Nan._L;
    case FP_ZERO:
      return _M_PI_2L;
    default:
      if (x < -1.0L || x > 1.0L)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      if (x == 1.0L)
	return +0.0L;
      if (x > 0.5L)
	return ldexpl (asinl (sqrtl (0.5L - 0.5L * x)), 1);
      if (x < -0.5L)
	return _M_PIL - ldexpl (asinl (sqrtl (0.5L * (1.0L + x))), 1);
      y = _M_PI_2L - asinl (x);
      return y;
    }
}

/* END OF FILE */
