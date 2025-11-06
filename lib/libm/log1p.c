/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* log1p, log1pf, log1pl - compute a natural logarithm

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute log(1.0 + x).

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the natural 
   logarithm of 1.0 + x.

   If x is -1, a pole error shall occur and log1p(), log1pf(), and 
   log1pl() shall return -HUGE_VAL, -HUGE_VALF, and -HUGE_VALL, 
   respectively.

   For finite values of x that are less than -1, or if x is -Inf, a domain 
   error shall occur, and either a NaN (if supported), or an implementation-
   defined value shall be returned.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, or +Inf, x shall be returned.

   If x is subnormal, a range error may occur and x should be returned.

   If x is not returned, log1p(), log1pf(), and log1pl() shall return an 
   implementation-defined value no greater in magnitude than DBL_MIN, 
   FLT_MIN, and LDBL_MIN, respectively.

   ERRORS

   These functions shall fail if:
   
   Domain Error
   The finite value of x is less than -1, or x is -Inf.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   Pole Error
   The value of x is -1. 
   
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero,
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the divide-by-zero 
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

double (log1p) (double x)
{
  double y, t, z;
  unsigned i;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      if (_Getsign ((unsigned char *) &x, _Dbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      else
	return x;
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return x;
    default:
      if (x < -1.0)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      if (x == -1.0)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return -HUGE_VAL;
	}
      if (x < -1e-4 || x > 1e-4)
	return log (1.0 + x);
      /* The magnitude of x is small enough that we can do a Taylor series here.
         log(1+x) = x - x^2/2 + x^3/3 ... */
      y = t = x;
      i = 2U;
      do
	{
	  z = y;
	  t *= x;
	  if (i & 1)
	    y += t / i;
	  else
	    y -= t / i;
	  z -= y;  
	}
      while (_Fpclassify(z) != FP_ZERO);
      return y;
    }
}

float (log1pf) (float x)
{
  float y, t, z;
  unsigned i;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      if (_Getsign ((unsigned char *) &x, _Flt))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      else
	return x;
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return x;
    default:
      if (x < -1.0F)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      if (x == -1.0F)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return -HUGE_VALF;
	}
      if (x < -1e-4F || x > 1e-4F)
	return logf (1.0F + x);
      /* The magnitude of x is small enough that we can do a Taylor series here.
         log(1+x) = x - x^2/2 + x^3/3 ... */
      y = t = x;
      i = 2U;
      do
	{
	  z = y;
	  t *= x;
	  if (i & 1)
	    y += t / i;
	  else
	    y -= t / i;
	  z -= y;  
	}
      while (_Fpclassifyf(z) != FP_ZERO);
      return y;
    }
}

long double (log1pl) (long double x)
{
  long double y, t, z;
  unsigned i;

  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      if (_Getsign ((unsigned char *) &x, _Ldbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      else
	return x;
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return x;
    default:
      if (x < -1.0L)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      if (x == -1.0L)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return -HUGE_VALL;
	}
      if (x < -1e-4L || x > 1e-4L)
	return logl (1.0L + x);
      /* The magnitude of x is small enough that we can do a Taylor series here.
         log(1+x) = x - x^2/2 + x^3/3 ... */
      y = t = x;
      i = 2U;
      do
	{
	  z = y;
	  t *= x;
	  if (i & 1)
	    y += t / i;
	  else
	    y -= t / i;
	  z -= y;  
	}
      while (_Fpclassifyl(z) != FP_ZERO);
      return y;
    }
}

/* END OF FILE */
