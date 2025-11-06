/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* atanh, atanhf, atanhl - inverse hyperbolic tangent functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the inverse hyperbolic tangent of their 
   argument x.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the inverse 
   hyperbolic tangent of their argument.

   If x is +/-1, a pole error shall occur, and atanh(), atanhf(), and atanhl() 
   shall return the value of the macro HUGE_VAL, HUGE_VALF, and HUGE_VALL, 
   respectively, with the same sign as the correct value of the function.

   For finite |x|>1, a domain error shall occur, and either a NaN (if 
   supported), or an implementation-defined value shall be returned.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, x shall be returned.

   If x is +/-Inf, a domain error shall occur, and a NaN shall be returned.

   If x is subnormal, a range error may occur and x should be returned.

   If x is not returned, atanh(), atanhf(), and atanhl() shall return an 
   implementation-defined value no greater in magnitude than DBL_MIN, FLT_MIN, 
   and LDBL_MIN, respectively.

   ERRORS:

   These functions shall fail if:
   Domain Error
   The x argument is finite and not in the range [-1,1], or is +/-Inf.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, then 
   errno shall be set to EDOM. If the integer expression (math_errhandling & 
   MATH_ERREXCEPT) is non-zero, then the invalid floating-point exception 
   shall be raised.

   Pole Error
   The x argument is +/-1. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, then 
   errno shall be set to ERANGE. If the integer expression (math_errhandling & 
   MATH_ERREXCEPT) is non-zero, then the divide-by-zero floating-point 
   exception shall be raised.

   These functions may fail if:
   Range Error
   The value of x is subnormal. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, then 
   errno shall be set to ERANGE. If the integer expression (math_errhandling & 
   MATH_ERREXCEPT) is non-zero, then the underflow floating-point exception 
   shall be raised.
*/

#include "xmath.h"

double (atanh) (double x)
{
  double p, r, w, y;
  unsigned long i;

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
      if (x < -1.0 || x > +1.0)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      else if (x == -1.0)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return -HUGE_VAL;
	}
      else if (x == +1.0)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return +HUGE_VAL;
	}
      else if (x > -0.5 && x < 0.5)
	{
	  /* Use rational approximation */
	  p = r = x;
	  w = x * x;
	  for (i = 3;; i += 2)
	    {
	      y = r;
	      p *= w;
	      r += p / i;
	      y -= r;
	      if (y == 0.0)
		break;
	    }
	  return r;
	}
      else
	return ldexp (log ((1.0 + x) / (1.0 - x)), -1);
    }
}

float (atanhf) (float x)
{
  float p, r, w, y;
  unsigned long i;

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
      if (x < -1.0F || x > +1.0F)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      else if (x == -1.0F)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return -HUGE_VALF;
	}
      else if (x == +1.0F)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return +HUGE_VALF;
	}
      else if (x > -0.5F && x < 0.5F)
	{
	  /* Use rational approximation */
	  p = r = x;
	  w = x * x;
	  for (i = 3;; i += 2)
	    {
	      y = r;
	      p *= w;
	      r += p / i;
	      y -= r;
	      if (y == 0.0)
		break;
	    }
	  return r;
	}
      else
	return ldexpf (logf ((1.0F + x) / (1.0F - x)), -1);
    }
}

long double (atanhl) (long double x)
{
  long double p, r, w, y;
  unsigned long i;

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
      if (x < -1.0L || x > +1.0L)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      else if (x == -1.0L)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return -HUGE_VALL;
	}
      else if (x == +1.0L)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return +HUGE_VALL;
	}
      else if (x > -0.5L && x < 0.5L)
	{
	  /* Use rational approximation */
	  p = r = x;
	  w = x * x;
	  for (i = 3;; i += 2)
	    {
	      y = r;
	      p *= w;
	      r += p / i;
	      y -= r;
	      if (y == 0.0)
		break;
	    }
	  return r;
	}
      else
	return ldexpl (logl ((1.0L + x) / (1.0L - x)), -1);
    }
}

/* END OF FILE */
