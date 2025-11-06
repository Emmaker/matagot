/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* log, logf, logl - natural logarithm function

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the natural logarithm of their argument x.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the natural 
   logarithm of x.

   If x is +/-0, a pole error shall occur and log(), logf(), and logl() shall 
   return -HUGE_VAL, -HUGE_VALF, and -HUGE_VALL, respectively.

   For finite values of x that are less than 0, or if x is -Inf, a domain 
   error shall occur, and either a NaN (if supported), or an implementation-
   defined value shall be returned.

   If x is NaN, a NaN shall be returned.

   If x is 1, +0 shall be returned.

   If x is +Inf, x shall be returned.

   ERRORS:

   These functions shall fail if:

   Domain Error
   The finite value of x is negative, or x is -Inf.
    
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   Pole Error
   The value of x is zero. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the divide-by-zero 
   floating-point exception shall be raised.
*/

#include "xmath.h"

double (log) (double x)
{
  double f, z, w, r, b;
  int e;
  unsigned long i;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      if (_Getsign ((unsigned char *) &x, _Dbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VAL;
    default:
      if (_Getsign ((unsigned char *) &x, _Dbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      if (x == 1.0)
	return +0.0;
      f = frexp (x, &e);
      if (f < M_SQRT1_2)
	{
	  z = f - 0.5;
	  z /= z + 1.0;
	  --e;
	}
      else
	z = (f - 1.0) / (f + 1.0);
      w = z * z;
      i = 3;
      r = z;
      do
	{
	  b = r;
	  z *= w;
	  r += z / i;
	  i += 2;
	}
      while (r - b > 0.0);
      r += r + e * M_LN2;
      return r;
    }
}

float (logf) (float x)
{
  float f, z, w, r, b;
  int e;
  unsigned long i;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      if (_Getsign ((unsigned char *) &x, _Flt))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VALF;
    default:
      if (_Getsign ((unsigned char *) &x, _Flt))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      if (x == 1.0F)
	return +0.0F;
      f = frexpf (x, &e);
      if (f < _M_SQRT1_2F)
	{
	  z = f - 0.5F;
	  z /= z + 1.0F;
	  --e;
	}
      else
	z = (f - 1.0F) / (f + 1.0F);
      w = z * z;
      i = 3;
      r = z;
      do
	{
	  b = r;
	  z *= w;
	  r += z / i;
	  i += 2;
	}
      while (r - b > 0.0F);
      r += r + e * _M_LN2F;
      return r;
    }
}

long double (logl) (long double x)
{
  long double f, z, w, r, b;
  int e;
  unsigned long i;

  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      if (_Getsign ((unsigned char *) &x, _Ldbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VALL;
    default:
      if (_Getsign ((unsigned char *) &x, _Ldbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      if (x == 1.0L)
	return +0.0L;
      f = frexpl (x, &e);
      if (f < _M_SQRT1_2L)
	{
	  z = f - 0.5L;
	  z /= z + 1.0L;
	  --e;
	}
      else
	z = (f - 1.0L) / (f + 1.0L);
      w = z * z;
      i = 3;
      r = z;
      do
	{
	  b = r;
	  z *= w;
	  r += z / i;
	  i += 2;
	}
      while (r - b > 0.0L);
      r += r + e * _M_LN2L;
      return r;
    }
}

/* END OF FILE */
